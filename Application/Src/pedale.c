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
#include "pedale.h"
#include "adc_inputs.h"
#include "inputs.h"
#include "error.h"
//----------------------------------------------------------------------

// Gaspedal auswerten
//----------------------------------------------------------------------
uint16_t readTrottle(void)
{
	// Variablen anlegen
	uint16_t ADC_Gas = 0;

	// Gaspedal auf Plausibilitaet pruefen
//	if ((system_in.Kickdown != 1) && (system_in.Leerlauf == 1))				// Gaspedal voll getreten
//	{
//
//	}
//	else if ((system_in.Kickdown == 1))										// Gaspedal nicht oder teilweise getreten
//	{
//		// Gaspedal einlesen
		ADC_Gas = ADC_Gaspedal();
//	}
//	else																	// Falls beide Schalter betaetigt sind
//	{
//		// Gaspedal invalide
//		software_error(ERROR_GASPEDAL);
//	}

	if (ADC_Gas < 300)
	{
		ADC_Gas = 0;
	}

	if (ADC_Gas >= 300)
	{
		ADC_Gas -= 300;
	}

	if (ADC_Gas >= 1000)
	{
		ADC_Gas = 1000;
	}

	return ADC_Gas;
}
//----------------------------------------------------------------------

/* // Bremse auswerten
//----------------------------------------------------------------------
void readBrake(void)
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
}
//----------------------------------------------------------------------*/
