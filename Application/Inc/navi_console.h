//----------------------------------------------------------------------
// Titel	:	navi_console.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jun 17, 2024
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_NAVI_CONSOLE_H_
#define INC_NAVI_CONSOLE_H_
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
// Navibedienelement Schwellwerte
//----------------------------------------------------------------------
#define NAVI_TRAFFIC_U									1600				// Traffic Taste gedrueckt, 1650
#define NAVI_TRAFFIC_O									1700				// Traffic Taste gedrueckt, 1650
#define NAVI_INFO_U										500					// Info Taste gedrueckt, 570
#define NAVI_INFO_O										600					// Info Taste gedrueckt, 570
#define NAVI_RETURN_U									1600				// Traffic Taste gedrueckt, 1650
#define NAVI_RETURN_O									1700				// Traffic Taste gedrueckt, 1650
#define NAVI_NAVI_U										500					// Info Taste gedrueckt, 570
#define NAVI_NAVI_O										600					// Info Taste gedrueckt, 570
#define NAVI_DEFAULT									3750				// Wenn keine Taste gedrueckt dann ist der ADC Wert groesser 3750
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void traffic_info_button (uint16_t value);									// ADC Wert Traffic Button auswerten
void return_navi_button (uint16_t value);									// ADC Wert Return Button auswerten
//----------------------------------------------------------------------

#endif /* INC_NAVI_CONSOLE_H_ */
//----------------------------------------------------------------------
