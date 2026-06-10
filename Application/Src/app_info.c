//----------------------------------------------------------------------
// Titel	:	app_info.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jul 16, 2023
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "app_info.h"
#include "Motorsteuergeraet.h"
//----------------------------------------------------------------------

// Application Informationen sammeln
//----------------------------------------------------------------------
void app_info(void)
{
  	// Teste serielle Schnittstelle
	#define START_STRING_UART		"!--- Motorsteuergeraet ---!\n"
	uartTransmit(START_STRING_UART, sizeof(START_STRING_UART));

	// Version der Software auf Uart ausgeben
	#define VERSION_STRING_UART		"Application Version: "
	uartTransmit(VERSION_STRING_UART, sizeof(VERSION_STRING_UART));
	uartTransmitNumber(MOTORSTEUERGERAET_MAJOR, 10);
	uartTransmit(".", 1);
	uartTransmitNumber(MOTORSTEUERGERAET_MINOR, 10);
	uartTransmit(".", 1);
	uartTransmitNumber(MOTORSTEUERGERAET_PATCH, 10);
	uartTransmit(".", 1);
	uartTransmitNumber(MOTORSTEUERGERAET_DEV, 10);
	uartTransmit("\n", 1);

  	// Sammelt Systeminformationen
  	collectSystemInfo();
	printResetSource(readResetSource());
}
//----------------------------------------------------------------------