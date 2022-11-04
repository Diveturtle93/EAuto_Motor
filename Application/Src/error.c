//----------------------------------------------------------------------
// Titel	:	Error.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.01.2021
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
#include "error.h"
#include "BasicUart.h"
//----------------------------------------------------------------------

// Hal Error auswerten und ausgeben
//----------------------------------------------------------------------
void hal_error(uint8_t status)
{
#ifdef DEBUG
	if (status == HAL_OK) {													// HAL OK
		uartTransmit("HAL OK\n", 7);
	}
	else if (status == HAL_ERROR) {											// HAL Error
		uartTransmit("HAL ERROR\n", 10);
	}
	else if (status == HAL_BUSY) {											// HAL Beschaeftigt
		uartTransmit("HAL BUSY\n", 9);
	}
	else if (status == HAL_TIMEOUT) {										// HAL Timeout
		uartTransmit("HAL TIMEOUT\n", 12);
	}
#endif
}
//----------------------------------------------------------------------

// Diagnose Funktion falls ein Fehler auftritt
//----------------------------------------------------------------------
void software_error(uint8_t errorcode)
{
	__disable_irq();														// Interrupts deaktivieren

	// Schalte Fehler LED ein
	//leuchten_out.RedLed = 1;												// Setze Variable
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET);		// Fehler LED einschalten

	// Schalte Ok LED aus
	//leuchten_out.GreenLed = 0;											// Zuruechsetzen Variable
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);	// Fehler LED ausschalten

#ifdef DEBUG																// Serielle Kommunukation nur waehrend Debugging
#define SOFTERRORMESSAGE			"\nSoftware Error Handler ausgeloest\n"	// Ausgabe das Fehler aufgetreten ist
	uartTransmit(SOFTERRORMESSAGE,sizeof(SOFTERRORMESSAGE));

#define ERRORCODE					"Error Code:\t"							// Ausgabe des Fehlers anhand von Fehlercode
	uartTransmit(ERRORCODE,sizeof(ERRORCODE));
	uartTransmitNumber(errorcode, 10);										// Fehlercode ausgeben
#endif
	while (1);																// Endlosschleife
}
//----------------------------------------------------------------------
