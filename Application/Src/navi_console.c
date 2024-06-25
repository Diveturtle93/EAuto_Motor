//----------------------------------------------------------------------
// Titel	:	navi_console.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jun 17, 2024
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
#include "navi_console.h"
#include "Motorsteuergeraet.h"
//----------------------------------------------------------------------

// Variablen definieren
//----------------------------------------------------------------------
// Drehgeber
//----------------------------------------------------------------------
uint8_t inc = 0, dec = 0, outa;
//----------------------------------------------------------------------

// Traffic und Info Button auswerten, ADC Wert
//----------------------------------------------------------------------
void traffic_info_button (uint16_t value)
{
	if (value > NAVI_DEFAULT)
	{
		komfort_in.Traffic = 0;
		komfort_in.Info = 0;
	}
	else if ((value > NAVI_TRAFFIC_U) && (value < NAVI_TRAFFIC_O))
	{
		komfort_in.Traffic = 1;
		komfort_in.Info = 0;
	}
	else if ((value > NAVI_INFO_U) && (value < NAVI_INFO_O))
	{
		komfort_in.Traffic = 0;
		komfort_in.Info = 1;
	}
}
//----------------------------------------------------------------------

// Return und Navi Button auswerten, ADC Wert
//----------------------------------------------------------------------
void return_navi_button (uint16_t value)
{
	if (value > NAVI_DEFAULT)
	{
		komfort_in.Return = 0;
		komfort_in.Navi= 0;
	}
	else if ((value > NAVI_RETURN_U) && (value < NAVI_RETURN_O))
	{
		komfort_in.Return = 1;
		komfort_in.Navi = 0;
	}
	else if ((value > NAVI_NAVI_U) && (value < NAVI_NAVI_O))
	{
		komfort_in.Return = 0;
		komfort_in.Navi = 1;
	}
}
//----------------------------------------------------------------------

// Drehgeber abfragen und auswerten
//----------------------------------------------------------------------
void drehgeber (void)
{
	if ((komfort_in.OutA != 1) && (outa == 1))
	{
		outa = 0;

		if (komfort_in.OutB != 1)
		{
			dec = 1;
		}
	}
	else if ((komfort_in.OutA == 1) && (outa != 1))
	{
		outa = 1;

		if (komfort_in.OutB != 1)
		{
			inc = 1;
		}
	}
}
//----------------------------------------------------------------------
