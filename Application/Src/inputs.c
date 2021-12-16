//----------------------------------------------------------------------
// Titel	:	Inputs.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	31.03.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "inputs.h"
#include "error.h"
//----------------------------------------------------------------------

// Lese alle Eingaenge
//----------------------------------------------------------------------
void readall_inputs(void)
{
#ifdef DEBUG_INPUT
	ITM_SendString("Lese Inputs ein\n");
#endif

	// Systemeingaenge einlesen
	system_in.Kickdown = HAL_GPIO_ReadPin(KICKDOWN_GPIO_Port, KICKDOWN_Pin);					// Eingang Gaspedal getreten
	system_in.Leerlauf = HAL_GPIO_ReadPin(LEERLAUF_GPIO_Port, LEERLAUF_Pin);					// Eingang Gaspedal nicht getreten
	system_in.BremseNO = HAL_GPIO_ReadPin(BREMSE_NO_GPIO_Port, BREMSE_NO_Pin);					// Eingang Bremse nicht getreten
	system_in.BremseNC = HAL_GPIO_ReadPin(BREMSE_NC_GPIO_Port, BREMSE_NC_Pin);					// Eingang Bremse getreten
	system_in.Kupplung = HAL_GPIO_ReadPin(KUPPLUNG_NO_GPIO_Port, KUPPLUNG_NO_Pin);				// Eingang Kupplung nicht getreten
	system_in.Recuperation = HAL_GPIO_ReadPin(RECUPERATION_GPIO_Port, RECUPERATION_Pin);		// Eingang Recuperation
	system_in.ECON = HAL_GPIO_ReadPin(ECON_GPIO_Port, ECON_Pin);								// Eingang Klima
	system_in.Anlasser = HAL_GPIO_ReadPin(ANLASSER_GPIO_Port, ANLASSER_Pin);					// Eingang Zuendschloss, Motor starten
	system_in.KL15 = HAL_GPIO_ReadPin(KL15_GPIO_Port, KL15_Pin);								// Eingang Auto an
	system_in.DCDC_Inst = HAL_GPIO_ReadPin(DCDC_INSTRUCTION_GPIO_Port, DCDC_INSTRUCTION_Pin);	// DCDC Wandler funktioniert einwandfrei
	system_in.Button1 = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);						// Zusatzeingang Taster 1
	system_in.Button2 = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);						// Zusatzeingang Taster 2
	system_in.Crash = HAL_GPIO_ReadPin(CRASH_GPIO_Port, CRASH_Pin);								// Crash Eingang
	system_in.Wakeup = HAL_GPIO_ReadPin(HW_WAKE_GPIO_Port, HW_WAKE_Pin);						// Eingang Hardware Wakeup
//	system_in.Bremsdruck_NO = HAL_GPIO_ReadPin(Bremsdruck_NO_GPIO_Port, Bremsdruck_NO_Pin);		// Bremsdruck nicht zu hoch
//	system_in.Bremsdruck_NC = HAL_GPIO_ReadPin(Bremsdruck_NC_GPIO_Port, Bremsdruck_NC_Pin);		// Bremsdruck zu hoch

	// SDC-Eingaenge einlesen
	sdc_in.EmergencyRun = HAL_GPIO_ReadPin(EMERGENCY_RUN_GPIO_Port, EMERGENCY_RUN_Pin);			// Emergency Run, Akku
	sdc_in.SDC0 = HAL_GPIO_ReadPin(SENSE_SDC_0_GPIO_Port, SENSE_SDC_0_Pin);						// Shutdown-Circuit, OK
	sdc_in.AkkuSDC = HAL_GPIO_ReadPin(SENSE_SDC_AKKU_GPIO_Port, SENSE_SDC_AKKU_Pin);			// Shutdown-Circuit Akku, OK
	sdc_in.BTB_SDC = HAL_GPIO_ReadPin(SENSE_SDC_BTB_GPIO_Port, SENSE_SDC_BTB_Pin);				// Shutdown-Circuit Bamocar, OK
	sdc_in.DCDC_Fault = HAL_GPIO_ReadPin(DCDC_FAULT_GPIO_Port, DCDC_FAULT_Pin);					// DCDC Wandler funktioniert nicht richtig

	// Komforteingaenge einlesen
	komfort_in.ASR1 = HAL_GPIO_ReadPin(ASR_IN1_GPIO_Port, ASR_IN1_Pin);							// ASR Eingang Mittelkonsole
	komfort_in.ASR2 = HAL_GPIO_ReadPin(ASR_IN2_GPIO_Port, ASR_IN2_Pin);							// ASR Eingang Mittelkonsole
	komfort_in.ECO = HAL_GPIO_ReadPin(ECO_GPIO_Port, ECO_Pin);									// ECO Eingang Mittelkonsole
	komfort_in.BC_Rst_In = HAL_GPIO_ReadPin(BC_RESET_IN_GPIO_Port, BC_RESET_IN_Pin);			// Boardcomputer Reset Eingang, Steuerung Motorsteuergeraet oder Kombiinstrument
	komfort_in.BC_Up_In = HAL_GPIO_ReadPin(BC_UP_IN_GPIO_Port, BC_UP_IN_Pin);					// Boardcomputer Rauf Eingang, Steuerung Motorsteuergeraet oder Kombiinstrument
	komfort_in.BC_Down_In = HAL_GPIO_ReadPin(BC_DOWN_IN_GPIO_Port, BC_DOWN_IN_Pin);				// Boardcomputer Runter Eingang, Steuerung Motorsteuergeraet oder Kombiinstrument
	komfort_in.BamoIn1 = HAL_GPIO_ReadPin(BAMOCAR_IN1_GPIO_Port, BAMOCAR_IN1_Pin);				// Eingang Bamocar 1
	komfort_in.BamoIn2 = HAL_GPIO_ReadPin(BAMOCAR_IN2_GPIO_Port, BAMOCAR_IN2_Pin);				// Eingang Bamocar 2
	komfort_in.Enter = HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin);							// Encoder Taster Enter Eingang Mittelconsole
	komfort_in.OutA = HAL_GPIO_ReadPin(OUTA_GPIO_Port, OUTA_Pin);								// Encoder OUTA Eingang Mittelconsole
	komfort_in.OutB = HAL_GPIO_ReadPin(OUTB_GPIO_Port, OUTB_Pin);								// Encoder OUTB Eingang Mittelconsole
	komfort_in.GRA1 = HAL_GPIO_ReadPin(GRA1_GPIO_Port, GRA1_Pin);								// Tempomat 1 Eingang
	komfort_in.GRA2 = HAL_GPIO_ReadPin(GRA2_GPIO_Port, GRA2_Pin);								// Tempomat 2 Eingang
	komfort_in.GRA3 = HAL_GPIO_ReadPin(GRA3_GPIO_Port, GRA3_Pin);								// Tempomat 3 Eingang
	komfort_in.GRA4 = HAL_GPIO_ReadPin(GRA4_GPIO_Port, GRA4_Pin);								// Tempomat 4 Eingang
	komfort_in.Durchfluss = HAL_GPIO_ReadPin(DURCHFLUSS_GPIO_Port, DURCHFLUSS_Pin);				// Durchflusssensor Eingang

#ifdef DEBUG_INPUT
	ITM_SendString("Eingaenge gelesen.\n");
	ITM_SendString("system_in: ");
	ITM_SendNumber(system_in.systeminput);
	ITM_SendChar('\n');
	ITM_SendString("sdc_in: ");
	ITM_SendNumber(sdc_in.sdcinput);
	ITM_SendChar('\n');
	ITM_SendString("komfort_in: ");
	ITM_SendNumber(komfort_in.komfortinput);
	ITM_SendChar('\n');
#endif
}
//----------------------------------------------------------------------
