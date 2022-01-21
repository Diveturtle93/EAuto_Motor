//----------------------------------------------------------------------
// Titel	:	pedale.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	03.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfügen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfügen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Einfügen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "BasicUart.h"
#include "inputs.h"
#include "error.h"
#include "adc_inputs.h"
#include "pedale.h"
//----------------------------------------------------------------------

// Gaspedal auswerten
//----------------------------------------------------------------------
uint16_t readPedals(void)
{
	// Variablen anlegen
	uint16_t ADC_Gas = 0;
	uint8_t tmpBrake = 0;

#ifdef DEBUG_PEDALE
	ITM_SendString("Zustand von Bremse ausgeben\n");
	ITM_SendString("Bremse darf nicht bei beiden Eingaengen 1 sein.\n");
	ITM_SendString("BremseNO:\t");
	ITM_SendNumber(system_in.BremseNO);
	ITM_SendChar('\n');
	ITM_SendString("BremseNC:\t");
	ITM_SendNumber(system_in.BremseNC);
	ITM_SendChar('\n');
#endif
/*
	// Bremspedal auf Plausibilitaet pruefen
	if ((system_in.BremseNO == 1) && (system_in.BremseNC != 1))				// Bremse nicht getreten
	{
		tmpBrake = 0;
	}
	else if ((system_in.BremseNO != 1) && (system_in.BremseNC == 1))		// Bremse voll getreten
	{
		tmpBrake = 0x01;
	}
	else
	{
		// Fehlermeldung auf Uart ausgeben
#define BRAKE_INVALID				"ERROR_Bremspedal_2 Plausibilitaetsfehler: Bremse_NO und Bremse_NC"
		uartTransmit(BRAKE_INVALID, sizeof(BRAKE_INVALID));
		// Bremse invalide
		software_error(ERROR_BREMSPEDAL);
	}*/

#ifdef DEBUG_PEDALE
	ITM_SendString("Zustand von Kupplung ausgeben, Kupplung:\t");
	ITM_SendNumber(system_in.Kupplung);
	ITM_SendChar('\n');
#endif

	// Kupplung pruefen
	if (system_in.Kupplung == 1)
	{
		tmpBrake |= 0x02;
	}

#ifdef DEBUG_PEDALE
	ITM_SendString("Zustand Pedale ausgeben, tmpBrake:\t");
	ITM_SendNumber(tmpBrake);
	ITM_SendChar('\n');
#endif

	// Gaspedal einlesen
	ADC_Gas = ADC_Gaspedal();

	// Wenn Bremse oder Kupplung nicht getreten ist, Gaspedal auswerten, KL15 muss an sein
	if (tmpBrake == 0 && (system_in.KL15 != 1))
	{
		// Wenn Leerlauf und Kickdown aktiv Plausibilitaetsfehler
		if ((system_in.Leerlauf == 1) && (system_in.Kickdown == 1))
		{
			// Fehlermeldung auf Uart ausgeben
#define TROTTLE_INVALID				"Error_Gaspedal_1 Plausibilitaetsfehler: Kickdown und Leerlauf"
			uartTransmit(TROTTLE_INVALID, sizeof(TROTTLE_INVALID));
			// Gaspedal invalide
			software_error(ERROR_GASPEDAL);
		}
		// Threshold Wert vergleichen / Threshold Wert >= THRESHOLD und Leerlauf aktiv
		else if ((system_in.Leerlauf == 1) && (ADC_Gas >= GAS_THRESHOLD))
		{
			// Wenn Wert groesser THRESHOLD ist, dann THRESHOLD vom ADC-Wert abziehen
			ADC_Gas -= GAS_THRESHOLD;
		}
		// Threshold Wert vergleichen / Threshold Wert < THRESHOLD und Leerlauf aktiv
		else if ((system_in.Leerlauf == 1) && (ADC_Gas < GAS_THRESHOLD))
		{
			// Wenn der Wert kleine als THRESHOLD ist, dann ADC ignorieren, alle Werte sind 0
			ADC_Gas = 0;
		}
		// Threshold Wert vergleichen / Threshold Wert < THRESHOLD und Kickdown aktiv
		else if ((system_in.Kickdown == 1) && (ADC_Gas < (GAS_MAX_ADC - GAS_THRESHOLD)))
		{
			// Wenn Wert kleiner THRESHOLD ist

		}
		// Threshold Wert vergleichen / Threshold Wert > THRESHOLD und Kickdown aktiv
		else if ((system_in.Kickdown == 1) && (ADC_Gas >= (GAS_MAX_ADC - GAS_THRESHOLD)))
		{
			// Wenn Wert gleich THRESHOLD ist
			ADC_Gas = 4095;
		}
	}
	// Wenn tmpBrake != 0
	else
	{
		// Wenn Kupplung oder Bremse getreten
		ADC_Gas = 0;
	}

	return ADC_Gas;
}
//----------------------------------------------------------------------
