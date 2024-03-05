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
#include "dma.h"
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
// Motorsteuergeraet Statevariable
Motor_state mStrg_state = {{Start, true, false, false, false}};
static uint32_t timeError = 0, timeWarning = 0;
static uint32_t longerror = 0, longwarning = 0;

// Fehler Speicher CAN-Bus
uint8_t  can_online = 0;

// Millisekunden Flag fuer PWM Task
volatile uint8_t millisekunden_flag = 0;											// Flag fuer Millisekungen Timer Task

// Motor CAN Variablen
motor280_tag motor280;																// Daten der CAN-Nachricht 280
//motor288_tag motor288;																// Daten der CAN-Nachricht 288
//motor380_tag motor380;																// Daten der CAN-Nachricht 380
//motor388_tag motor388;																// Daten der CAN-Nachricht 388
motor480_tag motor480;																// Daten der CAN-Nachricht 480
//motor488_tag motor488;																// Daten der CAN-Nachricht 488
//motor580_tag motor580;																// Daten der CAN-Nachricht 580

// ADC Array
uint16_t ADC_VAL[10] = {0};

// Mittelwert Gaspedal
uint16_t gas_mean = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void checkSDC(void);
void sortCAN(void);
void setStatus(uint8_t Status);
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
	// Motorsteuergeraet Statemaschine Zeitvariablen
	uint32_t timeStandby = 0, timeErrorLED = 0;

	// Timer Task Variablen (PWM)
	uint8_t task = 0;
	uint16_t count = 0;

	// Motorsteuergeraet CAN-Bus Zeitvariable, Errorvariable
	uint32_t timeBAMO = 0, timeBMS = 0, timeStromHV = 0, timeStromLV = 0, timeKombi = 0;

	// CAN-Bus Receive Message
	CAN_message_t RxMessage;

	// ADC Wert Gaspedal
	uint16_t gas_adc = 0;

	// WS2812 LED
	uint8_t WS2812_update = 0;
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

#ifdef DEBUG
	app_info();
	HAL_Delay(3000);
#endif

	uartTransmit("Start\n", 6);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_CAN1_Init();
  MX_TIM6_Init();
  MX_TIM3_Init();
  MX_CAN3_Init();
  /* USER CODE BEGIN 2 */

	Set_LED(MAX_LED, 0, 0, 0);
	Set_LED(0, 255, 0, 255);
	WS2812_Send_Wait();

	// Starte Timer 6 Interrupt
	HAL_TIM_Base_Start_IT(&htim6);

	leuchten_out.Anhaenger = true;
	leuchten_out.Niveau = true;
	HAL_GPIO_WritePin(ANHAENGER_GPIO_Port, ANHAENGER_Pin, leuchten_out.Anhaenger);
	HAL_GPIO_WritePin(NIVEAU_OUT_GPIO_Port, NIVEAU_OUT_Pin, leuchten_out.Niveau);

#ifdef DEBUG
	#define MAINWHILE			"\nStarte While Schleife\n"
	uartTransmit(MAINWHILE, sizeof(MAINWHILE));
#endif

	CANinit(RX_SIZE_16, TX_SIZE_16);
	CAN_config();
	mStrg_state.State = Ready;

	for (uint8_t j = 0; j < ANZAHL_OUTPUT_PAKETE; j++)
	{
		CAN_Output_PaketListe[j].msg.buf[0] = 0;
		CAN_Output_PaketListe[j].msg.buf[1] = 0;
		CAN_Output_PaketListe[j].msg.buf[2] = 0;
		CAN_Output_PaketListe[j].msg.buf[3] = 0;
		CAN_Output_PaketListe[j].msg.buf[4] = 0;
		CAN_Output_PaketListe[j].msg.buf[5] = 0;
		CAN_Output_PaketListe[j].msg.buf[6] = 0;
		CAN_Output_PaketListe[j].msg.buf[7] = 0;
	}

	// Wenn Tischaufbau dann CAN-Nachricht fuer Lenkung senden
#if TISCHAUFBAU == 1
	CAN_Output_PaketListe[9].msg.buf[0] = 0;
	CAN_Output_PaketListe[9].msg.buf[1] = 1;
#endif
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
	  ADC_VAL[0] = ADC_Bremsdruck();
	  ADC_VAL[1] = ADC_Bremsdrucktemperatur();
	  ADC_VAL[2] = ADC_STMTemperatur();
	  ADC_VAL[3] = ADC_PCBTemperatur();
	  ADC_VAL[4] = ADC_KL15();
	  ADC_VAL[5] = ADC_Klimaflap();
	  ADC_VAL[6] = ADC_Info();
	  ADC_VAL[7] = ADC_Return();
	  ADC_VAL[8] = ADC_Kuhlwassertemperatur();
	  ADC_VAL[9] = ADC_Gaspedal();

	  // Sortiere CAN-Daten auf CAN-Buffer
	  sortCAN();

	  // Lese CAN-Nachrichten ein
	  if (CAN_available() >= 1)
	  {
		  CANread(&RxMessage);

		  switch (RxMessage.id)
		  {
#if BAMOCAR_AVAILIBLE == 1
			  // Bamocar ID
			  case BAMOCAR_CAN_RX:
			  {
				  can_online |= (1 << 0);
				  timeBAMO = millis();
				  BAMOCAN_ID(&RxMessage.buf[0], RxMessage.len);
				  break;
			  }
#endif

#if BMS_AVAILIBLE == 1
			  // Batteriemanagement Status ID
			  case BMS_CAN_STATUS:
			  {
				  timeBMS = millis();
				  can_online |= (1 << 1);
				  break;
			  }
#endif

#if STROM_HV_AVAILIBLE == 1
			  // Stromsensor
			  case STROM_HV_CAN_I:
			  {
				  can_online |= (1 << 2);
				  timeStromHV = millis();
				  break;
			  }
#endif

#if STROM_LV_AVAILIBLE == 1
			  // Stromsensor
			  case STROM_LV_CAN_I:
			  {
				  can_online |= (1 << 3);
				  timeStromHV = millis();
				  break;
			  }
#endif

#if KOMBIINSTRUMENT_AVALIBLE == 1
			  // Stromsensor
			  case KOMBI2_CAN:
			  {
				  can_online |= (1 << 4);
				  timeKombi = millis();

				  setStatus(StateNormal);

				  break;
			  }
#endif



			  // Alle anderen Pakete laufen in leere und werden ignoriert
			  default:
			  {
				  break;
			  }
		  }
	  }

#if BAMOCAR_AVAILIBLE == 1
	  // Wenn Timeoutzeit ueberschritten, Bamocar CAN-Timeout
	  if (millis() > (timeBAMO + CAN_TIMEOUT))
	  {
		  can_online &= ~(1 << 0);
		  longwarning |= (1 << 0);

		  setStatus(StateWarning);
	  }
#endif

#if BMS_AVALIBLE == 1
	  // Wenn Timeoutzeit ueberschritten, BMS CAN-Timeout
	  if (millis() > (timeBMS + CAN_TIMEOUT))
	  {
		  can_online &= ~(1 << 1);
		  longwarning |= (1 << 0);

		  setStatus(StateWarning);
	  }
#endif

#if STROM_HV_AVAILIBLE == 1
	  // Wenn Timeoutzeit ueberschritten, Stromsensor HV CAN-Timeout
	  if (millis() > (timeStromHV + CAN_TIMEOUT))
	  {
		  can_online &= ~(1 << 2);
		  longwarning |= (1 << 0);

		  setStatus(StateWarning);
	  }
#endif

#if STROM_LV_AVAILIBLE == 1
	  // Wenn Timeoutzeit ueberschritten, Stromsensor LV CAN-Timeout
	  if (millis() > (timeStromLV + CAN_TIMEOUT))
	  {
		  can_online &= ~(1 << 3);
		  longwarning |= (1 << 0);

		  setStatus(StateWarning);
	  }
#endif

#if KOMBIINSTRUMENT_AVALIBLE == 1
	  // Wenn Timeoutzeit ueberschritten, Kombiinstrument
	  if (millis() > (timeKombi + CAN_TIMEOUT))
	  {
		  can_online &= ~(1 << 4);
		  longwarning |= (1 << 0);

		  setStatus(StateWarning);
	  }
#endif

	  // PWM Oelstandsensor Kombiinstrument ausgeben
	  pwm_oelstand(count);

	  // Task wird jede Millisekunde ausgefuehrt
	  if (millisekunden_flag == 1)
	  {
		  count++;																	// Zaehler count hochzaehlen
		  millisekunden_flag = 0;													// Setze Millisekunden-Flag zurueck

		  // Setze Flag start, nur wenn millisekunden Flag gesetzt war
		  task = 1;
	  }

	  // Zuruecksetzen der Countervariable fuer pwm_Oelstand
	  if (((count % 400) == 0) && (task == 1))
	  {
		  // Variable count auf 0 zuruecksetzen
		  count = 0;
	  }

	  // Crash Ausgeloest
	  if (system_in.Crash != 1)
	  {
		  setStatus(CriticalError);
	  }

	  // Wenn Statemaschine nicht im Standby ist
	  if (mStrg_state.State != Standby)
	  {
		  // Schreibe alle CAN-NAchrichten auf BUS, wenn nicht im Standby
		  CANwork();

		  // Shutdown-Circuit checken
		  checkSDC();
	  }

	  // Statemaschine keine Fehler
	  if (mStrg_state.Normal)
	  {
		  leuchten_out.RedLed = false;
		  leuchten_out.GreenLed = true;

		  motor480.MotorLED = false;
	  }

	  // Statemaschine hat Warnungen
	  if (mStrg_state.Warning)
	  {
		  if (millis() - timeErrorLED > 1000)
		  {
			  leuchten_out.RedLed = !leuchten_out.RedLed;

			  motor480.MotorLED = !motor480.MotorLED;
			  timeErrorLED = millis();
		  }

		  leuchten_out.GreenLed = true;
	  }

	  // Statemaschine hat Fehler
	  if (mStrg_state.Error)
	  {
		  if (millis() - timeErrorLED > 1000)
		  {
			  leuchten_out.RedLed = !leuchten_out.RedLed;
			  timeErrorLED = millis();
		  }

		  leuchten_out.GreenLed = false;

		  motor480.MotorLED = true;
	  }

	  // Statemaschine hat Kritische Fehler
	  if (mStrg_state.CriticalError)
	  {
		  leuchten_out.RedLed = true;
		  leuchten_out.Ladeleuchte = false;
		  leuchten_out.GreenLed = false;

		  motor480.MotorLED = true;

		  system_out.MotorSDC = false;
	  }

	  // Statemaschine von Motorsteuergeraet
	  switch (mStrg_state.State)
	  {
		  // State Ready, Vorbereiten des Motorsteuergeraetes
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
			  mStrg_state.State = KL15;

			  break;
		  }

		  // State KL15, wenn Schluessel auf Position 2, KL15 einschalten
		  case KL15:
		  {
			  // Wenn Schluessel auf Position 3 geschaltet wird, nur einmal moeglich
			  if ((system_in.Anlasser != 1) || ((sdc_in.Anlasser == 1) && (komfort_in.ASR1 == 1) && (millis() > (timeStandby + 3000))))
			  {
				  // Solange kein kritischer Fehler auftritt
				  if (!(mStrg_state.CriticalError))
				  {
					  uartTransmit("Anlassen\n", 9);
					  mStrg_state.State = Anlassen;

					  // Anlasser Zustand abspeichern
					  sdc_in.Anlasser = true;

					  // LED in Cockpit aktivieren
					  motor480.VorgluehenLED = true;

					  // Motor Shutdown-Circuit aktivieren, wenn OK
					  system_out.MotorSDC = true;
				  }

				  // Pumpe, Vakuumpumpe, Bamocar einschalten
				  // system_out.Gluehkerzen = 1;
			  }

			  // Falls KL15 abfaellt und der Schluessel abgezogen wird
			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  mStrg_state.State = Standby;
				  system_out.MotorSDC = false;
				  sdc_in.Anlasser = false;
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State Anlassen, wenn Schluessel auf Position 3 und keine kritischen Fehler, Anlasser einschalten
		  case Anlassen:
		  {
			  // Kupplung und Bremse getreten
			  if ((system_in.Kupplung != 1) && (system_in.BremseNO != 1) && (system_in.BremseNC == 1))
			  {
				  uartTransmit("Precharge\n", 10);
				  mStrg_state.State = Precharge;
			  }

			  // Falls KL15 abfaellt und der Schluessel abgezogen wird
			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  mStrg_state.State = Standby;
				  system_out.MotorSDC = false;
				  sdc_in.Anlasser = false;
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State Precharge, wenn Bremse beim Anlassen oder danach getreten ist
		  case Precharge:
		  {
			  // Abfrage Shutdown-Circuit
			  if ((sdc_in.SDC0 != 1) && (sdc_in.BTB_SDC != 1) && (sdc_in.AkkuSDC != 1))
			  {
				  // ReadyToDrive Sound abspielen und warten, ob abgeschlossen werden kann
				  if (playRTDS() == true)
				  {

					  uartTransmit("ReadyToDrive\n", 13);
					  mStrg_state.State = ReadyToDrive;

					  motor480.VorgluehenLED = false;

					  timeStandby = millis();
				  }
				  else
				  {
					  mStrg_state.State = KL15;
					  system_out.MotorSDC = false;
					  sdc_in.Anlasser = false;
				  }
			  }

			  // Falls KL15 abfaellt und der Schluessel abgezogen wird
			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  mStrg_state.State = Standby;
				  system_out.MotorSDC = false;
				  sdc_in.Anlasser = false;
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State ReadyToDrive, wenn SDC Ok ist und Vorgeladen wurde
		  case ReadyToDrive:
		  {
			  // Bei Tasterbetaetigung umschalten in Drive Modus
			  if ((komfort_in.ASR1 == 1) && (millis() > (timeStandby + 3000)))
			  {
				  uartTransmit("Drive\n", 6);
				  mStrg_state.State = Drive;

				  Set_LED(0, 0, 255, 0);
				  WS2812_update = 1;

				  timeStandby = millis();
			  }

			  // Falls KL15 abfaellt und der Schluessel abgezogen wird
			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  mStrg_state.State = Standby;
				  system_out.MotorSDC = false;
				  sdc_in.Anlasser = false;
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State Drive, wenn Fahrmodus manuel aktiviert wird
		  case Drive:
		  {
			   gas_adc = readTrottle(ADC_VAL[9]);

			  // Abfrage ob Mittelwertbildung
			  if (gas_adc > 0)														// Wenn Gaspedal Plausible dann Mittelwertbildung
			  {
				  // Mittelwert bilden (https://nestedsoftware.com/2018/03/20/calculating-a-moving-average-on-streaming-data-5a7k.22879.html)
				  // Mittelwertbildung aus 10 Werten (Weniger die 10 verkleineren, Mehr die 10 vergroeßern)
				  gas_mean = (gas_mean + ((gas_adc - gas_mean)/10));

				  // Todo: Wenn Drehzahl zu hoch dann Fehler Cockpit (Oelstand, Bremse)
				  writeBamoReg16(BAMOCAR_REG_TORQUE_SETPOINT, gas_mean);
				  motor280.Drehzahl = (gas_mean * 5);
			  }
			  else																	// Wenn Gaspedal unplausible oder Kupplung getreten
			  {
				  gas_mean = 0;
				  writeBamoReg16(BAMOCAR_REG_TORQUE_SETPOINT, gas_mean);
				  motor280.Drehzahl = gas_mean;
			  }

			  if ((komfort_in.ASR1 == 1) && (millis() > (timeStandby + 3000)))
			  {
				  uartTransmit("KL15\n", 5);
				  mStrg_state.State = KL15;
				  system_out.MotorSDC = false;

				  Set_LED(0, 255, 0, 0);
				  WS2812_update = 1;

				  timeStandby = millis();
			  }

			  // Falls KL15 abfaellt und der Schluessel abgezogen wird
			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  mStrg_state.State = Standby;
				  system_out.MotorSDC = false;
				  sdc_in.Anlasser = false;

				  Set_LED(0, 255, 0, 0);
				  WS2812_update = 1;

				  timeStandby = millis();
			  }

			  break;
		  }

		  // State Standby, wenn Schluessel gezogen wird, KL15 ausschalten
		  case Standby:
		  {
			  // Gluehkerzenrelais nach 1min abschalten, erst nach der Pumpe moeglich
			  if ((highcurrent_out.Pumpe_Kuhlung == false) && (millis() > (timeStandby + PUMPTIME + 1000)))
			  {
				  system_out.Gluehkerzen = false;
			  }

			  // Pumpe nach 1min abschalten
			  if ((highcurrent_out.Pumpe_Kuhlung == true) && (millis() > (timeStandby + PUMPTIME)))
			  {
				  highcurrent_out.Pumpe_Kuhlung = false;
			  }

			  // Fuer 5min warten und BMS weiterhin aktiv halten
			  if (millis() > (timeStandby + MOTORTIME))
			  {
				  uartTransmit("Ausschalten\n", 12);
				  mStrg_state.State = Ausschalten;
			  }
			  // Falls innerhalb der 5min die KL15 wieder aktiviert wird
			  else if (system_in.KL15 != 1)
			  {
				  uartTransmit("Ready\n", 6);
				  mStrg_state.State = Ready;
			  }

			  break;
		  }

		  // State Ausschalten, wenn Standby State laenger als 5min dauert
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

		  // Falls kein State zutrifft, dann Kritischer Fehler
		  default:
		  {
			  uartTransmit("Motor Kritischer Fehler\n", 24);
			  setStatus(CriticalError);

			  break;
		  }
	  }

	  // Schreibe WS2812
	  if (WS2812_update == 1)
	  {
		  // Wenn Schreiben moeglich
		  if (WS2812_Send() == 1)
		  {
			  // Solange keine neuen Daten, kein Senden notwendig
			  WS2812_update = 0;
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
// Checke Shutdown-Circuit
void checkSDC(void)
{
	sdc_in.SDC_OK = true;

	if (((mStrg_state.State == Precharge) || (mStrg_state.State == ReadyToDrive) || (mStrg_state.State == Drive)) && sdc_in.SDC0 == 1)
	{
		setStatus(StateError);
		longerror |= (1 << 0);

		sdc_in.SDC_OK = false;
	}

#if BAMOCAR_AVAILIBLE == 1
	if (sdc_in.BTB_SDC != 1)
	{
		setStatus(StateError);
		longerror |= (1 << 1);

		sdc_in.SDC_OK = false;
	}
#endif

#if BMS_AVALIBLE == 1
	if (sdc_in.AkkuSDC != 1)
	{
		setStatus(StateError);
		longerror |= (1 << 2);

		sdc_in.SDC_OK = false;
	}
#endif

	if (sdc_in.SDC_OK == true)
	{
		setStatus(StateNormal);
	}
}

// Sortiere CAN Daten
void sortCAN(void)
{
	// Digital-Ausgaenge
	CAN_Output_PaketListe[1].msg.buf[0] = system_out.systemoutput;
	CAN_Output_PaketListe[1].msg.buf[1] = highcurrent_out.high_out;
	CAN_Output_PaketListe[1].msg.buf[2] = (leuchten_out.ledoutput >> 8);
	CAN_Output_PaketListe[1].msg.buf[3] = leuchten_out.ledoutput;
	CAN_Output_PaketListe[1].msg.buf[4] = komfort_out.komfortoutput;
	CAN_Output_PaketListe[1].msg.buf[5] = 0;

	// Digital-Eingaenge
	CAN_Output_PaketListe[2].msg.buf[0] = 0;
	CAN_Output_PaketListe[2].msg.buf[1] = (system_in.systeminput >> 8);
	CAN_Output_PaketListe[2].msg.buf[2] = system_in.systeminput;
	CAN_Output_PaketListe[2].msg.buf[3] = sdc_in.sdcinput;
	CAN_Output_PaketListe[2].msg.buf[4] = (komfort_in.komfortinput >> 8);
	CAN_Output_PaketListe[2].msg.buf[5] = komfort_in.komfortinput;

	// Analogeingaenge
	CAN_Output_PaketListe[3].msg.buf[0] = ADC_VAL[4];
	CAN_Output_PaketListe[3].msg.buf[1] = (ADC_VAL[4] >> 8) | (ADC_VAL[0] << 4);
	CAN_Output_PaketListe[3].msg.buf[2] = (ADC_VAL[0] >> 4);
	CAN_Output_PaketListe[3].msg.buf[3] = gas_mean;
	CAN_Output_PaketListe[3].msg.buf[4] = (gas_mean >> 8) | (ADC_VAL[6] << 4);
	CAN_Output_PaketListe[3].msg.buf[5] = (ADC_VAL[6] >> 4);
	CAN_Output_PaketListe[3].msg.buf[6] = ADC_VAL[7];
	CAN_Output_PaketListe[3].msg.buf[7] = (ADC_VAL[7] >> 8);

	// Motor 280
	CAN_Output_PaketListe[4].msg.buf[0] = motor280.motor280output[0];
	CAN_Output_PaketListe[4].msg.buf[1] = motor280.motor280output[1];
	CAN_Output_PaketListe[4].msg.buf[2] = motor280.motor280output[2];
	CAN_Output_PaketListe[4].msg.buf[3] = motor280.motor280output[3];
	CAN_Output_PaketListe[4].msg.buf[4] = motor280.motor280output[4];
	CAN_Output_PaketListe[4].msg.buf[5] = motor280.motor280output[5];
	CAN_Output_PaketListe[4].msg.buf[6] = motor280.motor280output[6];
	CAN_Output_PaketListe[4].msg.buf[7] = motor280.motor280output[7];

	// Motor 480
	CAN_Output_PaketListe[5].msg.buf[0] = motor480.motor480output[0];
	CAN_Output_PaketListe[5].msg.buf[1] = motor480.motor480output[1];
	CAN_Output_PaketListe[5].msg.buf[2] = motor480.motor480output[2];
	CAN_Output_PaketListe[5].msg.buf[3] = motor480.motor480output[3];
	CAN_Output_PaketListe[5].msg.buf[4] = motor480.motor480output[4];
	CAN_Output_PaketListe[5].msg.buf[5] = motor480.motor480output[5];
	CAN_Output_PaketListe[5].msg.buf[6] = motor480.motor480output[6];
	CAN_Output_PaketListe[5].msg.buf[7] = motor480.motor480output[7];

	// Temperatureingaenge
	CAN_Output_PaketListe[6].msg.buf[0] = ADC_VAL[2];
	CAN_Output_PaketListe[6].msg.buf[1] = (ADC_VAL[2] >> 8) | (ADC_VAL[3] << 4);
	CAN_Output_PaketListe[6].msg.buf[2] = (ADC_VAL[3] >> 4);
	CAN_Output_PaketListe[6].msg.buf[3] = ADC_VAL[8];
	CAN_Output_PaketListe[6].msg.buf[4] = (ADC_VAL[8] >> 8) | (ADC_VAL[1] << 4);
	CAN_Output_PaketListe[6].msg.buf[5] = (ADC_VAL[1] >> 4);
	CAN_Output_PaketListe[6].msg.buf[6] = ADC_VAL[5];
	CAN_Output_PaketListe[6].msg.buf[7] = (ADC_VAL[5] >> 8);

	// Motor Status
	CAN_Output_PaketListe[7].msg.buf[0] = mStrg_state.status;
	CAN_Output_PaketListe[7].msg.buf[1] = longwarning;
	CAN_Output_PaketListe[7].msg.buf[2] = longerror;
	CAN_Output_PaketListe[7].msg.buf[3] = can_online;
}

// Set Status der Statemaschine
void setStatus(uint8_t Status)
{
	switch (Status & 0xF0)
	{
		case StateNormal:
		{
			if (mStrg_state.status & StateWarning)
			{
				if (millis() > (timeWarning + WARNING_RESET))
				{
					mStrg_state.status = (Status | mStrg_state.State);

					longwarning = 0;
					longerror = 0;
				}

				break;
			}
		}
		case StateWarning:
		{
			timeWarning = millis();

			if (mStrg_state.status & StateError)
			{
				if (millis() > (timeError + ERROR_RESET))
				{
					mStrg_state.status = (StateWarning | mStrg_state.State);
				}

				break;
			}
		}
		case StateError:
		{
			timeError = millis();

			if (mStrg_state.status & CriticalError)
			{
				break;
			}
		}
		case CriticalError:
		{
			mStrg_state.status = (Status | mStrg_state.State);
			break;
		}
		default:
		{
			mStrg_state.status = (CriticalError | mStrg_state.State);
			break;
		}
	}
}

// Timer-Interrupt: Timer ist uebergelaufen
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// Kontrolliere welcher Timer den Ueberlauf ausgeloest hat
	if (htim == &htim6)																	// Wenn Timer 6 den ueberlauf ausgeloest hat
	{
		millisekunden_flag = 1;															// Setze Millisekunden Flag
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
