//----------------------------------------------------------------------
// Titel	:	WS2812.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Dec 1, 2023
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Bibliothek benoetigt Timer 3 PWM Channel und DMA
// Konfiguration fuer den Timer muss am Motorsteuergeraet sein:
// Clock Source:					Interne Clock
// Channel2:						PWM Generation CH2
// Prescaler:						0
// Counter:							Up
// Periode:							135 - 1
// Internal Clock division:			0
// Auto-Reload:						Disable
// Master/Slave:					Disable
// Trigger Event:					Reset
// Mode:							PWM-Mode 1
// Pulse:							0
// Output compare Preload:			Enable
// Fast Mode:						Enable
// CH Polarity:						Low

// Interrupts
// Timer 3 Global:					Enable
// DMA 1 Channel 5:					Enable

// Pin Config
// Mode:							Alternative Push Pull
// Pull up/Pull down:				No
// Speed:							High

// DMA
// Mode:							Normal
// Increment:						Nur Memory
// Data size:						Half Word / Half word
// Direction:						Memory to Peripheral
// Priority:						High

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_WS2812_H_
#define INC_WS2812_H_
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
#define MAX_LED					1
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void Set_LED (uint8_t LED_Num, uint8_t red, uint8_t green, uint8_t blue);		// Setze die Farben der einzelnen LEDs
void WS2812_Send_Wait (void);													// Sende Daten als PWM, mit Wartezeit
uint8_t WS2812_Send (void);														// Sende Daten als PWM, keine Wartezeit
//----------------------------------------------------------------------

#endif /* INC_WS2812_H_ */
//----------------------------------------------------------------------
