//----------------------------------------------------------------------
// Titel	:	pedale.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	03.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "BasicUart.h"
#include "inputs.h"
#include "error.h"
#include "adc_inputs.h"
#include "pedale.h"
//----------------------------------------------------------------------

// Gaspedal auswerten
//----------------------------------------------------------------------
uint16_t readTrottle(void)
{
	// Variablen anlegen
	uint16_t ADC_Gas = 0;

	// Pruefen ob Variable Anlasser aktiv ist
	if (sdc_in.Anlasser == 1)												// Nur aktiv, wenn KL15 an und Anlasser einmal betaetigt.
	{
		// Gaspedal einlesen
		ADC_Gas = ADC_Gaspedal();

		// Pruefen ob Kupplung getreten wurde
		if (system_in.Kupplung == 1)										// Wenn Kupplung nicht getreten wurde == 1
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
			else if ((system_in.Leerlauf == 1) && (ADC_Gas >= GAS_MIN_ADC))
			{
				// Wenn Wert groesser THRESHOLD ist, dann THRESHOLD vom ADC-Wert abziehen
				ADC_Gas -= GAS_MIN_ADC;
			}
			// Threshold Wert vergleichen / Threshold Wert < THRESHOLD und Leerlauf aktiv
			else if ((system_in.Leerlauf == 1) && (ADC_Gas < GAS_MIN_ADC))
			{
				// Wenn der Wert kleine als THRESHOLD ist, dann ADC ignorieren, alle Werte sind 0
				ADC_Gas = 0;
			}
			// Threshold Wert vergleichen / Threshold Wert < THRESHOLD und Kickdown aktiv
			else if ((system_in.Kickdown == 1) && (ADC_Gas < (GAS_MAX_ADC - GAS_MIN_ADC)))
			{
				// Wenn Wert kleiner THRESHOLD ist

			}
			// Threshold Wert vergleichen / Threshold Wert > THRESHOLD und Kickdown aktiv
			else if ((system_in.Kickdown == 1) && (ADC_Gas >= (GAS_MAX_ADC - GAS_MIN_ADC)))
			{
				// Wenn Wert gleich THRESHOLD ist
				ADC_Gas = GAS_MAX_ADC;
			}
		}
		// Wenn Kupplung getreten == 0
		else
		{
			// Wenn Kupplung oder Bremse getreten
			ADC_Gas = 0;
		}
	}

	return ADC_Gas;
}
//----------------------------------------------------------------------

// Bremse auswerten
//----------------------------------------------------------------------
/*void readBrake(void)
{
	// Variablen anlegen
	uint16_t ADC_Bremse = 0;

	// Gaspedal auf Plausibilitaet pruefen
	if ((system_in.BremseNO == 1) && (system_in.BremseNC != 1))				// Bremse nicht getreten
	{

	}
	else if ((system_in.BremseNO != 1) && (system_in.BremseNC == 1))		// Bremse voll getreten
	{

	}
	else if ((system_in.BremseNO != 1) && (system_in.BremseNC != 1))		// Bremse teilweise getreten
	{
		// Bremsdruck einlesen
		ADC_Bremse = ADC_Bremsdruck();
	}
	else																	// Falls beide Schalter betaetigt sind
	{
		// Bremse invalide
		software_error(ERROR_BREMSPEDAL);
	}
}*/
//----------------------------------------------------------------------
