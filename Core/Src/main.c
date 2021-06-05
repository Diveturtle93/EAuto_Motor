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
  	#define TEST_STRING_UART	"\nUART3 Transmitting in polling mode, Hello Diveturtle93!\n"
  	uartTransmit(TEST_STRING_UART, sizeof(TEST_STRING_UART));

  	/* Sammel Systeminformationen */
  	collectSystemInfo();
#endif

  	// Leds Testen
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
  	readall_inputs();

	#define TASTERPRESSED		"Taster betaetigt, Not OK\n"
	#define TASTERNOTPRESSED	"Taster nicht betaetigt, OK\n"

  	#define SYSTEMIN			"\n\nSystem Eingaenge\n\n"
  	uartTransmit(SYSTEMIN, sizeof(SYSTEMIN));

	#define STRINGKICKDOWN		"Test Kickdown, default = 0\n"
  	uartTransmit(STRINGKICKDOWN, sizeof(STRINGKICKDOWN));
  	if(system_in.Kickdown == 1)
  		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGLEERLAUF		"Test Leerlauf, default = 0\n"
	uartTransmit(STRINGLEERLAUF, sizeof(STRINGLEERLAUF));
	if(system_in.Leerlauf == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
	uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBREMSENO		"Test Bremse normally open, default = 1\n"
	uartTransmit(STRINGBREMSENO, sizeof(STRINGBREMSENO));
	if(system_in.BremseNO != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBREMSENC		"Test Bremse normally connect, default = 0\n"
	uartTransmit(STRINGBREMSENC, sizeof(STRINGBREMSENC));
	if(system_in.BremseNC == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGKUPPLUNG		"Test Kupplung, default = 1\n"
	uartTransmit(STRINGKUPPLUNG, sizeof(STRINGKUPPLUNG));
	if(system_in.Kupplung != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGRECUPERATION	"Test Recuperation, default = 1\n"
	uartTransmit(STRINGRECUPERATION, sizeof(STRINGRECUPERATION));
	if(system_in.Recuperation != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGECON			"Test ECON, default = 0\n"
	uartTransmit(STRINGECON, sizeof(STRINGECON));
	if(system_in.ECON != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGANLASSER		"Test Anlasser, default = 1\n"
	uartTransmit(STRINGANLASSER, sizeof(STRINGANLASSER));
	if(system_in.Anlasser != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGKL15			"Test KL15, default = 1\n"
	uartTransmit(STRINGKL15, sizeof(STRINGKL15));
	if(system_in.KL15 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGDCDCINST		"Test DCDC_Inst, default = 0\n"
	uartTransmit(STRINGDCDCINST, sizeof(STRINGDCDCINST));
	if(system_in.DCDC_Inst == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBUTTON1		"Test Button1, default = 1\n"
	uartTransmit(STRINGBUTTON1, sizeof(STRINGBUTTON1));
	if(system_in.Button1 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBUTTON2		"Test Button2, default = 1\n"
	uartTransmit(STRINGBUTTON2, sizeof(STRINGBUTTON2));
	if(system_in.Button2 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGCRASH			"Test Crash, default = 0\n"
	uartTransmit(STRINGCRASH, sizeof(STRINGCRASH));
	if(system_in.Crash == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGWAKEUP		"Test Wakeup, default = 0\n"
	uartTransmit(STRINGWAKEUP, sizeof(STRINGWAKEUP));
	if(system_in.Wakeup == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBREMSDRUCKNO	"Test Bremsdruck normally open, default = 0\n"
	uartTransmit(STRINGBREMSDRUCKNO, sizeof(STRINGBREMSDRUCKNO));
	if(system_in.Bremsdruck_NO == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBREMSDRUCKNC	"Test Bremsdruck normally connect, default = 0\n"
	uartTransmit(STRINGBREMSDRUCKNC, sizeof(STRINGBREMSDRUCKNC));
	if(system_in.Bremsdruck_NC == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define KOMFORTIN			"\n\nKomfort Eingaenge\n\n"
  	uartTransmit(KOMFORTIN, sizeof(KOMFORTIN));

	#define STRINGASR1			"Test ASR1, default = 0\n"
  	uartTransmit(STRINGASR1, sizeof(STRINGASR1));
  	if(komfort_in.ASR1 == 1)
  		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGASR2			"Test ASR2, default = 0\n"
	uartTransmit(STRINGASR1, sizeof(STRINGASR1));
	if(komfort_in.ASR2 == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
	uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGECO			"Test ECO, default = 0\n"
	uartTransmit(STRINGECO, sizeof(STRINGECO));
	if(komfort_in.ECO == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBCRSTIN		"Test BC_Rst_In, default = 0\n"
	uartTransmit(STRINGBCRSTIN, sizeof(STRINGBCRSTIN));
	if(komfort_in.BC_Rst_In == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBCUPIN		"Test BC_Up_In, default = 0\n"
	uartTransmit(STRINGBCUPIN, sizeof(STRINGBCUPIN));
	if(komfort_in.BC_Up_In == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBCDOWNIN		"Test BC_Down_In, default = 0\n"
	uartTransmit(STRINGBCDOWNIN, sizeof(STRINGBCDOWNIN));
	if(komfort_in.BC_Down_In == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBAMOIN1		"Test BamoIn1, default = 1\n"
	uartTransmit(STRINGBAMOIN1, sizeof(STRINGBAMOIN1));
	if(komfort_in.BamoIn1 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBAMOIN2		"Test BamoIn2, default = 1\n"
	uartTransmit(STRINGBAMOIN2, sizeof(STRINGBAMOIN2));
	if(komfort_in.BamoIn2 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGENTER			"Test Enter, default = 0\n"
	uartTransmit(STRINGENTER, sizeof(STRINGENTER));
	if(komfort_in.Enter == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGOUTA			"Test OutB, default = 0\n"
	uartTransmit(STRINGOUTA, sizeof(STRINGOUTA));
	if(komfort_in.OutA == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGOUTB			"Test OutB, default = 0\n"
	uartTransmit(STRINGOUTB, sizeof(STRINGOUTB));
	if(komfort_in.OutB == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGGRA1			"Test GRA1, default = 0\n"
	uartTransmit(STRINGGRA1, sizeof(STRINGGRA1));
	if(komfort_in.GRA1 == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGGRA2			"Test GRA2, default = 0\n"
	uartTransmit(STRINGGRA2, sizeof(STRINGGRA2));
	if(komfort_in.GRA2 == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGGRA3			"Test GRA3, default = 0\n"
	uartTransmit(STRINGGRA3, sizeof(STRINGGRA3));
	if(komfort_in.GRA3 == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGGRA4			"Test GRA4, default = 0\n"
	uartTransmit(STRINGGRA4, sizeof(STRINGGRA4));
	if(komfort_in.GRA4 == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGDURCHFLUSS	"Test Durchfluss, default = 1\n"
	uartTransmit(STRINGDURCHFLUSS, sizeof(STRINGDURCHFLUSS));
	if(komfort_in.Durchfluss != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define PEDALIN				"\n\nPedal Eingaenge\n\n"
	uartTransmit(PEDALIN, sizeof(PEDALIN));

	#define STRINGEMERGENCY		"Test Emergency Run, default = 1\n"
	uartTransmit(STRINGEMERGENCY, sizeof(STRINGEMERGENCY));
	if(sdc_in.EmergencyRun != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGSDC0			"Test SDC0, default = 1\n"
	uartTransmit(STRINGSDC0, sizeof(STRINGSDC0));
	if(sdc_in.SDC0 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
	uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGAKKUSDC		"Test Akku SDC, default = 1\n"
	uartTransmit(STRINGAKKUSDC, sizeof(STRINGAKKUSDC));
	if(sdc_in.AkkuSDC != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGBTBSDC		"Test BTB SDC, default = 1\n"
	uartTransmit(STRINGBTBSDC, sizeof(STRINGBTBSDC));
	if(sdc_in.BTB_SDC != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define STRINGDCDCFAULT		"Test DCDC Fault, default = 1\n"
	uartTransmit(STRINGDCDCFAULT, sizeof(STRINGDCDCFAULT));
	if(sdc_in.DCDC_Fault != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));







  	/*if (system_in != SYSTEM_INPUT)
  		Error_Handler();
  	if (sdc_in != SDC_INPUT)
  		Error_Handler();
  	if (komfort_in != KOMFORT_INPUT)
  		Error_Handler();*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

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
  HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET);
#ifdef DEBUG
#define ERRORMESSAGE			"\nError Handler ausgeloest\n"
  uartTransmit(ERRORMESSAGE,sizeof(ERRORMESSAGE));
#endif
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
