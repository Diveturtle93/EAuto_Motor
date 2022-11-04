//----------------------------------------------------------------------
// Titel	:	millis.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	01.06.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfügen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfügen der STM Include-Dateien
//----------------------------------------------------------------------
#include "stm32f7xx_hal.h"
//----------------------------------------------------------------------

// Einfügen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "millis.h"
//----------------------------------------------------------------------

uint32_t millis(void)
{
	return HAL_GetTick();
}