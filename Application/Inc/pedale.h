//----------------------------------------------------------------------
// Titel	:	pedale.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	03.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_PEDALE_H_
#define INC_PEDALE_H_
//----------------------------------------------------------------------

// Definiere Debug Symbol
//----------------------------------------------------------------------
#ifdef DEBUG
	#define DEBUG_PEDALE
#endif
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
#define GAS_MIN_ADC							300								// Minimaler ADC-Wert
#define GAS_MAX_ADC							4095							// Maximaler ADC-Wert
//----------------------------------------------------------------------

// Fehler definieren
//----------------------------------------------------------------------
#define GAS_OK								0								// Minimaler ADC-Wert
#define GAS_VALUE_TOO_LOW					1								// Maximaler ADC-Wert
#define GAS_VALUE_TOO_HIGH					2								// Thresholdwert fuer Gaspedal ADC
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
uint16_t readTrottle(void);													// Gaspedal auswerten
void readBrake(void);														// Bremspedal auswerten
//----------------------------------------------------------------------

#endif /* INC_PEDALE_H_ */
//----------------------------------------------------------------------
