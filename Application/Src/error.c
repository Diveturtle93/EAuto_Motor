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
#include "outputs.h"
#include "inputs.h"
//----------------------------------------------------------------------

// Hal Error auswerten und ausgeben
//----------------------------------------------------------------------
void hal_error(uint8_t status)
{
#ifdef HAL_DEBUG
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
	leuchten_out.RedLed = 1;												// Setze Variable
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);	// Fehler LED einschalten

	// Schalte Ok LED aus
	leuchten_out.GreenLed = 0;												// Zuruechsetzen Variable
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);// Fehler LED ausschalten

	// Schalte Fehler LED ein
	leuchten_out.RedLed = 1;												// Setze Variable
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);	// Fehler LED einschalten

	// Schalte Ok LED aus
	leuchten_out.GreenLed = 0;												// Zuruechsetzen Variable
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);// OK LED ausschalten

	// Schalte SDC_Motor aus
	system_out.MotorSDC = 0;												// Zuruecksetzen Variable
	HAL_GPIO_WritePin(MOTOR_SDC_OUT_GPIO_Port, MOTOR_SDC_OUT_Pin, system_out.MotorSDC);// SDC oeffnen
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

// Debug Nachricht ueber SWO senden
// Nachricht SWO ITM Data Console
// Core Clock := Maximalfrequenz ; HCLK fuer Serial Wire Viewer
// Im String #GRN# oder #RED# oder #ORG# erscheint die Nachricht in einer Farbe
//----------------------------------------------------------------------
void ITM_SendString(char *text)
{
#ifdef DEBUG
	// So lange *text != '\0', also ungleich dem "String-Endezeichen(Terminator)"
	while(*text)															// Starte Pointerschleife
	{
		ITM_SendChar(*text);												// Sende ITM Zeichen
		text++;																// Pointer hochzaehlen
	}
#endif
}
//----------------------------------------------------------------------

// Debug Nummer ueber SWO senden
//----------------------------------------------------------------------
void ITM_SendNumber(long number)
{
#ifdef DEBUG
	// Variablen definieren
	unsigned char buf[8 * sizeof(long)];
	unsigned int i = 0;

	// Wenn Nummer 0 ist
	if(number == 0)
	{
		ITM_SendChar('0');													// Sende 0
		return;																// Beende Funktion
	}

	// Wenn Zahl negativ ist
	if(number < 0)
	{
		ITM_SendChar('-');													// Vorzeichen senden
		number = number * -1;												// Nummer invertieren
	}

	// Berechne Ziffern bis Zahl 0 ist
	while(number > 0)
	{
		// Ziffern in Puffer schreiben
		buf[i++] = number % 10;												// Rest berechnen
		number = number / 10;												// Dividiere durch 10
	}

	// Sende Zeichen
	for(; i > 0; i--)
	{
		ITM_SendChar('0' + buf[i-1]);
	}
#endif
}
//----------------------------------------------------------------------

// Debug Float ueber SWO senden
//----------------------------------------------------------------------
void ITM_SendFloat(double number, int digits)
{
#ifdef DEBUG
	int i = 0;

	// Wenn Zahl negativ ist
	if(number < 0.0)
	{
		ITM_SendChar('-');													// Vorzeichen senden
		number = number * -1;												// Nummer invertieren
	}

	// Runde Zahl auf die angegebene Nachkommazahl, (1.999, 2) wird als "2.00" angezeigt
	double rounding = 0.5;

	// Schleife mit anzahl Nachkommastellen
	for(i = 0; i < digits; i++)
	{
		rounding = rounding / 10.0;
	}

	number = number + rounding;

	// Ziehe Integer Wert aus der Zahl
	unsigned long int_part = (unsigned long) number;						// Integerwert in Float formatieren
	double remainder = (double)(number - (double)int_part);					// Nachkommastellen isolieren
	ITM_SendNumber(int_part);												// Sende Intergerwert

	// Wenn Nachkommastellen groeßer 0 ist
	if (digits > 0)
	{
		ITM_SendChar('.');													// Sende Dezimalpunkt
	}

	int toprint;

	// Solange Ziffern senden wie Nachkommastellen benoetigt werden
	while(digits-- > 0)
	{
		remainder = remainder * 10.0;										// Nachkommastelle in Interger umrechnen
		toprint = (int)remainder;											// Nachkommastelle in Interger umrechnen
		ITM_SendNumber(toprint);											// Sende Ziffer
		remainder = remainder - toprint;									// Intergerwerte aus Float rausrechnen
	}
#endif
}
//----------------------------------------------------------------------
