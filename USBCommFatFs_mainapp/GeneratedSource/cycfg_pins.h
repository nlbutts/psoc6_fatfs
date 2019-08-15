/*******************************************************************************
* File Name: cycfg_pins.h
*
* Description:
* Pin configuration
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

#if !defined(CYCFG_PINS_H)
#define CYCFG_PINS_H

#include "cycfg_notices.h"
#include "cy_gpio.h"
#include "cycfg_routing.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define BUTTON_PORT GPIO_PRT0
#define BUTTON_PIN 4U
#define BUTTON_NUM 4U
#define BUTTON_DRIVEMODE CY_GPIO_DM_PULLUP
#define BUTTON_INIT_DRIVESTATE 1
#ifndef ioss_0_port_0_pin_4_HSIOM
	#define ioss_0_port_0_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define BUTTON_HSIOM ioss_0_port_0_pin_4_HSIOM
#define BUTTON_IRQ ioss_interrupts_gpio_0_IRQn
#define CARD_DET_PORT GPIO_PRT12
#define CARD_DET_PIN 1U
#define CARD_DET_NUM 1U
#define CARD_DET_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CARD_DET_INIT_DRIVESTATE 1
#ifndef ioss_0_port_12_pin_1_HSIOM
	#define ioss_0_port_12_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CARD_DET_HSIOM ioss_0_port_12_pin_1_HSIOM
#define CARD_DET_IRQ ioss_interrupts_gpio_12_IRQn
#define ioss_0_port_12_pin_4_PORT GPIO_PRT12
#define ioss_0_port_12_pin_4_PIN 4U
#define ioss_0_port_12_pin_4_NUM 4U
#define ioss_0_port_12_pin_4_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_12_pin_4_INIT_DRIVESTATE 1
#ifndef ioss_0_port_12_pin_4_HSIOM
	#define ioss_0_port_12_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_12_pin_4_IRQ ioss_interrupts_gpio_12_IRQn
#define ioss_0_port_12_pin_5_PORT GPIO_PRT12
#define ioss_0_port_12_pin_5_PIN 5U
#define ioss_0_port_12_pin_5_NUM 5U
#define ioss_0_port_12_pin_5_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_12_pin_5_INIT_DRIVESTATE 1
#ifndef ioss_0_port_12_pin_5_HSIOM
	#define ioss_0_port_12_pin_5_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_12_pin_5_IRQ ioss_interrupts_gpio_12_IRQn
#define ioss_0_port_13_pin_0_PORT GPIO_PRT13
#define ioss_0_port_13_pin_0_PIN 0U
#define ioss_0_port_13_pin_0_NUM 0U
#define ioss_0_port_13_pin_0_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_13_pin_0_INIT_DRIVESTATE 1
#ifndef ioss_0_port_13_pin_0_HSIOM
	#define ioss_0_port_13_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_13_pin_0_IRQ ioss_interrupts_gpio_13_IRQn
#define ioss_0_port_13_pin_1_PORT GPIO_PRT13
#define ioss_0_port_13_pin_1_PIN 1U
#define ioss_0_port_13_pin_1_NUM 1U
#define ioss_0_port_13_pin_1_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_13_pin_1_INIT_DRIVESTATE 1
#ifndef ioss_0_port_13_pin_1_HSIOM
	#define ioss_0_port_13_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_13_pin_1_IRQ ioss_interrupts_gpio_13_IRQn
#define ioss_0_port_13_pin_2_PORT GPIO_PRT13
#define ioss_0_port_13_pin_2_PIN 2U
#define ioss_0_port_13_pin_2_NUM 2U
#define ioss_0_port_13_pin_2_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_13_pin_2_INIT_DRIVESTATE 1
#ifndef ioss_0_port_13_pin_2_HSIOM
	#define ioss_0_port_13_pin_2_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_13_pin_2_IRQ ioss_interrupts_gpio_13_IRQn
#define ioss_0_port_13_pin_3_PORT GPIO_PRT13
#define ioss_0_port_13_pin_3_PIN 3U
#define ioss_0_port_13_pin_3_NUM 3U
#define ioss_0_port_13_pin_3_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_13_pin_3_INIT_DRIVESTATE 1
#ifndef ioss_0_port_13_pin_3_HSIOM
	#define ioss_0_port_13_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_13_pin_3_IRQ ioss_interrupts_gpio_13_IRQn
#define ioss_0_port_14_pin_0_PORT GPIO_PRT14
#define ioss_0_port_14_pin_0_PIN 0U
#define ioss_0_port_14_pin_0_NUM 0U
#define ioss_0_port_14_pin_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_14_pin_0_INIT_DRIVESTATE 1
#ifndef ioss_0_port_14_pin_0_HSIOM
	#define ioss_0_port_14_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_14_pin_0_IRQ ioss_interrupts_gpio_14_IRQn
#define ioss_0_port_14_pin_1_PORT GPIO_PRT14
#define ioss_0_port_14_pin_1_PIN 1U
#define ioss_0_port_14_pin_1_NUM 1U
#define ioss_0_port_14_pin_1_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_14_pin_1_INIT_DRIVESTATE 1
#ifndef ioss_0_port_14_pin_1_HSIOM
	#define ioss_0_port_14_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_14_pin_1_IRQ ioss_interrupts_gpio_14_IRQn
#define WRITE_TIME_PORT GPIO_PRT5
#define WRITE_TIME_PIN 0U
#define WRITE_TIME_NUM 0U
#define WRITE_TIME_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define WRITE_TIME_INIT_DRIVESTATE 1
#ifndef ioss_0_port_5_pin_0_HSIOM
	#define ioss_0_port_5_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define WRITE_TIME_HSIOM ioss_0_port_5_pin_0_HSIOM
#define WRITE_TIME_IRQ ioss_interrupts_gpio_5_IRQn
#define READ_TIME_PORT GPIO_PRT5
#define READ_TIME_PIN 1U
#define READ_TIME_NUM 1U
#define READ_TIME_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define READ_TIME_INIT_DRIVESTATE 1
#ifndef ioss_0_port_5_pin_1_HSIOM
	#define ioss_0_port_5_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define READ_TIME_HSIOM ioss_0_port_5_pin_1_HSIOM
#define READ_TIME_IRQ ioss_interrupts_gpio_5_IRQn
#define ioss_0_port_6_pin_4_PORT GPIO_PRT6
#define ioss_0_port_6_pin_4_PIN 4U
#define ioss_0_port_6_pin_4_NUM 4U
#define ioss_0_port_6_pin_4_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define ioss_0_port_6_pin_4_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_4_HSIOM
	#define ioss_0_port_6_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_4_IRQ ioss_interrupts_gpio_6_IRQn
#define ioss_0_port_6_pin_6_PORT GPIO_PRT6
#define ioss_0_port_6_pin_6_PIN 6U
#define ioss_0_port_6_pin_6_NUM 6U
#define ioss_0_port_6_pin_6_DRIVEMODE CY_GPIO_DM_PULLUP
#define ioss_0_port_6_pin_6_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_6_HSIOM
	#define ioss_0_port_6_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_6_IRQ ioss_interrupts_gpio_6_IRQn
#define ioss_0_port_6_pin_7_PORT GPIO_PRT6
#define ioss_0_port_6_pin_7_PIN 7U
#define ioss_0_port_6_pin_7_NUM 7U
#define ioss_0_port_6_pin_7_DRIVEMODE CY_GPIO_DM_PULLDOWN
#define ioss_0_port_6_pin_7_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_7_HSIOM
	#define ioss_0_port_6_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_7_IRQ ioss_interrupts_gpio_6_IRQn

extern const cy_stc_gpio_pin_config_t BUTTON_config;
extern const cy_stc_gpio_pin_config_t CARD_DET_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_12_pin_4_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_12_pin_5_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_13_pin_0_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_13_pin_1_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_13_pin_2_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_13_pin_3_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_14_pin_0_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_14_pin_1_config;
extern const cy_stc_gpio_pin_config_t WRITE_TIME_config;
extern const cy_stc_gpio_pin_config_t READ_TIME_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_4_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_6_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_7_config;

void init_cycfg_pins(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_PINS_H */
