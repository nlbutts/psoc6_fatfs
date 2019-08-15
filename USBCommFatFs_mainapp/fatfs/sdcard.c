/*
* @Author: nbutts
* @Date:   2019-08-14 16:46:49
* @Last Modified by:   nbutts
* @Last Modified time: 2019-08-14 17:20:34
*/

#include "cy_pdl.h"
#include "cycfg.h"
#include "ff.h"
#include "diskio.h"



/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/

//#include "STM32F100.h"


/* MMC/SD command */
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)		/* ERASE_ER_BLK_START */
#define CMD33	(33)		/* ERASE_ER_BLK_END */
#define CMD38	(38)		/* ERASE */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */


static volatile
DSTATUS Stat = STA_NOINIT;	/* Physical drive status */

static volatile
UINT Timer1, Timer2;	/* 1kHz decrement timer stopped at zero (disk_timerproc()) */

static
BYTE CardType;			/* Card type flags */

cy_stc_sd_host_context_t _sdHostContext;

#if 0
/*-----------------------------------------------------------------------*/
/* SPI controls (Platform dependent)                                     */
/*-----------------------------------------------------------------------*/

/* Initialize MMC interface */
static
void init_spi (void)
{
	SPIxENABLE();		/* Enable SPI function */
	CS_HIGH();			/* Set CS# high */

	for (Timer1 = 10; Timer1; ) ;	/* 10ms */
}


/* Exchange a byte */
static
BYTE xchg_spi (
	BYTE dat	/* Data to send */
)
{
	SPIx_DR = dat;				/* Start an SPI transaction */
	while ((SPIx_SR & 0x83) != 0x03) ;	/* Wait for end of the transaction */
	return (BYTE)SPIx_DR;		/* Return received byte */
}


/* Receive multiple byte */
static
void rcvr_spi_multi (
	BYTE *buff,		/* Pointer to data buffer */
	UINT btr		/* Number of bytes to receive (even number) */
)
{
	WORD d;


	SPIx_CR1 &= ~_BV(6);
	SPIx_CR1 |= (_BV(6) | _BV(11));	/* Put SPI into 16-bit mode */

	SPIx_DR = 0xFFFF;		/* Start the first SPI transaction */
	btr -= 2;
	do {					/* Receive the data block into buffer */
		while ((SPIx_SR & 0x83) != 0x03) ;	/* Wait for end of the SPI transaction */
		d = SPIx_DR;						/* Get received word */
		SPIx_DR = 0xFFFF;					/* Start next transaction */
		buff[1] = d; buff[0] = d >> 8; 		/* Store received data */
		buff += 2;
	} while (btr -= 2);
	while ((SPIx_SR & 0x83) != 0x03) ;		/* Wait for end of the SPI transaction */
	d = SPIx_DR;							/* Get last word received */
	buff[1] = d; buff[0] = d >> 8;			/* Store it */

	SPIx_CR1 &= ~(_BV(6) | _BV(11));	/* Put SPI into 8-bit mode */
	SPIx_CR1 |= _BV(6);
}


#if FF_FS_READONLY == 0
/* Send multiple byte */
static
void xmit_spi_multi (
	const BYTE *buff,	/* Pointer to the data */
	UINT btx			/* Number of bytes to send (even number) */
)
{
	WORD d;


	SPIx_CR1 &= ~_BV(6);
	SPIx_CR1 |= (_BV(6) | _BV(11));		/* Put SPI into 16-bit mode */

	d = buff[0] << 8 | buff[1]; buff += 2;
	SPIx_DR = d;	/* Send the first word */
	btx -= 2;
	do {
		d = buff[0] << 8 | buff[1]; buff += 2;	/* Word to send next */
		while ((SPIx_SR & 0x83) != 0x03) ;	/* Wait for end of the SPI transaction */
		SPIx_DR;							/* Discard received word */
		SPIx_DR = d;						/* Start next transaction */
	} while (btx -= 2);
	while ((SPIx_SR & 0x83) != 0x03) ;	/* Wait for end of the SPI transaction */
	SPIx_DR;							/* Discard received word */

	SPIx_CR1 &= ~(_BV(6) | _BV(11));	/* Put SPI into 8-bit mode */
	SPIx_CR1 |= _BV(6);
}
#endif


/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/

static
int wait_ready (	/* 1:Ready, 0:Timeout */
	UINT wt			/* Timeout [ms] */
)
{
	BYTE d;


	Timer2 = wt;
	do {
		d = xchg_spi(0xFF);
		/* This loop takes a time. Insert rot_rdq() here for multitask envilonment. */
	} while (d != 0xFF && Timer2);	/* Wait for card goes ready or timeout */

	return (d == 0xFF) ? 1 : 0;
}



/*-----------------------------------------------------------------------*/
/* Deselect card and release SPI                                         */
/*-----------------------------------------------------------------------*/

static
void deselect (void)
{
	CS_HIGH();		/* Set CS# high */
	xchg_spi(0xFF);	/* Dummy clock (force DO hi-z for multiple slave SPI) */

}



/*-----------------------------------------------------------------------*/
/* Select card and wait for ready                                        */
/*-----------------------------------------------------------------------*/

static
int select (void)	/* 1:OK, 0:Timeout */
{
	CS_LOW();		/* Set CS# low */
	xchg_spi(0xFF);	/* Dummy clock (force DO enabled) */
	if (wait_ready(500)) return 1;	/* Wait for card ready */

	deselect();
	return 0;	/* Timeout */
}



/*-----------------------------------------------------------------------*/
/* Receive a data packet from the MMC                                    */
/*-----------------------------------------------------------------------*/

static
int rcvr_datablock (	/* 1:OK, 0:Error */
	BYTE *buff,			/* Data buffer */
	UINT btr			/* Data block length (byte) */
)
{
	BYTE token;


	Timer1 = 200;
	do {							/* Wait for DataStart token in timeout of 200ms */
		token = xchg_spi(0xFF);
		/* This loop will take a time. Insert rot_rdq() here for multitask envilonment. */
	} while ((token == 0xFF) && Timer1);
	if(token != 0xFE) return 0;		/* Function fails if invalid DataStart token or timeout */

	rcvr_spi_multi(buff, btr);		/* Store trailing data to the buffer */
	xchg_spi(0xFF); xchg_spi(0xFF);			/* Discard CRC */

	return 1;						/* Function succeeded */
}



/*-----------------------------------------------------------------------*/
/* Send a data packet to the MMC                                         */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0
static
int xmit_datablock (	/* 1:OK, 0:Failed */
	const BYTE *buff,	/* Ponter to 512 byte data to be sent */
	BYTE token			/* Token */
)
{
	BYTE resp;


	if (!wait_ready(500)) return 0;		/* Wait for card ready */

	xchg_spi(token);					/* Send token */
	if (token != 0xFD) {				/* Send data if token is other than StopTran */
		xmit_spi_multi(buff, 512);		/* Data */
		xchg_spi(0xFF); xchg_spi(0xFF);	/* Dummy CRC */

		resp = xchg_spi(0xFF);				/* Receive data resp */
		if ((resp & 0x1F) != 0x05) return 0;	/* Function fails if the data packet was not accepted */
	}
	return 1;
}
#endif


/*-----------------------------------------------------------------------*/
/* Send a command packet to the MMC                                      */
/*-----------------------------------------------------------------------*/

static
BYTE send_cmd (		/* Return value: R1 resp (bit7==1:Failed to send) */
	BYTE cmd,		/* Command index */
	DWORD arg		/* Argument */
)
{
	BYTE n, res;

	return res;							/* Return received response */
}
#endif


/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Initialize disk drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE drv		/* Physical drive number (0) */
)
{
    /* Allocate context for SD Host operation */
    volatile cy_en_sd_host_status_t host_status;
    /* Configure SD Host to operate */
    Cy_SD_Host_Enable(SDCARD_HW);
    host_status = Cy_SD_Host_Init(SDCARD_HW, &SDCARD_config, &_sdHostContext);

    cy_en_sd_host_card_type_t cardType;
    uint32_t rca;
    cy_en_sd_host_card_capacity_t cardCapacity;
    /* Populate configuration structure */
    cy_stc_sd_host_sd_card_config_t sdCardConfig =
    {
        .lowVoltageSignaling = false,
        .busWidth = CY_SD_HOST_BUS_WIDTH_4_BIT,
        .cardType = &cardType,
        .rca = &rca,
        .cardCapacity = &cardCapacity,
    };
    /* Initialize the card */
    host_status = Cy_SD_Host_InitCard(SDCARD_HW, &sdCardConfig, &_sdHostContext);

    if (CY_SD_HOST_SUCCESS == host_status)
    {
    	Stat &= ~STA_NOINIT;
    }
    else
    {
    	Stat |= STA_NOINIT;
    }

    // Get the CSD register
    uint8_t csd[32];
    host_status = Cy_SD_Host_GetCsd(SDCARD_HW, (uint32_t*)&csd, &_sdHostContext);

	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Get disk status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE drv		/* Physical drive number (0) */
)
{
	if (drv) return STA_NOINIT;		/* Supports only drive 0 */

	return Stat;	/* Return disk status */
}



/*-----------------------------------------------------------------------*/
/* Read sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE drv,		/* Physical drive number (0) */
	BYTE *buff,		/* Pointer to the data buffer to store read data */
	DWORD sector,	/* Start sector number (LBA) */
	UINT count		/* Number of sectors to read (1..128) */
)
{
	if (drv || !count) return RES_PARERR;		/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */

	//if (!(CardType & CT_BLOCK)) sector *= 512;	/* LBA ot BA conversion (byte addressing cards) */

    cy_stc_sd_host_write_read_config_t data;
    cy_en_sd_host_status_t ret;

    data.address = sector;         /* The address to write/read data on the card or eMMC. */
    data.numberOfBlocks = count;  /* The number of blocks to write/read (Single block write/read). */
    data.autoCommand = CY_SD_HOST_AUTO_CMD_NONE;  /* Selects which auto commands are used if any. */
    data.dataTimeout = 12UL;     /* The timeout value for the transfer. */
    data.enReliableWrite = false; /* For EMMC cards enable reliable write. */
    data.enableDma = true;  /* Enable DMA mode. */
    data.data = (uint32_t*)buff;  /* The pointer to data to write. */
    Cy_SD_Host_ClearNormalInterruptStatus(SDCARD_HW, CY_SD_HOST_XFER_COMPLETE);
    ret = Cy_SD_Host_Read(SDCARD_HW, &data, &_sdHostContext);  /* Write data to the card. */
    volatile int loop_counter = 0;
    if (CY_SD_HOST_SUCCESS == ret)
    {
        while (CY_SD_HOST_XFER_COMPLETE != (Cy_SD_Host_GetNormalInterruptStatus(SDCARD_HW) & CY_SD_HOST_XFER_COMPLETE))
        {
            /* Wait for the data-transaction complete event. */
        	loop_counter++;
        }
    }
    else
    {
    	return RES_ERROR;
    }

	return RES_OK;	/* Return result */
}



/*-----------------------------------------------------------------------*/
/* Write sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive number (0) */
	const BYTE *buff,	/* Ponter to the data to write */
	DWORD sector,		/* Start sector number (LBA) */
	UINT count			/* Number of sectors to write (1..128) */
)
{
	if (drv || !count) return RES_PARERR;		/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check drive status */
	if (Stat & STA_PROTECT) return RES_WRPRT;	/* Check write protect */

	//if (!(CardType & CT_BLOCK)) sector *= 512;	/* LBA ==> BA conversion (byte addressing cards) */

    cy_stc_sd_host_write_read_config_t data;
    cy_en_sd_host_status_t ret;

    data.address = sector;         /* The address to write/read data on the card or eMMC. */
    data.numberOfBlocks = count;  /* The number of blocks to write/read (Single block write/read). */
    data.autoCommand = CY_SD_HOST_AUTO_CMD_NONE;  /* Selects which auto commands are used if any. */
    data.dataTimeout = 12UL;     /* The timeout value for the transfer. */
    data.enReliableWrite = false; /* For EMMC cards enable reliable write. */
    data.enableDma = true;  /* Enable DMA mode. */
    data.data = (uint32_t*)buff;  /* The pointer to data to write. */
    Cy_SD_Host_ClearNormalInterruptStatus(SDCARD_HW, CY_SD_HOST_XFER_COMPLETE);
    ret = Cy_SD_Host_Write(SDCARD_HW, &data, &_sdHostContext);  /* Write data to the card. */
    volatile int loop_counter = 0;
    if (CY_SD_HOST_SUCCESS == ret)
    {
    	volatile uint32_t status = Cy_SD_Host_GetNormalInterruptStatus(SDCARD_HW);
    	volatile uint32_t sdStatus[16];
    	Cy_SD_Host_GetSdStatus(SDCARD_HW, &sdStatus, &_sdHostContext);

        while (CY_SD_HOST_XFER_COMPLETE != (Cy_SD_Host_GetNormalInterruptStatus(SDCARD_HW) & CY_SD_HOST_XFER_COMPLETE))
        {
            /* Wait for the data-transaction complete event. */
        	loop_counter++;
        }
    }
    else
    {
    	return RES_ERROR;
    }

	return RES_OK;	/* Return result */
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous drive controls other than data read/write               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive number (0) */
	BYTE cmd,		/* Control command code */
	void *buff		/* Pointer to the conrtol data */
)
{
	DRESULT res;
	BYTE n, csd[16];
	//DWORD *dp, st, ed, csize;
	DWORD csize;
	cy_en_sd_host_status_t host_status;

	if (drv) return RES_PARERR;					/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */

	res = RES_ERROR;

	switch (cmd) {
	case CTRL_SYNC :		/* Wait for end of internal write process of the drive */
		//if (select()) res = RES_OK;
		break;

	case GET_SECTOR_COUNT :	/* Get drive capacity in unit of sector (DWORD) */
		host_status = Cy_SD_Host_GetCsd(SDCARD_HW, (uint32_t*)&csd, &_sdHostContext);
		if (CY_SD_HOST_SUCCESS == host_status)
		{
			if ((csd[0] >> 6) == 1) {	/* SDC ver 2.00 */
				csize = csd[9] + ((WORD)csd[8] << 8) + ((DWORD)(csd[7] & 63) << 16) + 1;
				*(DWORD*)buff = csize << 10;
			} else {					/* SDC ver 1.XX or MMC ver 3 */
				n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
				csize = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
				*(DWORD*)buff = csize << (n - 9);
			}
			res = RES_OK;
		}
		break;

#if 0
	case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */

		if (CardType & CT_SD2) {	/* SDC ver 2.00 */
			if (send_cmd(ACMD13, 0) == 0) {	/* Read SD status */
				xchg_spi(0xFF);
				if (rcvr_datablock(csd, 16)) {				/* Read partial block */
					for (n = 64 - 16; n; n--) xchg_spi(0xFF);	/* Purge trailing data */
					*(DWORD*)buff = 16UL << (csd[10] >> 4);
					res = RES_OK;
				}
			}
		} else {					/* SDC ver 1.XX or MMC */
			if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {	/* Read CSD */
				if (CardType & CT_SD1) {	/* SDC ver 1.XX */
					*(DWORD*)buff = (((csd[10] & 63) << 1) + ((WORD)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
				} else {					/* MMC */
					*(DWORD*)buff = ((WORD)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
				}
				res = RES_OK;
			}
		}
		break;

	case CTRL_TRIM :	/* Erase a block of sectors (used when _USE_ERASE == 1) */
		if (!(CardType & CT_SDC)) break;				/* Check if the card is SDC */
		if (disk_ioctl(drv, MMC_GET_CSD, csd)) break;	/* Get CSD */
		if (!(csd[0] >> 6) && !(csd[10] & 0x40)) break;	/* Check if sector erase can be applied to the card */
		dp = buff; st = dp[0]; ed = dp[1];				/* Load sector block */
		if (!(CardType & CT_BLOCK)) {
			st *= 512; ed *= 512;
		}
		if (send_cmd(CMD32, st) == 0 && send_cmd(CMD33, ed) == 0 && send_cmd(CMD38, 0) == 0 && wait_ready(30000)) {	/* Erase sector block */
			res = RES_OK;	/* FatFs does not check result of this command */
		}
		break;
#endif

	default:
		res = RES_PARERR;
	}

	return res;
}

DWORD get_fattime()
{
	return 0;
}
