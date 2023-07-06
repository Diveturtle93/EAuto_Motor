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
int32_t temperature;
CAN_RxHeaderTypeDef RxMessage;
uint8_t UART2_rxBuffer[12] = {0};
uint8_t UART2_msg[12] = {0};
uint8_t uart_count = 0;
uint8_t RxData[8];
volatile uint8_t millisekunden_flag_1 = 0, can_change = 0;
motor1_tag motor1;																	// Variable fuer Motor CAN-Nachricht 1 definieren
motor2_tag motor2;																	// Variable fuer Motor CAN-Nachricht 2 definieren
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

	// Definiere Variablen fuer Main-Funktion
	uint8_t TxData[8], OutData[6] = {0}, InData[6] = {0}, AnalogData[8] = {0}, TempData[8] = {0};
	uint8_t status, tmp[4] = {0}, tmp_Lenkung[4] = {0}, task = 0, heizung = 0;
	uint16_t count = 0, gas_adc = 0, gas_mean = 0;
  	uint32_t lastcan = 0, lastsendcan = 0;
  	static Motor_State statemaschine = Start;

  	// Erstelle Can-Nachrichten
    // Sendenachricht erstellen
  	CAN_TxHeaderTypeDef TxMessage = {0x123, 0, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE};
	// Sendenachricht Motorsteuergeraet digitale Ausgaenge erstellen
  	CAN_TxHeaderTypeDef TxOutput = {MOTOR_CAN_DIGITAL_OUT, 0, CAN_RTR_DATA, CAN_ID_STD, 6, DISABLE};
	// Sendenachricht Motorsteuergeraet digitale Eingaenge erstellen
  	CAN_TxHeaderTypeDef TxInput = {MOTOR_CAN_DIGITAL_IN, 0, CAN_RTR_DATA, CAN_ID_STD, 6, DISABLE};
	// Sendenachricht Motorsteuergeraet Motor1 erstellen
  	CAN_TxHeaderTypeDef TxMotor1 = {MOTOR_CAN_DREHZAHL, 0, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE};
  	// Sendenachricht Motorsteuergeraet an Bamocar erstellen
  	CAN_TxHeaderTypeDef TxBamocar = {BAMOCAR_TX_ID, 0, CAN_RTR_DATA, CAN_ID_STD, 3, DISABLE};
  	// Sendenachricht Motorsteuergeraet an Bamocar erstellen
  	CAN_TxHeaderTypeDef TxLenkung = {LENKUNG1_CAN, 0, CAN_RTR_DATA, CAN_ID_STD, 3, DISABLE};
	// Sendenachricht Motorsteuergeraet analoge Eingaenge erstellen
  	CAN_TxHeaderTypeDef TxAnalog = {MOTOR_CAN_ANALOG_IN, 0, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE};
  	// Sendenachricht Motorsteuergeraet Temperatur Eingaenge erstellen
  	CAN_TxHeaderTypeDef TxTemperatur = {MOTOR_CAN_TEMPERATUR, 0, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE};

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
  MX_CAN1_Init();
  /* USER CODE BEGIN 2 */

  // ITM HCLK
  ITM_SendChar('H');
  ITM_SendChar('a');
  ITM_SendChar('l');
  ITM_SendChar('l');
  ITM_SendChar('o');
  ITM_SendChar(' ');
  	// Start Timer 6 Interrupt
  	HAL_TIM_Base_Start_IT(&htim6);
  	HAL_UART_Receive_IT(&huart2, &UART2_rxBuffer[uart_count], 1);

  	// Schreibe Resetquelle auf die Konsole
#ifdef DEBUG
	printResetSource(readResetSource());

  	// Teste serielle Schnittstelle
  	#define WILLKOMM_STRING_UART	"\nUART2 Transmitting in polling mode, Hello Diveturtle93!\n"
  	uartTransmit(WILLKOMM_STRING_UART, sizeof(WILLKOMM_STRING_UART));
	#define VERSION_STRING_UART		"Starting Application "
	uartTransmit(VERSION_STRING_UART, sizeof(VERSION_STRING_UART));
	uartTransmitNumber(MAJOR, 10);
	uartTransmit(".", 1);
	uartTransmitNumber(MINOR, 10);
	uartTransmit("\n", 1);

  	// Sammel Systeminformationen
  	collectSystemInfo();
#endif

	// Leds Testen
//  testPCB_Leds();
//	testCockpit_Leds();

  	// Testen der Versorgungsspannung am Shutdown-Circuit
  	testSDC();

  	// Alle Fehler Cockpit loeschen
  	cockpit_default();
  	// Setze LED Green
  	leuchten_out.GreenLed = 1;
  	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);

  	// Lese alle Eingaenge
  	readall_inputs();

    // Sendenachricht 0x123 mit Dummy-Daten fuellen
  	for (uint8_t j = 0; j < 8; j++)
  		TxData[j] = (j + 1);

  	// Starte While-Schleife
#define MAINWHILE				"\nStarte While Schleife\n"
  	uartTransmit(MAINWHILE, sizeof(MAINWHILE));


  	if (statemaschine == Start)
  	{
  		statemaschine = Ready;
  		uartTransmit("Ready\n", 6);

  		system_out.F18 = 1;
  		system_out.F54 = 1;
  	}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
			else if (UART2_rxBuffer[0] == 'O' && UART2_rxBuffer[1] == 'E' && UART2_rxBuffer[2] == 'L')
			{
				uartTransmit("Display Oel\r\n", 13);
				leuchten_out.Oeldruck = !leuchten_out.Oeldruck;
				leuchten_out.GreenLed = leuchten_out.Oeldruck;
			}
			else if (UART2_rxBuffer[0] == 'W' && UART2_rxBuffer[1] == 'I' && UART2_rxBuffer[2] == 'S')
			{
				uartTransmit("Display Wisch\r\n", 15);
				leuchten_out.Wischwarn = !leuchten_out.Wischwarn;
			}
			else if (UART2_rxBuffer[0] == 'B' && UART2_rxBuffer[1] == 'R' && UART2_rxBuffer[2] == 'E')
			{
				uartTransmit("Display Brems\r\n", 15);
				leuchten_out.Bremswarn = !leuchten_out.Bremswarn;
			}
			else if (UART2_rxBuffer[0] == 'R' && UART2_rxBuffer[1] == 'U' && UART2_rxBuffer[2] == 'C')
			{
				uartTransmit("Display Rueck\r\n", 15);
				leuchten_out.Rueckwarn = !leuchten_out.Rueckwarn;
			}
			else if (UART2_rxBuffer[0] == 'B' && UART2_rxBuffer[1] == 'U' && UART2_rxBuffer[2] == 'P')
			{
				uartTransmit("BC Up\r\n", 7);
				UART2_msg[0] = 2;
			}
			else if (UART2_rxBuffer[0] == 'B' && UART2_rxBuffer[1] == 'D' && UART2_rxBuffer[2] == 'O')
			{
				uartTransmit("BC Down\r\n", 9);
				UART2_msg[0] = 3;
			}
			else if (UART2_rxBuffer[0] == 'B' && UART2_rxBuffer[1] == 'R' && UART2_rxBuffer[2] == 'S')
			{
				uartTransmit("BC Reset\r\n", 10);
				UART2_msg[0] = 4;
			}
			else
			{
				uint8_t c[10] = {204, 205, 205, 205, 205, 205, 205, 205, 205, 185};
				HAL_UART_Transmit(&huart2, (uint8_t*)"\a", 1, 100);
				HAL_UART_Transmit(&huart2, c, 10, 100);
				uartTransmit("Falsche Eingabe\r\n", 17);
			}
			uart_count = 0;
		}

	  	switch (UART2_msg[0])
	  	{
	  		case 1:
				HAL_UART_Transmit(&huart2, (uint8_t*)"\nSystem Reset\r\n", 15, 100);
				NVIC_SystemReset();
			break;
	  		case 2:
	  			komfort_out.BC_Up_Out = !komfort_out.BC_Up_Out;
	  			HAL_GPIO_WritePin(BC_UP_OUT_GPIO_Port, BC_UP_OUT_Pin, komfort_out.BC_Up_Out);
	  			UART2_msg[0] = 0;
			break;
	  		case 3:
	  			komfort_out.BC_Down_Out = !komfort_out.BC_Down_Out;
	  			HAL_GPIO_WritePin(BC_DOWN_OUT_GPIO_Port, BC_DOWN_OUT_Pin, komfort_out.BC_Down_Out);
	  			UART2_msg[0] = 0;
	  		break;
	  		case 4:
	  			komfort_out.BC_Rst_Out = !komfort_out.BC_Rst_Out;
	  			HAL_GPIO_WritePin(BC_RESET_OUT_GPIO_Port, BC_RESET_OUT_Pin, komfort_out.BC_Rst_Out);
	  			UART2_msg[0] = 0;
	  		break;
			default:
			break;
		}

	  	// Statemaschine
	  	if ((statemaschine == Ready) && (system_in.KL15 != 1))
	  	{
	  		statemaschine = KL15;
	  		leuchten_out.Niveau = 1;
	  		leuchten_out.Anhaenger = 1;
	  		uartTransmit("KL15\n", 5);
	  	}

	  	if ((statemaschine == KL15) && (system_in.KL15 == 1))
	  	{
	  		statemaschine = Ausschalten;
	  		uartTransmit("Ausschalten\n", 12);
	  	}

	  	if ((statemaschine == KL15) && (system_in.Anlasser != 1))
	  	{
	  		statemaschine = Anlasser;
	  		leuchten_out.Buzzer = 1;
	  		uartTransmit("Anlasser\n", 9);
	  		HAL_Delay(250);
	  		leuchten_out.Buzzer = 0;
	  		leuchten_out.Niveau = 0;
	  		leuchten_out.Anhaenger = 0;
	  	}

	  	if ((statemaschine == Anlasser) && (system_in.KL15 == 1))
	  	{
	  		statemaschine = Ausschalten;
	  		uartTransmit("Ausschalten\n", 12);
	  	}

	  	if ((statemaschine == Anlasser) && (system_in.BremseNO == 1) && (system_in.BremseNC == 1))
	  	{
	  		statemaschine = ReadyToDrive;
	  		sdc_in.Anlasser = 1;
	  		uartTransmit("ReadyToDrive\n", 13);
	  	}

	  	if ((statemaschine == ReadyToDrive) && (system_in.KL15 == 1))
	  	{
	  		statemaschine = Ausschalten;
	  		uartTransmit("Ausschalten\n", 12);

	  		sdc_in.Anlasser = 0;
	  	}

	  	if (statemaschine == MotorWarning)
	  	{

	  	}

	  	if (statemaschine == MotorError)
	  	{

	  	}

	  	if (statemaschine == CriticalError)
	  	{

	  	}

	  	if (statemaschine == Ausschalten)
	  	{
	  		// Alle Ausgaenge auf Null setzen
	  		system_out.systemoutput = 0;
	  		highcurrent_out.high_out = 0;
	  		komfort_out.komfortoutput = 0;
	  		leuchten_out.ledoutput = 0;

	  		// xxx Loeschen falls es reicht alle Ausgaenge auf einmal auf Null zu setzen
//	  		system_out.F18 = 0;
//	  		system_out.F54 = 0;
//	  		system_out.MotorSDC = 0;
//	  		sdc_in.SDC12V = 0;
//	  		komfort_out.BC_Down_Out = 0;
//	  		komfort_out.BC_Rst_Out = 0;
//	  		komfort_out.BC_Up_Out = 0;
//	  		komfort_out.BamoOut1 = 0;
//	  		komfort_out.BamoOut2 = 0;
		}

		// PWM Oelstandsensor Kombiinstrument ausgeben
		pwm_oelstand(count);

		// Ausgaenge setzen
		writeall_outputs();

	  	// Task wird jede Millisekunde ausgefuehrt
		if (millisekunden_flag_1 == 1)
		{
			count++;																	// Zaehler count hochzaehlen
			millisekunden_flag_1 = 0;													// Setze Millisekunden-Flag zurueck

			// Setze Flag start, nur wenn millisekunden Flag gesetzt war
			task = 1;
		}

		// Task wird alle 20 Millisekunden ausgefuehrt
		if (((count % 20) == 0) && (task == 1))
		{
			while (HAL_CAN_IsTxMessagePending(&hcan3, CAN_TX_MAILBOX0) == 1);
			// Sende Nachricht Motor1
			status = HAL_CAN_AddTxMessage(&hcan3, &TxMotor1, motor1.output, (uint32_t *)CAN_TX_MAILBOX0);
			tmp_Lenkung[0] = 0;
			tmp_Lenkung[1] = 1;

			while (HAL_CAN_IsTxMessagePending(&hcan3, CAN_TX_MAILBOX0) == 1);
			status = HAL_CAN_AddTxMessage(&hcan3, &TxLenkung, tmp_Lenkung, (uint32_t *)CAN_TX_MAILBOX0);
			hal_error(status);
		}

		if (((count % 220) == 0) && (task == 1))
		{
			// Bamocar Fehler auslesen
			tmp[0] = 0x3D;
			tmp[1] = 0x8F;
			tmp[2] = 0x00;

			while (HAL_CAN_IsTxMessagePending(&hcan3, CAN_TX_MAILBOX0) == 1);
			// Befehl Fehler auslesen an Bamocar senden
			status = HAL_CAN_AddTxMessage(&hcan3, &TxBamocar, tmp, (uint32_t *)CAN_TX_MAILBOX0);
			//hal_error(status);
		}

		// Task wird alle 100 Millisekunden ausgefuehrt
		if (((count % 100) == 0) && (task == 1))
		{
			// alle Inputs einlesen
			readall_inputs();

			// Anlasser abfragen
			readAnlasser();

			// Bremse pruefen
			//readBrake();

			if (statemaschine == ReadyToDrive)
			{
				// Gaspedal pruefen
				gas_adc = readTrottle();

				// TODO Wenn Kupplung dann auch gas_mean auf 0 setzen

				// Abfrage ob Mittelwertbildung
				if (gas_adc > 0)															// Wenn Gaspedal Plausible dann Mittelwertbildung
				{
					// Mittelwert bilden (https://nestedsoftware.com/2018/03/20/calculating-a-moving-average-on-streaming-data-5a7k.22879.html)
					// Mittelwertbildung aus 10 Werten (Weniger die 10 verkleineren, Mehr die 10 vergroeßern)
					gas_mean = (gas_mean + ((gas_adc - gas_mean)/10));
				}
				else																		// Wenn Gaspedal unplausible oder Kupplung getreten
				{
					gas_mean = 0;
				}

				// Daten in Bamocarformat umwandeln
				tmp[0] = 0x90;
				tmp[1] = (gas_mean);
				tmp[2] = ((gas_mean) >> 8);
			}

			if (system_in.Crash != 1)
			{
				uartTransmit("Crash ausgeloest!!!\n", 20);
				statemaschine = CriticalError;
				system_out.MotorSDC = 0;
				sdc_in.Anlasser = 0;
				leuchten_out.RedLed = 1;
				leuchten_out.GreenLed = 0;

				tmp[0] = 0x90;
				tmp[1] = 0;
				tmp[2] = 0;
			}

			if (sdc_in.BTB_SDC != 1)
			{
				uartTransmit("BTB Fehler!!!\n", 14);
				statemaschine = MotorError;
				sdc_in.Anlasser = 0;

				leuchten_out.RedLed = 1;
				leuchten_out.GreenLed = 0;
		  		highcurrent_out.Pumpe_Bremse = 1;
			}

			if (sdc_in.EmergencyRun != 1)
			{
				uartTransmit("Emergency Run ausgeloest!!!\n", 28);
				statemaschine = MotorError;

				leuchten_out.RedLed = 1;
				leuchten_out.GreenLed = 0;

				gas_mean = gas_mean/10;

				tmp[0] = 0x90;
				tmp[1] = (gas_mean);
				tmp[2] = ((gas_mean) >> 8);
			}

			if (sdc_in.Akku1SDC != 1)
			{
				uartTransmit("Akku SDC Fehler erkannt!!!\n", 27);
				statemaschine = MotorWarning;

				leuchten_out.RedLed = 1;
				leuchten_out.GreenLed = 1;

				gas_mean = gas_mean/10;

				tmp[0] = 0x90;
				tmp[1] = (gas_mean);
				tmp[2] = ((gas_mean) >> 8);
			}

			while (HAL_CAN_IsTxMessagePending(&hcan3, CAN_TX_MAILBOX0) == 1);
			// Drehmoment an Bamocar senden
			status = HAL_CAN_AddTxMessage(&hcan3, &TxBamocar, tmp, (uint32_t *)CAN_TX_MAILBOX0);
			//hal_error(status);
		}

		// Task wird alle 200 Millisekunden ausgefuehrt
		if (((count % 200) == 0) && (task == 1))
		{
			// Daten fuer Ausgaenge zusammenfuehren
			OutData[0] = system_out.systemoutput;
			OutData[1] = highcurrent_out.high_out;
			OutData[2] = (leuchten_out.ledoutput >> 8);
			OutData[3] = leuchten_out.ledoutput;
			OutData[4] = komfort_out.komfortoutput;
			OutData[5] ++;

			while (HAL_CAN_IsTxMessagePending(&hcan3, CAN_TX_MAILBOX0) == 1);
			// Sende Nachricht digitale Ausgaenge
			status = HAL_CAN_AddTxMessage(&hcan3, &TxOutput, OutData, (uint32_t *)CAN_TX_MAILBOX0);
			//hal_error(status);

			// ADC-Werte einlesen Bremse und Temperaturen
			ADC_VAL[0] = ADC_Bremsdruck();
			ADC_VAL[1] = ADC_Bremsdrucktemperatur();
			ADC_VAL[2] = ADC_STMTemperatur();
			ADC_VAL[3] = ADC_PCBTemperatur();

			// Daten fuer Eingaenge zusammenfuehren
			InData[0] ++;
			InData[1] = (system_in.systeminput >> 8);
			InData[2] = system_in.systeminput;
			InData[3] = sdc_in.sdcinput;
			InData[4] = (komfort_in.komfortinput >> 8);
			InData[5] = komfort_in.komfortinput;

			while (HAL_CAN_IsTxMessagePending(&hcan3, CAN_TX_MAILBOX0) == 1);
			// Sende Nachricht digitale Eingaenge
			status = HAL_CAN_AddTxMessage(&hcan3, &TxInput, InData, (uint32_t *)CAN_TX_MAILBOX0);
			//hal_error(status);

			// ADC-Werte einlesen Navi, Klima, KL15
			ADC_VAL[4] = ADC_KL15();
			ADC_VAL[5] = ADC_Klimaflap();
			ADC_VAL[6] = ADC_Info();
			ADC_VAL[7] = ADC_Return();

			// ADC-Werte umwandeln
			AnalogData[0] = ADC_VAL[4];
			AnalogData[1] = (ADC_VAL[4] >> 8) | (ADC_VAL[0] << 4);
			AnalogData[2] = (ADC_VAL[0] >> 4);
			AnalogData[3] = gas_mean;
			AnalogData[4] = (gas_mean >> 8) | (ADC_VAL[6] << 4);
			AnalogData[5] = (ADC_VAL[6] >> 4);
			AnalogData[6] = ADC_VAL[7];
			AnalogData[7] = (ADC_VAL[7] >> 8);

			// ADC-Werte einlesen Kuehlwassertemperatur
			ADC_VAL[8] = ADC_Kuhlwassertemperatur();

			// ADC-Werte umwandeln
			TempData[0] = ADC_VAL[2];
			TempData[1] = (ADC_VAL[2] >> 8) | (ADC_VAL[3] << 4);
			TempData[2] = (ADC_VAL[3] >> 4);
			TempData[3] = ADC_VAL[8];
			TempData[4] = (ADC_VAL[8] >> 8) | (ADC_VAL[1] << 4);
			TempData[5] = (ADC_VAL[1] >> 4);
			TempData[6] = ADC_VAL[5];
			TempData[7] = (ADC_VAL[5] >> 8);

			while (HAL_CAN_IsTxMessagePending(&hcan3, CAN_TX_MAILBOX0) == 1);
			// Befehl Fehler auslesen an Bamocar senden
			status = HAL_CAN_AddTxMessage(&hcan3, &TxTemperatur, TempData, (uint32_t *)CAN_TX_MAILBOX0);
			while (HAL_CAN_IsTxMessagePending(&hcan3, CAN_TX_MAILBOX0) == 1);
			status = HAL_CAN_AddTxMessage(&hcan3, &TxAnalog, AnalogData, (uint32_t *)CAN_TX_MAILBOX0);
		}

		if (((count % 400) == 0) && (task == 1))
		{
			// Return
			if ((ADC_VAL[7] > 1200) && (ADC_VAL[7] < 2900))
			{
				uartTransmit("Return gedrueckt\n", 17);
			}
			else if (ADC_VAL[7] < 1000)
			{
				uartTransmit("Navi gedrueckt\n", 15);
			}
			else
			{

			}

			// Info
			if ((ADC_VAL[6] > 1200) && (ADC_VAL[6] < 2900))
			{
				uartTransmit("Traffic gedrueckt\n", 18);
			}
			else if (ADC_VAL[6] < 1000)
			{
				uartTransmit("Info gedrueckt\n", 15);
			}
			else
			{

			}

			// KL15
			// if (ADC_VAL[4] <= 1150)								// Spannungsteiler fuer 36V (22k || 27k)
			if (ADC_VAL[4] < 2300)								// Spannungsteiler fuer 12V (10k || 10k)
			{
				uartTransmit("Unterspannung erkannt\n", 22);
			}
			// else if ADC_VAL[4] >= 4000)						// Spannungsteiler fuer 36V (22k || 27k)
			else if (ADC_VAL[7] >= 3900)						// Spannungsteiler fuer 12V (10k || 10k)
			{
				uartTransmit("Ueberspannung erkannt\n", 22);
			}
			else
			{

			}

			// Bremsdruck
			if (ADC_VAL[0] < 1000)
			{
				uartTransmit("Unterdruck erreicht\n", 20);
			}
			else if (ADC_VAL[0] >= 3500)
			{
				uartTransmit("Unterdruck verloren\n", 20);
			}
			else
			{

			}

			// STM Temperatur
			temperature = 45; //(int32_t)((TEMP110 - TEMP30) / ((float)(*TEMP110_CAL_VALUE) - (float)(*TEMP30_CAL_VALUE)) * ((float)(*TEMP30_CAL_VALUE)) + TEMP30);
			if (temperature > 60)
			{
				uartTransmit("STM Temperatur ueber 60°C\n", 27);
			}
			else if (temperature < -20)
			{
				uartTransmit("STM Temperatur ueber -20°C\n", 28);
			}
			else
			{

			}

			// PCB Temperatur
			if (ADC_VAL[3] < 800)
			{
				uartTransmit("PCB Temperatur ueber 60°C\n", 27);
			}
			else if (ADC_VAL[3] >= 3700)
			{
				uartTransmit("PCB Temperatur ueber -20°C\n", 28);
			}
			else
			{

			}

			// Bremsdruck Temperatur
			if (ADC_VAL[3] < 800)
			{
				uartTransmit("Bremsdruck Temperatur ueber 60°C\n", 34);
			}
			else if (ADC_VAL[3] >= 3700)
			{
				uartTransmit("Bremsdruck Temperatur ueber -20°C\n", 35);
			}
			else
			{

			}

			// Klimaflap Temperatur
			if (ADC_VAL[3] < 800)
			{
				uartTransmit("Klimaflap Temperatur ueber 60°C\n", 33);
			}
			else if (ADC_VAL[3] >= 3500)
			{
				uartTransmit("Klimaflap Temperatur ueber -20°C\n", 34);
			}
			else
			{

			}

			// Kuehlwasser Temperatur
			if (ADC_VAL[3] < 800)
			{
				uartTransmit("Kuehlwasser Temperatur ueber 60°C\n", 35);
			}
			else if (ADC_VAL[3] >= 3500)
			{
				uartTransmit("Kuehlwasser Temperatur ueber -20°C\n", 36);
			}
			else
			{

			}

			if (system_in.DCDC_Inst == 1)
			{
				uartTransmit("DCDC Instruct\n", 14);
			}
			else
			{

			}

			if ((system_in.ECON != 1) && (heizung != 1))
			{
				heizung = 1;
			}
			else if ((system_in.ECON != 1) && (heizung  == 1))
			{
				heizung = 0;
			}
			else
			{

			}

			// Variable count auf 0 zuruecksetzen
			count = 0;
		}

		// Zuruecksetzen Flag start
		task = 0;


	  	// Task wird alle 5 Millisekunden ausgefuehrt
	  	if (millis() - lastcan >= 5)
		{
	  		HAL_CAN_GetRxMessage(&hcan3, CAN_RX_FIFO0, &RxMessage, TxData);

			// Wenn Nachricht ueber den CAN-Bus empfangen wurden
			if (can_change == 1)
			{
				// Nachricht ID ueber UART ausgeben
				uartTransmitNumber(RxMessage.StdId, 16);
				uartTransmit("\t", 1);
				for (uint8_t i = 0; i < RxMessage.DLC; i++)
				{
					uartTransmitNumber(RxData[i], 16);
				}
				uartTransmit("\n", 1);

				// Sortieren der IDs nach Geraeten
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

				// Drehzahl ausgeben
				TxData[2] = motor1.output[2];
				TxData[3] = motor1.output[3];
				lastcan = millis();

				can_change = 0;
			}
		}

#ifdef DEBUG
		// Sende CAN Nachricht auf CAN-Bus / Teste CAN-BUS
		if (millis() - lastsendcan >= 1000)
		{
			while (HAL_CAN_IsTxMessagePending(&hcan3, CAN_TX_MAILBOX0) == 1);
			status = HAL_CAN_AddTxMessage(&hcan3, &TxMessage, TxData, (uint32_t *)CAN_TX_MAILBOX0);
			//hal_error(status);
			lastsendcan = millis();

			leuchten_out.BlueLed = !leuchten_out.BlueLed;
		}
#endif
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
// Interrupts
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	HAL_UART_Transmit(&huart2, &UART2_rxBuffer[uart_count], 1, 100);

	if (UART2_rxBuffer[uart_count] == 0x7F)
	{
		if (uart_count >= 1)
		{
			uart_count--;
		}
	}
	else
	{
		uart_count++;
	}

	if (uart_count == 12)
	{
		uint8_t tmp = 0x81;
		HAL_UART_Transmit(&huart2, (uint8_t*) "\r\nEingabe Ung", 13, 100);
		HAL_UART_Transmit(&huart2, &tmp, 1, 100);
		HAL_UART_Transmit(&huart2, (uint8_t*) "ltig\r\n", 6, 100);
		uart_count = 0;
	}

	if (UART2_rxBuffer[uart_count-1] == '\r')
	{
	    HAL_UART_Receive_IT(&huart2, &UART2_rxBuffer[0], 1);
	}
	else
	{
	    HAL_UART_Receive_IT(&huart2, &UART2_rxBuffer[uart_count], 1);
	}
}

// Can-Interrupt: Nachricht wartet
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	// Nachricht aus Speicher auslesen
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMessage, RxData);
	can_change = 1;
}

// Can-Interrupt: Fifo0 ist voll
void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan)
{
	// Fifo0 voll
	uartTransmit("Fifo0 von CAN3 ist voll\n", 24);

	Error_Handler();
}

// Timer-Interrupt: Timer ist uebergelaufen
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// Kontrolliere welcher Timer den Ueberlauf ausgeloest hat
	if (htim == &htim6)																	// Wenn Timer 6 den ueberlauf ausgeloest hat
	{
		millisekunden_flag_1 = 1;														// Setze Millisekunden Flag
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
