/*******************************************************************************
* File Name: cycfg_peripherals.c
*
* Description:
* Peripheral Hardware Block configuration
* This file was automatically generated and should not be modified.
* 
********************************************************************************
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
********************************************************************************/

#include "cycfg_peripherals.h"

#define USBUART_INTR_LVL_SEL (CY_USBFS_DEV_DRV_SET_SOF_LVL(0x2U) | \
                 CY_USBFS_DEV_DRV_SET_BUS_RESET_LVL(0x2U) | \
                 CY_USBFS_DEV_DRV_SET_EP0_LVL(0x2U) | \
                 CY_USBFS_DEV_DRV_SET_LPM_LVL(0x0U) | \
                 CY_USBFS_DEV_DRV_SET_ARB_EP_LVL(0x0U) | \
                 CY_USBFS_DEV_DRV_SET_EP1_LVL(0x2U) | \
                 CY_USBFS_DEV_DRV_SET_EP2_LVL(0x2U) | \
                 CY_USBFS_DEV_DRV_SET_EP3_LVL(0x1U) | \
                 CY_USBFS_DEV_DRV_SET_EP4_LVL(0x1U) | \
                 CY_USBFS_DEV_DRV_SET_EP5_LVL(0x1U) | \
                 CY_USBFS_DEV_DRV_SET_EP6_LVL(0x1U) | \
                 CY_USBFS_DEV_DRV_SET_EP7_LVL(0x1U) | \
                 CY_USBFS_DEV_DRV_SET_EP8_LVL(0x1U))

cy_en_sd_host_card_capacity_t SDCARD_cardCapacity = CY_SD_HOST_SDSC;
cy_en_sd_host_card_type_t SDCARD_cardType = CY_SD_HOST_NOT_EMMC;
uint32_t SDCARD_rca = 0u;
const cy_stc_sd_host_init_config_t SDCARD_config = 
{
	.emmc = false,
	.dmaType = CY_SD_HOST_DMA_SDMA,
	.enableLedControl = false,
};
cy_stc_sd_host_sd_card_config_t SDCARD_card_cfg = 
{
	.lowVoltageSignaling = false,
	.busWidth = CY_SD_HOST_BUS_WIDTH_4_BIT,
	.cardType = &SDCARD_cardType,
	.rca = &SDCARD_rca,
	.cardCapacity = &SDCARD_cardCapacity,
};
const cy_stc_usbfs_dev_drv_config_t USBUART_config = 
{
	.mode = CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU,
	.epAccess = CY_USBFS_DEV_DRV_USE_8_BITS_DR,
	.epBuffer = NULL,
	.epBufferSize = 0U,
	.dmaConfig[0] = NULL,
	.dmaConfig[1] = NULL,
	.dmaConfig[2] = NULL,
	.dmaConfig[3] = NULL,
	.dmaConfig[4] = NULL,
	.dmaConfig[5] = NULL,
	.dmaConfig[6] = NULL,
	.dmaConfig[7] = NULL,
	.enableLpm = false,
	.intrLevelSel = USBUART_INTR_LVL_SEL,
};


void init_cycfg_peripherals(void)
{
	Cy_SysClk_PeriphAssignDivider(PCLK_USB_CLOCK_DEV_BRS, CY_SYSCLK_DIV_16_BIT, 0U);
}
