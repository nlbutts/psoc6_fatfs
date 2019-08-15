/*******************************************************************************
* File Name: cycfg_peripherals.h
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

#if !defined(CYCFG_PERIPHERALS_H)
#define CYCFG_PERIPHERALS_H

#include "cycfg_notices.h"
#include "cy_sd_host.h"
#include "cy_usbfs_dev_drv.h"
#include "cy_sysclk.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define SDCARD_HW SDHC1
#define SDCARD_IRQ sdhc_1_interrupt_general_IRQn
#define USBUART_ACTIVE_ENDPOINTS_MASK 7U
#define USBUART_ENDPOINTS_BUFFER_SIZE 140U
#define USBUART_ENDPOINTS_ACCESS_TYPE 0U
#define USBUART_USB_CORE 4U
#define USBUART_HW USBFS0
#define USBUART_HI_IRQ usb_interrupt_hi_IRQn
#define USBUART_MED_IRQ usb_interrupt_med_IRQn
#define USBUART_LO_IRQ usb_interrupt_lo_IRQn

extern cy_en_sd_host_card_capacity_t SDCARD_cardCapacity;
extern cy_en_sd_host_card_type_t SDCARD_cardType;
extern uint32_t SDCARD_rca;
extern const cy_stc_sd_host_init_config_t SDCARD_config;
extern cy_stc_sd_host_sd_card_config_t SDCARD_card_cfg;
extern const cy_stc_usbfs_dev_drv_config_t USBUART_config;

void init_cycfg_peripherals(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_PERIPHERALS_H */
