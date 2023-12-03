//----------------------------------------------------------------------
// Titel	:	WS2812.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Dec 1, 2023
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_WS2812_H_
#define INC_WS2812_H_
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
#define MAX_LED					1
#define USE_BRIGHTNESS 			0
#define PI 						3.14159265
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void Set_LED (uint8_t LED_Num, uint8_t green, uint8_t red, uint8_t blue);
void Set_Brightness (uint8_t brightness);
void WS2812_Send (void);
//----------------------------------------------------------------------

#endif /* INC_WS2812_H_ */
//----------------------------------------------------------------------
