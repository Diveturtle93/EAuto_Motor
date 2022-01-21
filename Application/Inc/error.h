//----------------------------------------------------------------------
// Titel	:	Error.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.01.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef ERROR_H_
#define ERROR_H_
//----------------------------------------------------------------------

// Definiere Debug Symbol
//----------------------------------------------------------------------
//#define HAL_DEBUG
//----------------------------------------------------------------------

// Festlegen der Fehlercodes
//----------------------------------------------------------------------
#define ERROR_NONE						0
#define ERROR_GASPEDAL					1
#define ERROR_BREMSPEDAL				2
#define ERROR_SDC_SPANNUNG				3
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void hal_error(uint8_t status);
void software_error(uint8_t errorcode);
void ITM_SendString(char *text);
void ITM_SendNumber(long number);
void ITM_SendFloat(double number, int digits);
//----------------------------------------------------------------------

#endif /* INC_ERROR_H_ */
//----------------------------------------------------------------------
