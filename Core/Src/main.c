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
#include "Motorsteuergeraet.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// TODO: OELDRUCKSCHALTER
// FIXME: CAN Bus (CAN-Bus braucht Ablaufprogramm)
// xxx: Schlechte Performance
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

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
	Motor_State mStrg_state = Start;

	uint32_t timeStandby = 0, timeError = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  MX_USART2_UART_Init();

	uartTransmit("Start\n", 6);

#ifdef DEBUG
	app_info();
	HAL_Delay(3000);
#endif
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN3_Init();
  MX_ADC1_Init();
  MX_CAN1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
	leuchten_out.Anhaenger = 1;
	leuchten_out.Niveau = 1;
	HAL_GPIO_WritePin(ANHAENGER_GPIO_Port, ANHAENGER_Pin, leuchten_out.Anhaenger);
	HAL_GPIO_WritePin(NIVEAU_OUT_GPIO_Port, NIVEAU_OUT_Pin, leuchten_out.Niveau);

#ifdef DEBUG
	#define MAINWHILE			"\nStarte While Schleife\n"
	uartTransmit(MAINWHILE, sizeof(MAINWHILE));

	uartTransmit("Ready\n", 6);
#endif

//	CAN_config();
	mStrg_state = Ready;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // Alle Eingaenge einlesen
	  readall_inputs();

	  // Alle ADC einlesen
	  // TODO: ADCs

	  // Shutdown-Circuit checken
	  // checkSDC;

	  if (mStrg_state != Standby)
	  {
		  // TODO: CAN-BUS write Funktion ausfuehren
//		  CANwork();
	  }

	  if (mStrg_state & MotorNormal)
	  {
		  leuchten_out.RedLed = 0;
		  leuchten_out.GreenLed = 1;
	  }

	  if (mStrg_state & MotorWarning)
	  {
		  if (millis() - timeError > 1000)
		  {
			  leuchten_out.RedLed = !leuchten_out.RedLed;
		  }

		  leuchten_out.GreenLed = 1;
	  }

	  if (mStrg_state & MotorError)
	  {
		  if (millis() - timeError > 1000)
		  {
			  leuchten_out.RedLed = !leuchten_out.RedLed;
		  }

		  leuchten_out.GreenLed = 0;
	  }

	  if (mStrg_state & MotorCriticalError)
	  {
		  leuchten_out.RedLed = 1;
		  leuchten_out.GreenLed = 0;
	  }

	  switch (mStrg_state)
	  {
		  case Ready:
		  {
			  // LEDs testen
			  uartTransmit("Testen der PCB und Cockpit LEDs\n", 32);
			  testPCB_Leds();
			  testCockpit_Leds();

			  // Testen der Versorgungsspannung am Shutdown Circuit
			  uartTransmit("Testen der SDC-Sicherung\n", 25);
			  //testSDC();

			  // Alle Fehler am Cockpit loeschen
			  uartTransmit("Cockpit LEDs standardmaessig ausschalten\n", 41);
			  cockpit_default();

			  uartTransmit("KL15\n", 5);
			  mStrg_state = KL15;

			  break;
		  }

		  case KL15:
		  {
			  if (system_in.Anlasser != 1)
			  {
				  if (!(mStrg_state & MotorCriticalError))
				  {
					  uartTransmit("Anlassen\n", 9);
					  mStrg_state = Anlassen;

					  system_out.MotorSDC = 1;
				  }

				  // Pumpe, Vakuumpumpe, Bamocar einschalten
				  // system_out.Gluehkerzen = 1;
			  }

			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  mStrg_state = Standby;
				  timeStandby = millis();
			  }

			  break;
		  }

		  case Anlassen:
		  {
			  if ((system_in.Kupplung != 1) && (system_in.BremseNO != 1) && (system_in.BremseNC == 1))
			  {
				  uartTransmit("Precharge\n", 10);
				  mStrg_state = Precharge;
			  }

			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  mStrg_state = Standby;
				  timeStandby = millis();
			  }

			  break;
		  }

		  case Precharge:
		  {
			  if ((sdc_in.SDC0 != 1) && (sdc_in.BTB_SDC != 1) && (sdc_in.AkkuSDC == 1) && (sdc_in.EmergencyRun == 1))
			  {
				  uartTransmit("ReadyToDrive\n", 13);
				  mStrg_state = ReadyToDrive;
			  }

			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  mStrg_state = Standby;
				  timeStandby = millis();
			  }

			  break;
		  }

		  case ReadyToDrive:
		  {
			  if (system_in.Button2 != 1)
			  {
				  uartTransmit("Drive\n", 6);
				  mStrg_state = Drive;
			  }

			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  mStrg_state = Standby;
				  timeStandby = millis();
			  }

			  break;
		  }

		  case Drive:
		  {
			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  mStrg_state = Standby;
				  timeStandby = millis();
			  }

			  break;
		  }

		  case Standby:
		  {
			  if ((highcurrent_out.Pumpe_Kuhlung == 1) && (millis() - timeStandby > PUMPTIME))
			  {
				  highcurrent_out.Pumpe_Kuhlung = 0;
				  HAL_Delay(10);
				  system_out.Gluehkerzen = 0;
			  }

			  if (millis() - timeStandby > MOTORTIME)
			  {
				  uartTransmit("Ausschalten\n", 12);
				  mStrg_state = Ausschalten;
			  }
			  else if (system_in.KL15 != 1)
			  {
				  uartTransmit("Ready\n", 6);
				  mStrg_state = Ready;
			  }

			  break;
		  }

		  case Ausschalten:
		  {
			  // Alle Ausgaenge ausschalten
			  system_out.systemoutput = 0;
			  highcurrent_out.high_out = 0;
			  leuchten_out.ledoutput = 0;
			  komfort_out.komfortoutput = 0;
			  sdc_in.sdcinput = 0;

			  break;
		  }

		  default:
		  {
			  uartTransmit("Motor Kritischer Fehler\n", 24);
			  mStrg_state = MotorCriticalError;

			  break;
		  }
	  }

	  // Alle Ausgaenge schreiben
	  writeall_outputs();
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

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
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();														// Interrupts deaktivieren

	// Schalte Fehler LED ein
	leuchten_out.RedLed = 1;												// Setze Variable
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);	// Fehler LED einschalten

	// Schalte Ok LED aus
	leuchten_out.GreenLed = 0;												// Zuruechsetzen Variable
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);// Fehler LED ausschalten

	// Sende Nachricht auf Uart-Interface
#ifdef DEBUG
#define STRING_ERROR_HANDLER			"Error Handler wird ausgefuehrt!!!"
	uartTransmit(STRING_ERROR_HANDLER, sizeof(STRING_ERROR_HANDLER));
#endif
	// Beginne Endlosschleife nachdem Fehler aufgetreten ist
	while (1);
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
