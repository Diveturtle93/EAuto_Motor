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
#define ECO_Pin GPIO_PIN_3
#define ECO_GPIO_Port GPIOE
#define BC_DOWN_Pin GPIO_PIN_4
#define BC_DOWN_GPIO_Port GPIOE
#define DURCHFLUSS_Pin GPIO_PIN_5
#define DURCHFLUSS_GPIO_Port GPIOE
#define BUTTON2_Pin GPIO_PIN_6
#define BUTTON2_GPIO_Port GPIOE
#define POWER_ON_Pin GPIO_PIN_13
#define POWER_ON_GPIO_Port GPIOC
#define WS2812_Pin GPIO_PIN_3
#define WS2812_GPIO_Port GPIOC
#define CRASH_Pin GPIO_PIN_0
#define CRASH_GPIO_Port GPIOA
#define EMERGENCY_RUN_Pin GPIO_PIN_1
#define EMERGENCY_RUN_GPIO_Port GPIOA
#define HW_WAKE_Pin GPIO_PIN_2
#define HW_WAKE_GPIO_Port GPIOA
#define PCB_ADC_Pin GPIO_PIN_7
#define PCB_ADC_GPIO_Port GPIOA
#define LED_RED_Pin GPIO_PIN_0
#define LED_RED_GPIO_Port GPIOB
#define RECUPERATION_Pin GPIO_PIN_11
#define RECUPERATION_GPIO_Port GPIOF
#define DCDC_INSTRUCTION_Pin GPIO_PIN_0
#define DCDC_INSTRUCTION_GPIO_Port GPIOG
#define DCCDC_FAULT_Pin GPIO_PIN_1
#define DCCDC_FAULT_GPIO_Port GPIOG
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
#define LED_ORANGE_Pin GPIO_PIN_14
#define LED_ORANGE_GPIO_Port GPIOB
#define ANLASSER_Pin GPIO_PIN_15
#define ANLASSER_GPIO_Port GPIOB
#define KL15_Pin GPIO_PIN_8
#define KL15_GPIO_Port GPIOD
#define BAMOCAR_IN1_Pin GPIO_PIN_10
#define BAMOCAR_IN1_GPIO_Port GPIOD
#define BAMOCAR_IN2_Pin GPIO_PIN_12
#define BAMOCAR_IN2_GPIO_Port GPIOD
#define BUZZER_Pin GPIO_PIN_2
#define BUZZER_GPIO_Port GPIOG
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
#define ENTER_Pin GPIO_PIN_7
#define ENTER_GPIO_Port GPIOC
#define ACAN_RX_Pin GPIO_PIN_8
#define ACAN_RX_GPIO_Port GPIOA
#define OUTA_Pin GPIO_PIN_9
#define OUTA_GPIO_Port GPIOA
#define OUTB_Pin GPIO_PIN_10
#define OUTB_GPIO_Port GPIOA
#define BC_UP_Pin GPIO_PIN_11
#define BC_UP_GPIO_Port GPIOA
#define ACAN_TX_Pin GPIO_PIN_15
#define ACAN_TX_GPIO_Port GPIOA
#define ASR_IN2_Pin GPIO_PIN_4
#define ASR_IN2_GPIO_Port GPIOD
#define DEBUG_UART2TX_Pin GPIO_PIN_5
#define DEBUG_UART2TX_GPIO_Port GPIOD
#define DEBUG_UART2RX_Pin GPIO_PIN_6
#define DEBUG_UART2RX_GPIO_Port GPIOD
#define LED_BLUE_Pin GPIO_PIN_7
#define LED_BLUE_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
