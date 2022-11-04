/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SystemInfo.h"
#include "BasicUart.h"
#include "inputs.h"
#include "outputs.h"
#include "adc_inputs.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int32_t temperature;
uint8_t UART2_rxBuffer[12] = {0};
uint8_t UART2_msg[12] = {0};
uint8_t uart_count = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint16_t ADC_VAL[10] = {0};
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_CAN3_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
	/* Schreibe Resetquelle auf die Konsole */
#ifdef DEBUG
	printResetSource(readResetSource());

  	/* Teste serielle Schnittstelle*/
  	#define TEST_STRING_UART  "\nUART2 Transmitting in polling mode, Hello Diveturtle93!\n"
  	uartTransmit(TEST_STRING_UART, sizeof(TEST_STRING_UART));

  	/* Sammel Systeminformationen */
  	collectSystemInfo();
#endif

    HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);

  	/* Lese alle Eingaenge */
  	//readall_inputs();

  	// Lese Temperatur
  	uartTransmit("Temperatur messen\n", 18);
	uartTransmitNumber(*TEMP30_CAL_VALUE, 10);
	uartTransmit("\n", 1);
	uartTransmitNumber(*TEMP110_CAL_VALUE, 10);
	uartTransmit("\n", 1);

	ADC_VAL[4] = ADC_STMTemperatur();
	if(ADC_VAL[4] > 900 && ADC_VAL[4] < 1100)
	{
		temperature = (int32_t)((TEMP110 - TEMP30) / ((float)(*TEMP110_CAL_VALUE) - (float)(*TEMP30_CAL_VALUE)) * (ADC_VAL[4] - (float)(*TEMP30_CAL_VALUE)) + TEMP30);
	}
	else
	{
		temperature = -273;
	}
	uartTransmitNumber(temperature, 10);
	uartTransmit("\n", 1);

	// Lese alle ADC-Eingaenge
	ADC_VAL[0] = ADC_KL15();
	ADC_VAL[1] = ADC_Kuhlwassertemperatur();
	ADC_VAL[2] = ADC_Klimaflap();
	ADC_VAL[3] = ADC_Gaspedal();
	ADC_VAL[4] = ADC_PCBTemperatur();
	ADC_VAL[5] = ADC_Return();
	ADC_VAL[6] = ADC_Info();
	ADC_VAL[7] = ADC_Bremsdruck();
	ADC_VAL[8] = ADC_Bremsdrucktemperatur();
	ADC_VAL[9] = ADC_STMTemperatur();

	// Auswertung
	#define ADC_OK				"\nADC Value ist in Ordnung\n"
	#define ADC_NOK				"\nADC Value ist nicht in Ordnung\n"

	uartTransmit("KL15: ", 6);
	uartTransmitNumber(ADC_VAL[0], 10);
	if (ADC_VAL[0] > 3030 || ADC_VAL[0] < 2980)						// @12V Versorgungsspannung
		uartTransmit(ADC_NOK, sizeof(ADC_NOK));
	else
		uartTransmit(ADC_OK, sizeof(ADC_OK));

	uartTransmit("\nKühlwasser: ", 14);
	uartTransmitNumber(ADC_VAL[1], 10);
	if (ADC_VAL[1] > 3480 || ADC_VAL[1] < 3455)
		uartTransmit(ADC_NOK, sizeof(ADC_NOK));
	else
		uartTransmit(ADC_OK, sizeof(ADC_OK));

	uartTransmit("\nKlimaFlap: ", 12);
	uartTransmitNumber(ADC_VAL[2], 10);
	if (ADC_VAL[2] > 20)
		uartTransmit(ADC_NOK, sizeof(ADC_NOK));
	else
		uartTransmit(ADC_OK, sizeof(ADC_OK));

	uartTransmit("\nGas: ", 6);
	uartTransmitNumber(ADC_VAL[3], 10);
	if (ADC_VAL[3] > 250 || ADC_VAL[3] < 200)
		uartTransmit(ADC_NOK, sizeof(ADC_NOK));
	else
		uartTransmit(ADC_OK, sizeof(ADC_OK));

	uartTransmit("\nPCB: ", 6);
	uartTransmitNumber(ADC_VAL[4], 10);
	if (ADC_VAL[4] > 2000 || ADC_VAL[4] < 1970)
		uartTransmit(ADC_NOK, sizeof(ADC_NOK));
	else
		uartTransmit(ADC_OK, sizeof(ADC_OK));

	uartTransmit("\nReturn: ", 9);
	uartTransmitNumber(ADC_VAL[5], 10);
	if (ADC_VAL[5] > 3070 || ADC_VAL[5] < 3000)						// Mit Konsolenelement
		uartTransmit(ADC_NOK, sizeof(ADC_NOK));
	else
		uartTransmit(ADC_OK, sizeof(ADC_OK));

	uartTransmit("\nInfo: ", 7);
	uartTransmitNumber(ADC_VAL[6], 10);
	if (ADC_VAL[6] > 3070 || ADC_VAL[6] < 3000)						// Mit Konsolenelement
		uartTransmit(ADC_NOK, sizeof(ADC_NOK));
	else
		uartTransmit(ADC_OK, sizeof(ADC_OK));

	uartTransmit("\nBremsdruck: ", 13);
	uartTransmitNumber(ADC_VAL[7], 10);
	if (ADC_VAL[7] > 1500 || ADC_VAL[7] < 1450)						// @Umgebungsdruck
		uartTransmit(ADC_NOK, sizeof(ADC_NOK));
	else
		uartTransmit(ADC_OK, sizeof(ADC_OK));

	uartTransmit("\nBremstemp: ", 12);
	uartTransmitNumber(ADC_VAL[8], 10);
	if (ADC_VAL[8] > 2300 || ADC_VAL[8] < 2250)						// @Zimmertemperatur
		uartTransmit(ADC_NOK, sizeof(ADC_NOK));
	else
		uartTransmit(ADC_OK, sizeof(ADC_OK));

	uartTransmit("\nSTM Temp: ", 11);
	uartTransmitNumber(ADC_VAL[9], 10);
	if (ADC_VAL[9] > 955 || ADC_VAL[9] < 935)						// Nach 2h Betrieb
		uartTransmit(ADC_NOK, sizeof(ADC_NOK));
	else
		uartTransmit(ADC_OK, sizeof(ADC_OK));

	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);
	HAL_Delay(4500);
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);
    HAL_UART_Receive_IT(&huart2, &UART2_rxBuffer[uart_count], 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  if (UART2_msg[0] == 1)
	  {
		  HAL_UART_Transmit(&huart2, (uint8_t*)"\nSystem Reset\r\n", 15, 100);
		  NVIC_SystemReset();
	  }
	  HAL_Delay(1000);
	  HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Transmit(&huart2, &UART2_rxBuffer[uart_count], 1, 100);

	if (UART2_rxBuffer[uart_count] == 0x7F)
	{
		uart_count--;
	}
	else
	{
		uart_count++;
	}

	if (UART2_rxBuffer[uart_count-1] == '\r')
	{
		HAL_UART_Transmit(&huart2, (uint8_t*)"\nEingabe OK\r\n", 13, 100);
		if (UART2_rxBuffer[0] == 'R' && UART2_rxBuffer[1] == 'E' && UART2_rxBuffer[2] == 'S')
		{
			uint8_t c[10] = {204, 205, 205, 205, 205, 205, 205, 205, 205, 185};
			HAL_UART_Transmit(&huart2, (uint8_t*)"\a", 1, 100);
			HAL_UART_Transmit(&huart2, c, 10, 100);
			UART2_msg[0] = 1;
		}
		uart_count = 0;
	}

	if (uart_count == 12)
	{
		uint8_t tmp = 0x81;
		HAL_UART_Transmit(&huart2, (uint8_t*) "\r\nEingabe Ung", 13, 100);
		HAL_UART_Transmit(&huart2, &tmp, 1, 100);
		HAL_UART_Transmit(&huart2, (uint8_t*) "ltig\r\n", 6, 100);
		uart_count = 0;
	}
    HAL_UART_Receive_IT(&huart2, &UART2_rxBuffer[uart_count], 1);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
