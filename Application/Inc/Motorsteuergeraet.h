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
// Motorsteuergeraet neu
#define MOTOR_CAN_SAFETY							0x139					// Shutdown Circuit Motorsteuergeraet, Sicherheitsrelevante Daten
#define MOTOR_CAN_DIGITAL_OUT						0x240					// Digitale Ausgaenge Motorsteuergeraet, Alle digitalen Ausgaenge
#define MOTOR_CAN_DIGITAL_IN						0x241					// Digitale Eingaenge Motorsteuergeraet, Alle digitalen Eingaenge
#define MOTOR_CAN_ANALOG_IN							0x242					// Analogwerte Motorsteuergerat, Gaspedal, Bremsdruck, Info, Return, KlimaFlap, KL15
#define MOTOR_CAN_TEMPERATUR						0x539					// Temperatur Motorsteuergeraet, PCB, Bremsdrucktemperatur, Kuehlwassertemperatur
//----------------------------------------------------------------------
// Motorsteuergeraet alt
//----------------------------------------------------------------------
#define MOTOR_CAN_DREHZAHL							0x280					// Motorsteuergerät ID MotorSTG1
#define MOTOR_CAN_MOTOR2							0x288					// Motorsteuergerät ID MotorSTG2
#define MOTOR_CAN_GASPEDAL							0x380					// Motorsteuergerät ID MotorSTG3
#define MOTOR_CAN_GRA								0x388					// Motorsteuergerät ID MotorSTG4
#define MOTOR_CAN_LEUCHTEN							0x480					// Motorsteuergerät ID MotorSTG5
#define MOTOR_CAN_GAS								0x488					// Motorsteuergerät ID MotorSTG6
#define MOTOR_CAN_FLEXIA							0x580					// Motorsteuergerät ID MotorFlexia
//----------------------------------------------------------------------
// CAN-IDs auf dem BUS Fahrzeug intern
//----------------------------------------------------------------------
#define LENKWINKEL_CAN								0x0C2					// CAN ID Lenkwinkelsensor
#define BEMSE1_CAN									0x1A0
#define BEMSE2_CAN									0x4A0
#define BEMSE3_CAN									0x4A8
#define BEMSE4_CAN									0x5A0
#define KOMBI1_CAN									0x320
#define KOMBI2_CAN									0x420
#define KOMBI3_CAN									0x520
#define KLIMA_CAN									0x5E0
#define xxx_CAN										0x3D0
#define xx_CAN										0x5DE					// Immer aktive, außer im Sleep
#define x_CAN										0x010					// Einmalig gesendet wenn Schlüssel auf Stufe 2
#define xy_CAN										0x011					// EInmalig gesendet wenn Schlüssel auf Stufe 2
//----------------------------------------------------------------------

// Definiere CAN Strukturen
//----------------------------------------------------------------------
typedef union __motor1_tag {
	struct {
		uint8_t xxxx : 4;													// Ersten 4 Bit
		uint8_t Bremse : 1;													// Bit 3 des ersten Bytes
		uint8_t xx : 2;														// Bit 1 und 2
		uint8_t Kupplung : 1;												// Bit 0
		uint8_t leer1;														// Byte 6, Leer Byte
		uint16_t Drehzahl;													// Byte 5, Drehzahl Low, Byte 4 Drehzahl high, Wert/4=Drehzahl
		uint8_t leer2;														// Byte 3, Leer Byte
		uint8_t Winkel_Drosselklape;										// Byte 2, Drosselklappe
		uint8_t leer3;														// Byte 1, Leer Byte
		uint8_t Oeldruck;													// Byte 0, Öldruck, Verbrauch in Liter
	};

	uint8_t output[8];														// 8 Byte
} motor1_tag;
//----------------------------------------------------------------------
typedef union __motor2_tag {
	struct {
		uint8_t Sicherheit;													// Byte 7, Vier Werte wiedeholend, je 4 mal, 07, 53, 8F, D9
		uint8_t xxxx;														// Byte 6, ??
		uint8_t Bremse;														// Byte 5, Bremsschalter, 13, 10, 02, 00
		uint8_t leer1;														// Byte 4, Leer Byte
		uint8_t leer2;														// Byte 3, Leer Byte
		uint8_t xx;															// Byte 2, Leer Byte
		uint8_t leer3;														// Byte 1, Leer Byte
		uint8_t leer4;														// Byte 0, Leer Byte
	};

	uint8_t motor2output[8];												// 8 Byte
} motor2_tag;
//----------------------------------------------------------------------

// Definiere globale Variablen
//----------------------------------------------------------------------
extern motor1_tag motor1;													// Variable fuer Motor CAN-Nachricht 1 definieren
extern motor2_tag motor2;													// Variable fuer Motor CAN-Nachricht 2 definieren
//----------------------------------------------------------------------

#endif /* MOTORSTEUERGERAET_H_ */
//----------------------------------------------------------------------
