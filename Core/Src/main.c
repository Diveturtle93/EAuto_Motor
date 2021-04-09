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

	#define TESTKICKDOWN		"Test Kickdown, default = 0\n"
  	uartTransmit(TESTKICKDOWN, sizeof(TESTKICKDOWN));
  	if(system_in.Kickdown == 1)
  		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTLEERLAUF		"Test Leerlauf, default = 0\n"
	uartTransmit(TESTLEERLAUF, sizeof(TESTLEERLAUF));
	if(system_in.Leerlauf == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
	uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBREMSENO		"Test Bremse normally open, default = 1\n"
	uartTransmit(TESTBREMSENO, sizeof(TESTBREMSENO));
	if(system_in.BremseNO != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBREMSENC		"Test Bremse normally connect, default = 0\n"
	uartTransmit(TESTBREMSENC, sizeof(TESTBREMSENC));
	if(system_in.BremseNC == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTKUPPLUNG		"Test Kupplung, default = 1\n"
	uartTransmit(TESTKUPPLUNG, sizeof(TESTKUPPLUNG));
	if(system_in.Kupplung != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTRECUPERATION	"Test Recuperation, default = 1\n"
	uartTransmit(TESTRECUPERATION, sizeof(TESTRECUPERATION));
	if(system_in.Recuperation != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTECON			"Test ECON, default = 0\n"
	uartTransmit(TESTECON, sizeof(TESTECON));
	if(system_in.ECON != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTANLASSER		"Test Anlasser, default = 1\n"
	uartTransmit(TESTANLASSER, sizeof(TESTANLASSER));
	if(system_in.Anlasser != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTKL15			"Test KL15, default = 1\n"
	uartTransmit(TESTKL15, sizeof(TESTKL15));
	if(system_in.KL15 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTDCDCINST		"Test DCDC_Inst, default = 0\n"
	uartTransmit(TESTDCDCINST, sizeof(TESTDCDCINST));
	if(system_in.DCDC_Inst == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBUTTON1			"Test Button1, default = 1\n"
	uartTransmit(TESTBUTTON1, sizeof(TESTBUTTON1));
	if(system_in.Button1 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBUTTON2			"Test Button2, default = 1\n"
	uartTransmit(TESTBUTTON2, sizeof(TESTBUTTON2));
	if(system_in.Button2 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTCRASH			"Test Crash, default = 0\n"
	uartTransmit(TESTCRASH, sizeof(TESTCRASH));
	if(system_in.Crash == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTWAKEUP			"Test Wakeup, default = 0\n"
	uartTransmit(TESTWAKEUP, sizeof(TESTWAKEUP));
	if(system_in.Wakeup == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBREMSDRUCKNO	"Test Bremsdruck normally open, default = 0\n"
	uartTransmit(TESTBREMSDRUCKNO, sizeof(TESTBREMSDRUCKNO));
	if(system_in.Bremsdruck_NO == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBREMSDRUCKNC	"Test Bremsdruck normally connect, default = 0\n"
	uartTransmit(TESTBREMSDRUCKNC, sizeof(TESTBREMSDRUCKNC));
	if(system_in.Bremsdruck_NC == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define KOMFORTIN			"\n\nKomfort Eingaenge\n\n"
  	uartTransmit(KOMFORTIN, sizeof(KOMFORTIN));

	#define TESTASR1			"Test ASR1, default = 0\n"
  	uartTransmit(TESTASR1, sizeof(TESTASR1));
  	if(komfort_in.ASR1 == 1)
  		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTASR2			"Test ASR2, default = 0\n"
	uartTransmit(TESTASR1, sizeof(TESTASR1));
	if(komfort_in.ASR2 == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
	uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTECO				"Test ECO, default = 0\n"
	uartTransmit(TESTECO, sizeof(TESTECO));
	if(komfort_in.ECO == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBCRSTIN			"Test BC_Rst_In, default = 0\n"
	uartTransmit(TESTBCRSTIN, sizeof(TESTBCRSTIN));
	if(komfort_in.BC_Rst_In == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBCUPIN			"Test BC_Up_In, default = 0\n"
	uartTransmit(TESTBCUPIN, sizeof(TESTBCUPIN));
	if(komfort_in.BC_Up_In == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBCDOWNIN		"Test BC_Down_In, default = 0\n"
	uartTransmit(TESTBCDOWNIN, sizeof(TESTBCDOWNIN));
	if(komfort_in.BC_Down_In == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBAMOIN1			"Test BamoIn1, default = 1\n"
	uartTransmit(TESTBAMOIN1, sizeof(TESTBAMOIN1));
	if(komfort_in.BamoIn1 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBAMOIN2			"Test BamoIn2, default = 1\n"
	uartTransmit(TESTBAMOIN2, sizeof(TESTBAMOIN2));
	if(komfort_in.BamoIn2 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTENTER			"Test Enter, default = 0\n"
	uartTransmit(TESTENTER, sizeof(TESTENTER));
	if(komfort_in.Enter == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTOUTA			"Test OutB, default = 0\n"
	uartTransmit(TESTOUTA, sizeof(TESTOUTA));
	if(komfort_in.OutA == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTOUTB			"Test OutB, default = 0\n"
	uartTransmit(TESTOUTB, sizeof(TESTOUTB));
	if(komfort_in.OutB == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTGRA1			"Test GRA1, default = 0\n"
	uartTransmit(TESTGRA1, sizeof(TESTGRA1));
	if(komfort_in.GRA1 == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTGRA2			"Test GRA2, default = 0\n"
	uartTransmit(TESTGRA2, sizeof(TESTGRA2));
	if(komfort_in.GRA2 == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTGRA3			"Test GRA3, default = 0\n"
	uartTransmit(TESTGRA3, sizeof(TESTGRA3));
	if(komfort_in.GRA3 == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTGRA4			"Test GRA4, default = 0\n"
	uartTransmit(TESTGRA4, sizeof(TESTGRA4));
	if(komfort_in.GRA4 == 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTDURCHFLUSS		"Test Durchfluss, default = 1\n"
	uartTransmit(TESTDURCHFLUSS, sizeof(TESTDURCHFLUSS));
	if(komfort_in.Durchfluss != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define PEDALIN				"\n\nPedal Eingaenge\n\n"
	uartTransmit(PEDALIN, sizeof(PEDALIN));

	#define TESTEMERGENCY		"Test Emergency Run, default = 1\n"
	uartTransmit(TESTEMERGENCY, sizeof(TESTEMERGENCY));
	if(sdc_in.EmergencyRun != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTSDC0			"Test SDC0, default = 1\n"
	uartTransmit(TESTSDC0, sizeof(TESTSDC0));
	if(sdc_in.SDC0 != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
	uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTAKKUSDC			"Test Akku SDC, default = 1\n"
	uartTransmit(TESTAKKUSDC, sizeof(TESTAKKUSDC));
	if(sdc_in.AkkuSDC != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTBTBSDC			"Test BTB SDC, default = 1\n"
	uartTransmit(TESTBTBSDC, sizeof(TESTBTBSDC));
	if(sdc_in.BTB_SDC != 1)
		uartTransmit(TASTERPRESSED, sizeof(TASTERPRESSED));
	else
		uartTransmit(TASTERNOTPRESSED, sizeof(TASTERNOTPRESSED));

	#define TESTDCDCFAULT		"Test DCDC Fault, default = 1\n"
	uartTransmit(TESTDCDCFAULT, sizeof(TESTDCDCFAULT));
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
