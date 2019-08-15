/***************************************************************************//**
* \file main.c
* \version 1.0
*
* \brief
* Objective:
*    This code example demonstrates USB CDC interface class operation by
*    implementing virtual COM that continually sends message "Hello USB UART".
*
*    NOTE If OS Windows could not recognize device install driver manually.
*    During driver installation point to the code example folder
*    (includes driver INF file). 
*
* Compatible Kits:
*    CY8CKIT-062-WIFI-BT
*
* Migration to CY8CPROTO-062-4343W kit (ModusToolbox IDE):
*   1. Create this project targeting the CY8CPROTO-062-4343W kit.
*   2. Build and Program
* 
* Migration to CY8CPROTO-062-4343W kit (command line make):
*   1. Perform "make clean"
*   2. Build and Program the device with "make DEVICE=CY8C624ABZI-D44 program"
*      Note that depending on the method used to program the device, you may 
*      need to manually reset it by pressing the SW1 RESET button on the kit.
*   3. To switch back to CY8CKIT-062-WIFI-BT, 
*      perform "make clean", then "make program".
*
* \note
* To connect USB Device (PSoC6) to the USB Host use USB receptacle J28 for 
* CY8CKIT-062-WIFI-BT and J10 for CY8CPROTO-062-4343W.
*
********************************************************************************
* \copyright
* Copyright 2017-2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/


#include <string.h>
#include <stdio.h>

#include "cy_pdl.h"

#include "cy_usbfs_dev_drv.h"
#include "cycfg_usbdev.h"
#include "cycfg.h"

#include "ff.h"


/***************************************************************************
* Interrupt configuration
***************************************************************************/
static void USBUART_IsrHigh(void);
static void USBUART_IsrMedium(void);
static void USBUART_IsrLow(void);

const cy_stc_sysint_t UsbDevIntrHigh =
{
    .intrSrc = (IRQn_Type) usb_interrupt_hi_IRQn,
    .intrPriority = 5U,
};
const cy_stc_sysint_t UsbDevIntrMedium =
{
    .intrSrc = (IRQn_Type) usb_interrupt_med_IRQn,
    .intrPriority = 6U,
};
const cy_stc_sysint_t UsbDevIntrLow =
{
    .intrSrc = (IRQn_Type) usb_interrupt_lo_IRQn,
    .intrPriority = 7U,
};



/***************************************************************************
* Global variables
***************************************************************************/
cy_stc_usbfs_dev_drv_context_t  USBUART_context;
cy_stc_usb_dev_context_t        USBUART_devContext;
cy_stc_usb_dev_cdc_context_t    USBUART_cdcContext;


/***************************************************************************
* USB UART define
***************************************************************************/
#define USBUART_COM_PORT        (0U)


/***************************************************************************
* Function Name: PrintMessage
***************************************************************************/
void PrintMessage(const char msg[])
{
    while (!Cy_USB_Dev_CDC_IsReady(USBUART_COM_PORT, &USBUART_cdcContext)) {};
    if (Cy_USB_Dev_CDC_IsReady(USBUART_COM_PORT, &USBUART_cdcContext))
    {
        Cy_USB_Dev_CDC_PutData(USBUART_COM_PORT, (uint8_t *)msg, strlen(msg),
                                &USBUART_cdcContext);
    }
    Cy_SysLib_Delay(10);
}

FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    static FILINFO fno;
    char str[255];

    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR)
            {                    /* It is a directory */
            	snprintf(str, 255, "DIR: %s/%s\n", path, fno.fname);
            	PrintMessage(str);
            }
            else
            {
            	/* It is a file. */
            	snprintf(str, 255, "%s/%s\n", path, fno.fname);
            	PrintMessage(str);
            }
        }
        f_closedir(&dir);
    }

    return res;
}

void dump_file_contents(char * file)
{
    FRESULT res;
    UINT i;
    FIL f;
    char str[255];
    uint8_t buffer[100];
    UINT br;

	snprintf(str, 255, "opening file %s\n", file);
	PrintMessage(str);
	res = f_open(&f, file, FA_READ);
	if (FR_OK == res)
	{
		PrintMessage("File opened\n");
		res = f_read(&f, buffer, 100, &br);
		if (FR_OK == res)
		{
			snprintf(str, 255, "%d bytes read\n", br);
			PrintMessage(str);
			res = f_close(&f);

			PrintMessage("Dumping data:\n");
			for (i = 0; i < br; i++)
			{
				snprintf(str, 255, "%02X ", buffer[i]);
				PrintMessage(str);
			}
			PrintMessage("\n");
		}
	}
}

void save_data(char * file, uint8_t * buffer, uint32_t len)
{
    FRESULT res;
    FIL f;
    char str[255];
    UINT bw;

	snprintf(str, 255, "opening file %s\n", file);
	PrintMessage(str);
	res = f_open(&f, file, FA_WRITE | FA_CREATE_ALWAYS);
	if (FR_OK == res)
	{
		PrintMessage("File opened\n");
		res = f_write(&f, buffer, len, &bw);
		if (FR_OK == res)
		{
			snprintf(str, 255, "%d bytes written\n", bw);
			PrintMessage(str);
			res = f_close(&f);
		}
	}
}


/***************************************************************************
* Function Name: main.c
***************************************************************************/
int main(void)
{
    cy_en_usb_dev_status_t status;

    /* Set up internal routing, pins, and clock-to-peripheral connections */
    init_cycfg_all();

    /* Initialize USB */
    status = Cy_USB_Dev_Init(USBUART_HW, &USBUART_config, &USBUART_context,
                             &USBUART_devices[0], &USBUART_devConfig, &USBUART_devContext);
    if (CY_USB_DEV_SUCCESS != status)
    {
        /* Initialization error - stop execution */
        while(1);
    }

    status = Cy_USB_Dev_CDC_Init(&USBUART_cdcConfig, &USBUART_cdcContext, &USBUART_devContext);
    if (CY_USB_DEV_SUCCESS != status)
    {
        /* CDC Initialization error - stop execution */
        while(1);
    }

    /* Initialize and enable USB interrupts */
    (void) Cy_SysInt_Init(&UsbDevIntrHigh,   &USBUART_IsrHigh);
    (void) Cy_SysInt_Init(&UsbDevIntrMedium, &USBUART_IsrMedium);
    (void) Cy_SysInt_Init(&UsbDevIntrLow,    &USBUART_IsrLow);

    NVIC_EnableIRQ(UsbDevIntrHigh.intrSrc);
    NVIC_EnableIRQ(UsbDevIntrMedium.intrSrc);
    NVIC_EnableIRQ(UsbDevIntrLow.intrSrc);

    /* Enable interrupts */
    __enable_irq();

    /* Make device appear on the bus */
    Cy_USB_Dev_Connect(true, CY_USB_DEV_WAIT_FOREVER, &USBUART_devContext);

    // Mount the volume
    volatile FRESULT res;
    FATFS fatfs;
    res = f_mount(&fatfs, "", 1);

    PrintMessage("Command > ");

    // Read the files on the drive
    scan_files("/");

	uint8_t prevButton = 0;

#define TEST_LEN 48000
	uint8_t test_data[TEST_LEN];

	for (int i = 0; i < TEST_LEN; i++)
	{
		test_data[i] = i;
	}

	/* Add your application code here */
    for (;;)
    {
        //Cy_SysLib_Delay(1000UL);
    	uint8_t button = Cy_GPIO_Read(BUTTON_PORT, BUTTON_PIN);
    	if ((prevButton == 1) && (button == 0))
    	{
    		scan_files("/");
    		dump_file_contents("//DATA.BIN");
    		save_data("//FOO.bin", test_data, TEST_LEN);
    	}
    	prevButton = button;
    }
}


/***************************************************************************
* Function Name: USBUART_IsrHigh
***************************************************************************/
static void USBUART_IsrHigh(void)
{
    /* Call interrupt processing */
    Cy_USBFS_Dev_Drv_Interrupt(USBUART_HW, 
                               Cy_USBFS_Dev_Drv_GetInterruptCauseHi(USBUART_HW), 
                               &USBUART_context);
}


/***************************************************************************
* Function Name: USBUART_IsrMedium
***************************************************************************/
static void USBUART_IsrMedium(void)
{
    /* Call interrupt processing */
    Cy_USBFS_Dev_Drv_Interrupt(USBUART_HW, 
                               Cy_USBFS_Dev_Drv_GetInterruptCauseMed(USBUART_HW), 
                               &USBUART_context);
}


/***************************************************************************
* Function Name: USBUART_IsrLow
**************************************************************************/
static void USBUART_IsrLow(void)
{
    /* Call interrupt processing */
    Cy_USBFS_Dev_Drv_Interrupt(USBUART_HW, 
                               Cy_USBFS_Dev_Drv_GetInterruptCauseLo(USBUART_HW), 
                               &USBUART_context);
}
