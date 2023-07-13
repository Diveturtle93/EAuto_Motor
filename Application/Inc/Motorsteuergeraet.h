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
#ifndef INC_MOTORSTEUERGERAET_H_
#define INC_MOTORSTEUERGERAET_H_
//----------------------------------------------------------------------

// Include Project Header
//----------------------------------------------------------------------
#include "SystemInfo.h"
#include "BasicUart.h"
#include "inputs.h"
#include "outputs.h"
#include "error.h"
#include "Bamocar.h"
#include "millis.h"
#include "adc_inputs.h"
#include "pedale.h"
#include "rtd_sound.h"
//----------------------------------------------------------------------

// Define Revision of Motorsteuergeraet HW PCB
//----------------------------------------------------------------------
//#if REVISION == 255
//#error "Revision ist nicht definiert"
//#elif REVISION == 1
//#warning "PCB Revision 1.0 definiert"
//#elif REVISION == 2
//#warning "PCB Revision 1.1 definiert"
//#endif
//----------------------------------------------------------------------

// Tischaufbau
//----------------------------------------------------------------------
#define TISCHAUFBAU									1						// 0 = Auto, 1 = Tischaufbau
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// TODO:
//----------------------------------------------------------------------

// CAN-IDs definieren
//----------------------------------------------------------------------
// Motorsteuergeraet neu
//----------------------------------------------------------------------
#define MOTOR_CAN_SAFETY							0x139					// Shutdown Circuit Motorsteuergeraet, Sicherheitsrelevante Daten
#define MOTOR_CAN_DIGITAL_OUT						0x240					// Digitale Ausgaenge Motorsteuergeraet, Alle digitalen Ausgaenge
#define MOTOR_CAN_DIGITAL_IN						0x241					// Digitale Eingaenge Motorsteuergeraet, Alle digitalen Eingaenge
#define MOTOR_CAN_ANALOG_IN							0x242					// Analogwerte Motorsteuergerat, Gaspedal, Bremsdruck, Info, Return, KlimaFlap, KL15
#define MOTOR_CAN_TEMPERATUR						0x539					// Temperatur Motorsteuergeraet, PCB, Bremsdrucktemperatur, Kuehlwassertemperatur
//----------------------------------------------------------------------
// Motorsteuergeraet alt
//----------------------------------------------------------------------
#define MOTOR_CAN_DREHZAHL							0x280					// Motorsteuergeraet ID MotorSTG1
#define MOTOR_CAN_MOTOR2							0x288					// Motorsteuergeraet ID MotorSTG2
#define MOTOR_CAN_GASPEDAL							0x380					// Motorsteuergeraet ID MotorSTG3
#define MOTOR_CAN_GRA								0x388					// Motorsteuergeraet ID MotorSTG4
#define MOTOR_CAN_LEUCHTEN							0x480					// Motorsteuergeraet ID MotorSTG5
#define MOTOR_CAN_GAS								0x488					// Motorsteuergeraet ID MotorSTG6
#define MOTOR_CAN_FLEXIA							0x580					// Motorsteuergeraet ID MotorFlexia
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
#define LENKUNG1_CAN								0x3D0					// Nachricht unterdrueckt Fehlermeldung Kombiinstrument
#define LENKUNG2_CAN								0x5DE					// Immer aktive, außer im Sleep
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
		uint8_t leer1;														// Byte 1, Leer Byte
		uint16_t Drehzahl;													// Byte 2, Drehzahl Low, Byte 3 Drehzahl high, Wert/4=Drehzahl
		uint8_t leer2;														// Byte 4, Leer Byte
		uint8_t Winkel_Drosselklape;										// Byte 5, Drosselklappe
		uint8_t leer3;														// Byte 6, Leer Byte
		uint8_t Oeldruck;													// Byte 7, Oeldruck, Verbrauch in Liter
	};

	uint8_t output[8];														// 8 Byte
} motor280_tag;
//----------------------------------------------------------------------
typedef union __motor2_tag {
	struct {
		uint8_t Sicherheit;													// Byte 0, Vier Werte wiedeholend, je 4 mal, 07, 53, 8F, D9
		uint8_t xxxx;														// Byte 1, ??
		uint8_t Bremse;														// Byte 2, Bremsschalter, 13, 10, 02, 00
		uint8_t leer1;														// Byte 3, Leer Byte
		uint8_t leer2;														// Byte 4, Leer Byte
		uint8_t xx;															// Byte 5, Leer Byte
		uint8_t leer3;														// Byte 6, Leer Byte
		uint8_t leer4;														// Byte 7, Leer Byte
	};

	uint8_t motor2output[8];												// 8 Byte
} motor288_tag;
//----------------------------------------------------------------------
typedef union __motor3_tag {
	struct {
		uint8_t leer1;														// Byte 0, Leer Byte
		uint8_t leer2;														// Byte 1, Leer Byte
		uint8_t Gas1;														// Byte 2, Gaspedal
		uint8_t Gas2;														// Byte 3, Gaspedal
		uint8_t leer5;														// Byte 4, Leer Byte
		uint8_t leer6;														// Byte 5, Leer Byte
		uint8_t leer7;														// Byte 6, Leer Byte
		uint8_t leer8;														// Byte 7, Leer Byte

	};

	uint8_t motor2output[8];												// 8 Byte
} motor380_tag;
//----------------------------------------------------------------------
typedef union __motor5_tag {
	struct {
		uint8_t leer1;														// Byte 0, Leer Byte
		uint8_t leer21: 2;													// Byte 1, 2 leere Bits
		uint8_t EPC: 1;														// Byte 1, 2. Bit, EPC Leuchte
		uint8_t Motor: 1;													// Byte 1, 3. Bit, Motorleuchte
		uint8_t leer22: 4;													// Byte 1, 4 leere Bits
		uint8_t leer3;														// Byte 2, Leer Byte
		uint8_t leer4;														// Byte 3, Leer Byte
		uint8_t leer5;														// Byte 4, Leer Byte
		uint8_t leer6;														// Byte 5, Leer Byte
		uint8_t leer7;														// Byte 6, Leer Byte
		uint8_t leer8;														// Byte 7, Leer Byte
	};

	uint8_t motor2output[8];												// 8 Byte
} motor480_tag;
//----------------------------------------------------------------------

// Definiere globale Variablen
//----------------------------------------------------------------------
extern motor280_tag motor280;												// Variable fuer Motor CAN-Nachricht 1 definieren
extern motor288_tag motor288;												// Variable fuer Motor CAN-Nachricht 2 definieren
//----------------------------------------------------------------------

#endif /* INC_MOTORSTEUERGERAET_H_ */
//----------------------------------------------------------------------
