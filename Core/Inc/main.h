/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#if REVISION == 255
//#error "Revision ist nicht definiert"
//#elif REVISION == 1
//#warning "PCB Revision 1.0 definiert"
//#elif REVISION == 2
//#warning "PCB Revision 1.1 definiert"
//#endif

// FIXME: BAMOCAR_IN1
// FIXME: BAMOCAR_IN2
// FIXME: BAMOCAR_Out1
// FIXME: BAMOCAR_Out2
// FIXME: Anhaenger
// FIXME: Klima_PWM
// FIXME: Klima Out
// FIXME: DCDC_Instruction
// FIXME: EGas
// FIXME: Reserve
// FIXME: DCDC_Fault
// FIXME: HW_Wake
// FIXME: BC_Rst_Out
// FIXME: Niveau
// FIXME: BC_Rst_Out
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DIGITAL1_Pin GPIO_PIN_2
#define DIGITAL1_GPIO_Port GPIOE
#define ECO_Pin GPIO_PIN_3
#define ECO_GPIO_Port GPIOE
#define BC_DOWN_IN_Pin GPIO_PIN_4
#define BC_DOWN_IN_GPIO_Port GPIOE
#define DURCHFLUSS_Pin GPIO_PIN_5
#define DURCHFLUSS_GPIO_Port GPIOE
#define BUTTON2_Pin GPIO_PIN_6
#define BUTTON2_GPIO_Port GPIOE
#define POWER_ON_Pin GPIO_PIN_13
#define POWER_ON_GPIO_Port GPIOC
#define BUTTON1_Pin GPIO_PIN_0
#define BUTTON1_GPIO_Port GPIOF
#define ECON_Pin GPIO_PIN_1
#define ECON_GPIO_Port GPIOF
#define OELDRUCK_Pin GPIO_PIN_2
#define OELDRUCK_GPIO_Port GPIOF
#define BC_DOWN_OUT_Pin GPIO_PIN_3
#define BC_DOWN_OUT_GPIO_Port GPIOF
#define BC_UP_OUT_Pin GPIO_PIN_4
#define BC_UP_OUT_GPIO_Port GPIOF
#define BC_RESET_OUT_Pin GPIO_PIN_5
#define BC_RESET_OUT_GPIO_Port GPIOF
#define SPI5_CS_Pin GPIO_PIN_6
#define SPI5_CS_GPIO_Port GPIOF
#define SPI5_SCK_Pin GPIO_PIN_7
#define SPI5_SCK_GPIO_Port GPIOF
#define SPI5_MISO_Pin GPIO_PIN_8
#define SPI5_MISO_GPIO_Port GPIOF
#define SPI5_MOSI_Pin GPIO_PIN_9
#define SPI5_MOSI_GPIO_Port GPIOF
#define WS2812_Pin GPIO_PIN_3
#define WS2812_GPIO_Port GPIOC
#define CRASH_Pin GPIO_PIN_0
#define CRASH_GPIO_Port GPIOA
#define EMERGENCY_RUN_Pin GPIO_PIN_1
#define EMERGENCY_RUN_GPIO_Port GPIOA
#define HW_WAKE_Pin GPIO_PIN_2
#define HW_WAKE_GPIO_Port GPIOA
#define SENSE_KL15_Pin GPIO_PIN_3
#define SENSE_KL15_GPIO_Port GPIOA
#define SENSE_KUEHLWASSER_Pin GPIO_PIN_4
#define SENSE_KUEHLWASSER_GPIO_Port GPIOA
#define SENSE_KLIMA_FLAP_Pin GPIO_PIN_5
#define SENSE_KLIMA_FLAP_GPIO_Port GPIOA
#define SENSE_GAS_Pin GPIO_PIN_6
#define SENSE_GAS_GPIO_Port GPIOA
#define SENSE_PCB_Pin GPIO_PIN_7
#define SENSE_PCB_GPIO_Port GPIOA
#define SENSE_DRUCK_Pin GPIO_PIN_4
#define SENSE_DRUCK_GPIO_Port GPIOC
#define SENSE_DRUCK_TEMP_Pin GPIO_PIN_5
#define SENSE_DRUCK_TEMP_GPIO_Port GPIOC
#define SENSE_RETURN_Pin GPIO_PIN_0
#define SENSE_RETURN_GPIO_Port GPIOB
#define SENSE_INFO_Pin GPIO_PIN_1
#define SENSE_INFO_GPIO_Port GPIOB
#define RED_LED_Pin GPIO_PIN_2
#define RED_LED_GPIO_Port GPIOB
#define RECUPERATION_Pin GPIO_PIN_11
#define RECUPERATION_GPIO_Port GPIOF
#define BAMOCAR_OUT1_Pin GPIO_PIN_12
#define BAMOCAR_OUT1_GPIO_Port GPIOF
#define BAMOCAR_OUT2_Pin GPIO_PIN_13
#define BAMOCAR_OUT2_GPIO_Port GPIOF
#define J317_Pin GPIO_PIN_14
#define J317_GPIO_Port GPIOF
#define DCDC_ENABLE_Pin GPIO_PIN_15
#define DCDC_ENABLE_GPIO_Port GPIOF
#define DCDC_INSTRUCTION_Pin GPIO_PIN_0
#define DCDC_INSTRUCTION_GPIO_Port GPIOG
#define DCDC_FAULT_Pin GPIO_PIN_1
#define DCDC_FAULT_GPIO_Port GPIOG
#define GLUEHKERZEN_Pin GPIO_PIN_7
#define GLUEHKERZEN_GPIO_Port GPIOE
#define KICKDOWN_Pin GPIO_PIN_8
#define KICKDOWN_GPIO_Port GPIOE
#define LEERLAUF_Pin GPIO_PIN_9
#define LEERLAUF_GPIO_Port GPIOE
#define KUPPLUNG_NO_Pin GPIO_PIN_10
#define KUPPLUNG_NO_GPIO_Port GPIOE
#define BREMSE_NC_Pin GPIO_PIN_11
#define BREMSE_NC_GPIO_Port GPIOE
#define BREMSE_NO_Pin GPIO_PIN_12
#define BREMSE_NO_GPIO_Port GPIOE
#define SENSE_SDC_AKKU_Pin GPIO_PIN_13
#define SENSE_SDC_AKKU_GPIO_Port GPIOE
#define SENSE_SDC_0_Pin GPIO_PIN_14
#define SENSE_SDC_0_GPIO_Port GPIOE
#define MOTOR_SDC_OUT_Pin GPIO_PIN_15
#define MOTOR_SDC_OUT_GPIO_Port GPIOE
#define SENSE_SDC_BTB_Pin GPIO_PIN_10
#define SENSE_SDC_BTB_GPIO_Port GPIOB
#define F54_Pin GPIO_PIN_11
#define F54_GPIO_Port GPIOB
#define F18_Pin GPIO_PIN_12
#define F18_GPIO_Port GPIOB
#define KLIMA_OUT_Pin GPIO_PIN_13
#define KLIMA_OUT_GPIO_Port GPIOB
#define GREEN_LED_Pin GPIO_PIN_14
#define GREEN_LED_GPIO_Port GPIOB
#define BAMOCAR_IN2_Pin GPIO_PIN_15
#define BAMOCAR_IN2_GPIO_Port GPIOB
#define KL15_Pin GPIO_PIN_8
#define KL15_GPIO_Port GPIOD
#define BREMSLICHT_Pin GPIO_PIN_9
#define BREMSLICHT_GPIO_Port GPIOD
#define ANLASSER_Pin GPIO_PIN_10
#define ANLASSER_GPIO_Port GPIOD
#define RUECKFAHRLICHT_Pin GPIO_PIN_11
#define RUECKFAHRLICHT_GPIO_Port GPIOD
#define BAMOCAR_IN1_Pin GPIO_PIN_12
#define BAMOCAR_IN1_GPIO_Port GPIOD
#define KLIMA_PWM_Pin GPIO_PIN_13
#define KLIMA_PWM_GPIO_Port GPIOD
#define ANHAENGER_Pin GPIO_PIN_14
#define ANHAENGER_GPIO_Port GPIOD
#define NIVEAU_OUT_Pin GPIO_PIN_15
#define NIVEAU_OUT_GPIO_Port GPIOD
#define BUZZER_Pin GPIO_PIN_2
#define BUZZER_GPIO_Port GPIOG
#define GENERATOR_LED_Pin GPIO_PIN_3
#define GENERATOR_LED_GPIO_Port GPIOG
#define ASR_IN1_Pin GPIO_PIN_4
#define ASR_IN1_GPIO_Port GPIOG
#define GRA1_Pin GPIO_PIN_5
#define GRA1_GPIO_Port GPIOG
#define GRA2_Pin GPIO_PIN_6
#define GRA2_GPIO_Port GPIOG
#define GRA3_Pin GPIO_PIN_7
#define GRA3_GPIO_Port GPIOG
#define GRA4_Pin GPIO_PIN_8
#define GRA4_GPIO_Port GPIOG
#define SD_SW_Pin GPIO_PIN_6
#define SD_SW_GPIO_Port GPIOC
#define ENTER_Pin GPIO_PIN_7
#define ENTER_GPIO_Port GPIOC
#define SD_D0_Pin GPIO_PIN_8
#define SD_D0_GPIO_Port GPIOC
#define SD_D1_Pin GPIO_PIN_9
#define SD_D1_GPIO_Port GPIOC
#define ACAN_RX_Pin GPIO_PIN_8
#define ACAN_RX_GPIO_Port GPIOA
#define OUTA_Pin GPIO_PIN_9
#define OUTA_GPIO_Port GPIOA
#define OUTB_Pin GPIO_PIN_10
#define OUTB_GPIO_Port GPIOA
#define BC_UP_IN_Pin GPIO_PIN_11
#define BC_UP_IN_GPIO_Port GPIOA
#define OELSTAND_TEMP_Pin GPIO_PIN_12
#define OELSTAND_TEMP_GPIO_Port GPIOA
#define ACAN_TX_Pin GPIO_PIN_15
#define ACAN_TX_GPIO_Port GPIOA
#define SD_D2_Pin GPIO_PIN_10
#define SD_D2_GPIO_Port GPIOC
#define SD_D3_Pin GPIO_PIN_11
#define SD_D3_GPIO_Port GPIOC
#define SD_SCK_Pin GPIO_PIN_12
#define SD_SCK_GPIO_Port GPIOC
#define SD_CMD_Pin GPIO_PIN_2
#define SD_CMD_GPIO_Port GPIOD
#define LADELEUCHTE_Pin GPIO_PIN_3
#define LADELEUCHTE_GPIO_Port GPIOD
#define ASR_IN2_Pin GPIO_PIN_4
#define ASR_IN2_GPIO_Port GPIOD
#define DEBUG_UART2TX_Pin GPIO_PIN_5
#define DEBUG_UART2TX_GPIO_Port GPIOD
#define DEBUG_UART2RX_Pin GPIO_PIN_6
#define DEBUG_UART2RX_GPIO_Port GPIOD
#define RUECKWARNUNG_Pin GPIO_PIN_7
#define RUECKWARNUNG_GPIO_Port GPIOD
#define WISCHWARNUNG_Pin GPIO_PIN_9
#define WISCHWARNUNG_GPIO_Port GPIOG
#define BREMSWARNUNG_Pin GPIO_PIN_10
#define BREMSWARNUNG_GPIO_Port GPIOG
#define PUMPE_BREMSE_Pin GPIO_PIN_11
#define PUMPE_BREMSE_GPIO_Port GPIOG
#define BC_RESET_IN_Pin GPIO_PIN_12
#define BC_RESET_IN_GPIO_Port GPIOG
#define PUMPE_KUEHLUNG_Pin GPIO_PIN_13
#define PUMPE_KUEHLUNG_GPIO_Port GPIOG
#define FAN2_Pin GPIO_PIN_14
#define FAN2_GPIO_Port GPIOG
#define FAN1_Pin GPIO_PIN_15
#define FAN1_GPIO_Port GPIOG
#define HEATER2_Pin GPIO_PIN_4
#define HEATER2_GPIO_Port GPIOB
#define CAN2_TX_Pin GPIO_PIN_5
#define CAN2_TX_GPIO_Port GPIOB
#define CAN2_RX_Pin GPIO_PIN_6
#define CAN2_RX_GPIO_Port GPIOB
#define BLUE_LED_Pin GPIO_PIN_7
#define BLUE_LED_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_8
#define I2C1_SCL_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_9
#define I2C1_SDA_GPIO_Port GPIOB
#define HEATER1_Pin GPIO_PIN_0
#define HEATER1_GPIO_Port GPIOE
#define DIGITAL2_Pin GPIO_PIN_1
#define DIGITAL2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
