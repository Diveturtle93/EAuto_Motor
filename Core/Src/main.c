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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SystemInfo.h"
#include "BasicUart.h"
#include "inputs.h"
#include "outputs.h"
#include "error.h"
#include "Bamocar.h"
#include "millis.h"
#include "Motorsteuergeraet.h"
#include "adc_inputs.h"
#include "pedale.h"
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
CAN_RxHeaderTypeDef RxMessage;
uint8_t RxData[8], can_change = 0;
volatile uint8_t millisekunden_flag_1 = 0;
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

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

	// Definiere Variablen fuer Main-Funktion
	uint8_t TxData[8], OutData[5], InData[5], status, tmp[4];
	uint16_t count = 0, gas_adc, gas_mean = 0;
  	uint32_t lastcan = 0, lastsendcan = 0;

  	// Erstelle Can-Nachrichten
  	CAN_TxHeaderTypeDef TxMessage = {0x123, 0, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE};
  	CAN_TxHeaderTypeDef TxOutput = {MOTOR_CAN_DIGITAL_OUT, 0, CAN_RTR_DATA, CAN_ID_STD, 5, DISABLE};
  	CAN_TxHeaderTypeDef TxInput = {MOTOR_CAN_DIGITAL_IN, 0, CAN_RTR_DATA, CAN_ID_STD, 5, DISABLE};
  	CAN_TxHeaderTypeDef TxMotor1 = {MOTOR_CAN_DREHZAHL, 0, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE};
  	CAN_TxHeaderTypeDef TxBamocar = {BAMOCAR_TX_ID, 0, CAN_RTR_DATA, CAN_ID_STD, 3, DISABLE};


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
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

  	// Start Timer 6 Interrupt
  	HAL_TIM_Base_Start_IT(&htim6);

  	// Schreibe Resetquelle auf die Konsole
#ifdef DEBUG
	printResetSource(readResetSource());

  	/* Teste serielle Schnittstelle*/
  	#define TEST_STRING_UART	"\nUART2 Transmitting in polling mode, Hello Diveturtle93!\n"
  	uartTransmit(TEST_STRING_UART, sizeof(TEST_STRING_UART));

  	// Sammel Systeminformationen
  	collectSystemInfo();
#endif

	// Leds Testen
  	testPCB_Leds();

  	/* Lese alle Eingaenge */
  	readall_inputs();

    // Sendenachricht erstellen
  	/*TxMessage.StdId = 0x123;
  	TxMessage.ExtId = 0;
  	TxMessage.RTR = CAN_RTR_DATA;
  	TxMessage.IDE = CAN_ID_STD;
  	TxMessage.DLC = 8;
  	TxMessage.TransmitGlobalTime=DISABLE;*/

	// Sendenachricht Motorsteuergeraet digitale Ausgaenge erstellen
  	/*TxOutput.StdId = MOTOR_CAN_DIGITAL_OUT;
  	TxOutput.ExtId = 0;
  	TxOutput.RTR = CAN_RTR_DATA;
  	TxOutput.IDE = CAN_ID_STD;
  	TxOutput.DLC = 8;
  	TxOutput.TransmitGlobalTime=DISABLE;*/

	// Sendenachricht Motorsteuergeraet digitale Eingaenge erstellen
  	/*TxInput.StdId = MOTOR_CAN_DIGITAL_IN;
  	TxInput.ExtId = 0;
  	TxInput.RTR = CAN_RTR_DATA;
  	TxInput.IDE = CAN_ID_STD;
  	TxInput.DLC = 8;
  	TxInput.TransmitGlobalTime=DISABLE;*/

	// Sendenachricht Motorsteuergeraet Motor1 erstellen
	/*TxMotor1.StdId = MOTOR_CAN_DREHZAHL;
	TxMotor1.ExtId = 0;
	TxMotor1.RTR = CAN_RTR_DATA;
	TxMotor1.IDE = CAN_ID_STD;
	TxMotor1.DLC = 8;
	TxMotor1.TransmitGlobalTime=DISABLE;*/

  	for (uint8_t j = 0; j < 8; j++)
  		TxData[j] = (j + 1);

  	// Start timer
  	HAL_TIM_Base_Start(&htim6);

//  	// Schreibe BamoCar CAN-Timeout
//  	tmp[0] = 0xd0;
//  	tmp[1] = 0x4f;
//  	tmp[2] = 0x01;
//
//#define BAMOCANTIMEOUT			"\nSetze BamoCar CAN-Timeout Zeit auf 500ms\n"
//  	uartTransmit(BAMOCANTIMEOUT, sizeof(BAMOCANTIMEOUT));
//  	status = HAL_CAN_AddTxMessage(&hcan3, &TxBamocar, tmp, (uint32_t *)CAN_TX_MAILBOX0);
//	hal_error(status);

//  	// Loesche BamoCar Fehler
//  	tmp[0] = 0x8e;
//  	tmp[1] = 0x00;
//  	tmp[2] = 0x00;
//
//#define BAMOCANERROR			"\nSetze Bamocar Fehler zurueck\n"
//  	uartTransmit(BAMOCANERROR, sizeof(BAMOCANERROR));
//  	status = HAL_CAN_AddTxMessage(&hcan3, &TxBamocar, tmp, (uint32_t *)CAN_TX_MAILBOX0);
//	hal_error(status);

  	// Starte While-Schleife
#define MAINWHILE				"\nStarte While Schleife\n"
  	uartTransmit(MAINWHILE, sizeof(MAINWHILE));

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  	// Task wird jede Millisekunde ausgefuehrt
		if (millisekunden_flag_1 == 1)
		{
			count++;													// Zaehler count hochzaehlen
			millisekunden_flag_1 = 0;									// Setze Millisekunden-Flag zurueck
		}

		// Task wird alle 20 Millisekunden ausgefuehrt
		if ((count % 20) == 0)
		{
			// Sende Nachricht Motor1
			status = HAL_CAN_AddTxMessage(&hcan3, &TxMotor1, motor1.output, (uint32_t *)CAN_TX_MAILBOX0);
			hal_error(status);
		}

		// Task wird alle 50 Millisekunden ausgefuehrt
		if ((count % 50) == 0)
		{
		}

		// Task wird alle 100 Millisekunden ausgefuehrt
		if ((count % 100) == 0)
		{
			// alle Inputs einlesen
			readall_inputs();

			// Bremse pruefen
//			readBrake();

			// Gaspedal pruefen
			gas_adc = readTrottle();

			// Mittelwert bilden (https://nestedsoftware.com/2018/03/20/calculating-a-moving-average-on-streaming-data-5a7k.22879.html)
			// Mittelwertbildung aus 10 Werten (Weniger die 10 verkleineren, Mehr die 10 vergrößern)
			gas_mean = (gas_mean + ((gas_adc - gas_mean)/10));

			// Daten in Bamocarformat umwandeln
			tmp[0] = 0x90;
			tmp[1] = (gas_mean);
			tmp[2] = ((gas_mean) >> 8);

			// Drehmoment an Bamocar senden
			status = HAL_CAN_AddTxMessage(&hcan3, &TxBamocar, tmp, (uint32_t *)CAN_TX_MAILBOX0);
			hal_error(status);
		}

		// Task wird alle 200 Millisekunden ausgefuehrt
		if ((count % 200) == 0)
		{
			// Daten fuer Ausgaenge zusammenfuehren
			OutData[0] = system_out.systemoutput;
			OutData[1] = highcurrent_out.high_out;
			OutData[2] = (leuchten_out.ledoutput >> 8);
			OutData[3] = leuchten_out.ledoutput;
			OutData[4] = komfort_out.komfortoutput;

			// Sende Nachricht digitale Ausgaenge
			status = HAL_CAN_AddTxMessage(&hcan3, &TxOutput, OutData, (uint32_t *)CAN_TX_MAILBOX0);
			hal_error(status);

			// Daten fuer Eingaenge zusammenfuehren
			InData[0] = (system_in.systeminput >> 8);
			InData[1] = system_in.systeminput;
			InData[2] = sdc_in.sdcinput;
			InData[3] = (komfort_in.komfortinput >> 8);
			InData[4] = komfort_in.komfortinput;

			// Sende Nachricht digitale Eingaenge
			status = HAL_CAN_AddTxMessage(&hcan3, &TxInput, InData, (uint32_t *)CAN_TX_MAILBOX0);
			hal_error(status);

			// Bamocar Fehler auslesen
			tmp[0] = 0x3D;
			tmp[1] = 0x8F;
			tmp[2] = 0x00;

			// Befehl Fehler auslesen an Bamocar senden
			status = HAL_CAN_AddTxMessage(&hcan3, &TxBamocar, tmp, (uint32_t *)CAN_TX_MAILBOX0);
			hal_error(status);

			// Variable count auf 0 zuruecksetzen
			count = 0;
		}

	  	// Task wird alle 5 Millisekunden ausgefuehrt
	  	if (millis() - lastcan >= 5)
		{
			// Wenn Nachricht ueber den CAN-Bus empfangen wurden
			if (can_change == 1)
			{
				// Nachricht ID über UART ausgeben
				uartTransmitNumber(RxMessage.StdId, 16);
				uartTransmit("\t", 1);
				for (uint8_t i = 0; i < RxMessage.DLC; i++)
				{
					uartTransmitNumber(RxData[i], 16);
				}
				uartTransmit("\n", 1);

				// Sortieren der IDs nach Geräten
				switch (RxMessage.StdId)
				{
					case BAMOCAR_RX_ID:
						BAMOCAN_ID(&RxData[0], RxMessage.DLC);
						break;
					case 0x111:
						uartTransmit("CAN-ID Computer config\n", 23);
						break;
					default:
						uartTransmit("CAN-ID nicht verfuegbar\n", 24);
						break;
				}

				TxData[2] = motor1.output[2];
				TxData[3] = motor1.output[3];
				lastcan = millis();
				can_change = 0;
			}
		}

		// Sende CAN Nachricht auf CAN-Bus
		if (millis() - lastsendcan >= 993)
		{
			status = HAL_CAN_AddTxMessage(&hcan3, &TxMessage, TxData, (uint32_t *)CAN_TX_MAILBOX0);
			hal_error(status);
			lastsendcan = millis();
		}
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// Interrupts
// Can-Interrupt: Nachricht wartet
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	// Nachricht aus Speicher auslesen
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMessage, RxData);
	can_change = 1;
}

// Timer-Interrupt: Timer ist uebergelaufen
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// Kontrolliere welcher Timer den Ueberlauf ausgeloest hat
	if (htim == &htim6)
	{
		millisekunden_flag_1 = 1;
	}
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

  // Schalte Fehler LED ein
  leuchten_out.RedLed = 1;
  HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);

  // Sende Nachricht auf Uart-Interface
#ifdef DEBUG
  #define STRING_ERROR_HANDLER			"Error Handler wird ausgefuehrt!!!"
  uartTransmit(STRING_ERROR_HANDLER, sizeof(STRING_ERROR_HANDLER));
#endif
  // Beginne Endlosschleife nachdem Fehler aufgetreten ist
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
