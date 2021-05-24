//----------------------------------------------------------------------
// Titel	:	Motorsteuergeraet.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	24.05.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef MOTORSTEUERGERAET_H_
#define MOTORSTEUERGERAET_H_
//----------------------------------------------------------------------

// CAN-IDs definieren
//----------------------------------------------------------------------
#define CAN_SAFETY									0x139					// Shutdown Circuit Motorsteuergeraet, Sicherheitsrelevante Daten
#define CAN_DIGITAL_OUT								0x240					// Digitale Ausgaenge Motorsteuergeraet, Alle digitalen Ausgaenge
#define CAN_DIGITAL_IN								0x241					// Digitale Eingaenge Motorsteuergeraet, Alle digitalen Eingaenge
#define CAN_ANALOG_IN								0x242					// Analogwerte Motorsteuergerat, Gaspedal, Bremsdruck, Info, Return, KlimaFlap, KL15
#define CAN_TEMPERATUR								0x539					// Temperatur Motorsteuergeraet, PCB, Bremsdrucktemperatur, Kuehlwassertemperatur
//----------------------------------------------------------------------

#endif /* MOTORSTEUERGERAET_H_ */
//----------------------------------------------------------------------
