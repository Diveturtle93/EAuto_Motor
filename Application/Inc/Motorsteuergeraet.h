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

// Programmversion definieren
//----------------------------------------------------------------------
#define MAJOR 0																// Motorsteuergeraet Major version Number
#define MINOR 1																// Motorsteuergeraet Minor version Number

// Include Project Header
//----------------------------------------------------------------------
#include "BasicUart.h"
#include "adc_inputs.h"
#include "app_info.h"
#include "Bamocar.h"
#include "error.h"
#include "inputs.h"
#include "Bamocar.h"
#include "millis.h"
#include "outputs.h"
#include "pedale.h"
#include "rtd_sound.h"
#include "SystemInfo.h"
#include "statemaschine.h"
#include "CAN_Bus.h"
#include "WS2812.h"
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

// Motorsteuergeraet vorhanden
//----------------------------------------------------------------------
#define BMS_AVALIBLE								0						// 0 = Nicht vorhanden, 1 = vorhanden
#define BAMOCAR_AVAILIBLE							0						// 0 = Nicht vorhanden, 1 = vorhanden
#define STROM_HV_AVAILIBLE							0						// 0 = Nicht vorhanden, 1 = vorhanden
#define STROM_LV_AVAILIBLE							0						// 0 = Nicht vorhanden, 1 = vorhanden
#define KOMBIINSTRUMENT_AVALIBLE					1						// 0 = Nicht vorhanden, 1 = vorhanden
//----------------------------------------------------------------------

//----------------------------------------------------------------------
#if TISCHAUFBAU == 1
#warning "Programm ist fuer Tischaufbau kompiliert!!"
#elif
#warning "Programm ist fuer Auto kompiliert!!"
#endif
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// TODO:

//----------------------------------------------------------------------

// CAN-IDs definieren
//----------------------------------------------------------------------
// Motorsteuergeraet neu
//----------------------------------------------------------------------
#define MOTOR_CAN_SAFETY							0x139					// Shutdown Circuit Motorsteuergeraet, Sicherheitsrelevante Daten
#define MOTOR_CAN_STATUS							0x505					// Motorsteuergeraet Status
#define MOTOR_CAN_DIGITAL_OUT						0x581					// Digitale Ausgaenge Motorsteuergeraet, Alle digitalen Ausgaenge
#define MOTOR_CAN_DIGITAL_IN						0x582					// Digitale Eingaenge Motorsteuergeraet, Alle digitalen Eingaenge
#define MOTOR_CAN_ANALOG_IN							0x583					// Analogwerte Motorsteuergeraet, Gaspedal, Bremsdruck, Info, Return, KlimaFlap, KL15
#define MOTOR_CAN_TEMPERATUR						0x584					// Temperatur Motorsteuergeraet, PCB, Bremsdrucktemperatur, Kuehlwassertemperatur
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
// Batteriemanagement-System neu
//----------------------------------------------------------------------
#define BMS_CAN_SAFETY								0x138					// Shutdown Circuit Batteriemanagement, Sicherheitsrelevante Daten
#define BMS_CAN_DIGITAL_OUT							0x237					// Digitale Ausgaenge Batteriemanagement, Alle digitalen Ausgaenge
#define BMS_CAN_DIGITAL_IN							0x238					// Digitale Eingaenge Batteriemanagement, Alle digitalen Eingaenge
#define BMS_CAN_ANALOG_IN							0x239					// Analogwerte Batteriemanagement, Spannung Relais, PCB
#define BMS_CAN_TEMPERATUR							0x538					// Temperatur Batteriemanagement, Temperatursensor 1 bis 4
#define BMS_CAN_STATUS								0x560					// Status BMS
#define BMS_CAN_IMD									0x565					// Status IMD
#define BMS_CAN_Zellen11							0x640					// Batterie-Zellen 1-4 Modul 1
#define BMS_CAN_Zellen12							0x641					// Batterie-Zellen 5-8 Modul 1
#define BMS_CAN_Zellen13							0x642					// Batterie-Zellen 9-12 Modul 1
#define BMS_CAN_Zellen21							0x643					// Batterie-Zellen 1-4 Modul 2
#define BMS_CAN_Zellen22							0x644					// Batterie-Zellen 5-8 Modul 2
#define BMS_CAN_Zellen23							0x645					// Batterie-Zellen 9-12 Modul 2
#define BMS_CAN_Temperatur11						0x740					// Batterie-Temperatur 1-4 Modul 1
#define BMS_CAN_Temperatur12						0x741					// Batterie-Temperatur 5-8 Modul 1
#define BMS_CAN_Temperatur13						0x742					// Batterie-Temperatur 9-12 Modul 1
#define BMS_CAN_Temperatur21						0x743					// Batterie-Temperatur 1-4 Modul 2
#define BMS_CAN_Temperatur22						0x744					// Batterie-Temperatur 5-8 Modul 2
#define BMS_CAN_Temperatur23						0x745					// Batterie-Temperatur 9-12 Modul 2
//----------------------------------------------------------------------
// Stromsensor HV-Kreis
//----------------------------------------------------------------------
#define STROM_HV_COMMAND_RX							0x411					// Befehl an Stromsensor senden
#define STROM_HV_COMMAND_TX							0x511					// Befehl von Stromsensor empfanden
#define STROM_HV_CAN_I								0x521					// Aktueller Stromverbrauch
#define STROM_HV_CAN_U1								0x522					// Aktuelle Spannung U1
#define STROM_HV_CAN_U2								0x523					// Aktuelle Spannung U2
#define STROM_HV_CAN_U3								0x524					// Aktuelle Spannung U3
#define STROM_HV_CAN_T								0x525					// Aktuelle Temperatur
#define STROM_HV_CAN_W								0x526					// Power (U1 x I)
#define STROM_HV_CAN_AS								0x527					// Gesamtstromvrbrauch
#define STROM_HV_CAN_WH								0x528					// Gesamtenergie (U1 x I)
//----------------------------------------------------------------------
// Stromsensor LV-Kreis
//----------------------------------------------------------------------
//#define STROM_LV_COMMAND_RX							0x412					// Befehl an Stromsensor senden
//#define STROM_LV_COMMAND_TX							0x512					// Befehl von Stromsensor empfanden
//#define STROM_LV_CAN_I								0x521					// Aktueller Stromverbrauch
//#define STROM_LV_CAN_U1								0x522					// Aktuelle Spannung U1
//#define STROM_LV_CAN_U2								0x523					// Aktuelle Spannung U2
//#define STROM_LV_CAN_U3								0x524					// Aktuelle Spannung U3
//#define STROM_LV_CAN_T								0x525					// Aktuelle Temperatur
//#define STROM_LV_CAN_W								0x526					// Power (U1 x I)
//#define STROM_LV_CAN_AS								0x527					// Gesamtstromvrbrauch
//#define STROM_LV_CAN_WH								0x528					// Gesamtenergie (U1 x I)
//----------------------------------------------------------------------

// Zeit Intervalle
//----------------------------------------------------------------------
#define CAN_TIMEOUT									10000					// Zeit 10s bis CAN Timeout auftritt
#define ERROR_RESET									30000					// Zeit 30s bis Error Zurueckgesetzt werden kann
#define WARNING_RESET								300000					// Zeit 5min bis Warning Zurueckgesetzt werden kann
//----------------------------------------------------------------------

// Define Statemaschine Typedefines
//----------------------------------------------------------------------
typedef enum
{
	Start,																	// 0 Starte Motorsteuergeraet
	Ready,																	// 1 Motorsteuergeraet gestartet
	KL15,																	// 2 KL15 aktiv
	Anlassen,																// 3 Anlasser betaetigt
	Precharge,																// 4 Precharge Fahrzeug
	ReadyToDrive,															// 5 Motorsteuergeraet bereit fuer Fahrmodus
	Drive,																	// 6 Fahrzeug im Fahrmodus
	Standby,																// 7 Auto wird abgeschaltet, Zeitverzoegerung bis Motorsteuergeraet ausgeht
	Ausschalten,															// 8 Motorsteuergeraet ausschalten
	StateNormal = 0x10,														// 16 Normalzustand
	StateWarning = 0x20,													// 32 Warnung
	StateError = 0x40,														// 64 Fehler
	CriticalError = 0x80,													// 128 Critischer Fehler
} states;
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t State : 4;													// State der Statemaschine
		uint8_t Normal : 1;													// Statemaschine normal
		uint8_t Warning : 1;												// Statemaschine warning
		uint8_t Error : 1;													// Statemaschine error
		uint8_t CriticalError : 1;											// Statemaschine kritscher error
	};

	uint8_t status;									// 1 Byte
} Motor_state;
//----------------------------------------------------------------------

// Definiere CAN Strukturen
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t Leerlauf : 1;												// Byte 0, Bit 0
		uint8_t FehlerPWG : 1;												// Byte 0, Bit 1, ???
		uint8_t Kickdown : 1;												// Byte 0, Bit 2
		uint8_t Kupplung : 1;												// Byte 0, Bit 3
		uint8_t QuitASR : 1;												// Byte 0, Bit 4, ???
		uint8_t MomeingriffBremse : 1;										// Byte 0, Bit 5, ???
		uint8_t MomeingriffGetrieb : 1;										// Byte 0, Bit 6, ???
		uint8_t Momentungenau : 1;											// Byte 0, Bit 7, ???
		uint8_t MomMotor;													// Byte 1, ???
		uint16_t Drehzahl;													// Byte 2, Drehzahl Low, Byte 3 Drehzahl high, Wert/4=Drehzahl
		uint8_t MomMotorKorrigiert;											// Byte 4, ???
		uint8_t Fahrpedalstellung;											// Byte 5, Drosselklappe
		uint8_t MomVerlust;													// Byte 6, ???
		uint8_t MomFahrerwunsch;											// Byte 7, ???
	};

	uint8_t motor280output[8];												// 8 Byte
} motor280_tag;
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t MuxInfo : 6;												// Byte 0, Bit 0 bis 5, 07, 53, 8F, D9
		uint8_t MuxCode : 2;												// Byte 0, Bit 6 und 7, 07, 53, 8F, D9
		uint8_t KuehlTemp;													// Byte 1, Kuehlmitteltemperatur
		uint8_t BremseNO : 1;												// Byte 2, Bit 0, Bremsschalter, 13, 10, 02, 00
		uint8_t BremseRedundant : 1;										// Byte 2, Bit 1, Redundanter Bremsschalter NO ?
		uint8_t FehlerWTF : 1;												// Byte 2, Bit 2, ???
		uint8_t KlimaStelle : 1;											// Byte 2, Bit 3, ???
		uint8_t Normalbetrieb : 1;											// Byte 2, Bit 4, ???
		uint8_t OBD2 : 1;													// Byte 2, Bit 5, ???
		uint8_t GRA_Status : 2;												// Byte 2, Bit 6 und 7, 00 = aus, 01 = ein, 10 = uebersteuert, 11 = frei
		uint8_t FahrzeugGeschwindigkeit;									// Byte 3, Fahrzeuggeschwindigkeit
		uint8_t GRA_Geschwindigkeit;										// Byte 4, Sollgeschwindigkeit GRA
		uint8_t LeerlaufDrehzahl;											// Byte 5, ???
		uint8_t MomBegrenzung;												// Byte 6, ???
		uint8_t frei;														// Byte 7, Leer Byte
	};

	uint8_t motor288output[8];												// 8 Byte
} motor288_tag;
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t Vorgluehen : 1;												// Byte 0, Bit 0, ???
		uint8_t DSP : 1;													// Byte 0, Bit 1, ???
		uint8_t leer1 : 1;													// Byte 0, Bit 2, ???
		uint8_t frei1 : 1;													// Byte 0, Bit 3
		uint8_t FahrpedalUngenau : 1;										// Byte 0, Bit 4, ???
		uint8_t leer2 : 1;													// Byte 0, Bit 5, ???
		uint8_t MotorGesperrt : 1;											// Byte 0, Bit 6, ???
		uint8_t frei2 : 1;													// Byte 0, Bit 7
		uint8_t LuftTemp;													// Byte 1, ???
		uint8_t Gaspedal;													// Byte 2, Gaspedal, ???
		uint16_t MomRad : 12;												// Byte 3, 12 Bit, Radwunschmoment, ???
		uint16_t VorMomRad : 1;												// Byte 4, Bit 4, Radwunschmoment Vorzeichen, ???
		uint16_t frei3 : 1;													// Byte 4, Bit 5
		uint16_t EGAS : 1;													// Byte 4, Bit 6, ???
		uint16_t ECO : 1;													// Byte 4, Bit 7, ???
		uint8_t MotordrehBeeinflussung;										// Byte 5, ???
		uint8_t MotorDrehzahl;												// Byte 6, Wunschmoment Motor, ???
		uint8_t leer3;														// Byte 7, ???

	};

	uint8_t motor380output[8];												// 8 Byte
} motor380_tag;
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t Counter;													// Byte 0, Zaehler
		uint8_t Hauptschalter : 1;											// Byte 1, Bit 0, ???
		uint8_t TipAus : 1;													// Byte 1, Bit 1, ???
		uint8_t TipSet : 1;													// Byte 1, Bit 2, ???
		uint8_t TipBeschleunigen : 1;										// Byte 1, Bit 3, ???
		uint8_t Beschleunigen : 1;											// Byte 1, Bit 4, ???
		uint8_t Verzoegern : 1;												// Byte 1, Bit 5, ???
		uint8_t Bedienfehler : 1;											// Byte 1, Bit 6, ???
		uint8_t frei : 1;													// Byte 1, Bit 7
		uint8_t Checksum;													// Byte 2

	};

	uint8_t motor388output[3];												// 3 Byte
} motor388_tag;
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t MuxInfo : 6;												// Byte 0, Bit 0 bis 5, 14, 56, A3, C0
		uint8_t MuxCode : 2;												// Byte 0, Bit 6 und 7, 14, 56, A3, C0
		uint8_t leer1 : 1;													// Byte 1, Bit 0, ???
		uint8_t VorgluehenLED : 1;											// Byte 1, Bit 1, Vorgluehen LED
		uint8_t leer2 : 1;													// Byte 1, Bit 2, EPC Leuchte, Nicht Verwendbar
		uint8_t MotorLED : 1;												// Byte 1, Bit 3, Motorelektronik LED
		uint8_t leer3 : 1;													// Byte 1, Bit 4, ???
		uint8_t KlimaAus : 1;												// Byte 1, Bit 5, ???
		uint8_t KennfeldKuehlung : 1;										// Byte 1, Bit 6, ???
		uint8_t leer4 : 1;													// Byte 1, Bit 7, ???
		int16_t Verbrauch;													// Byte 2, Verbrauch seit KL15 an
		uint8_t Kuehlluefter;												// Byte 4, ???
		uint8_t KaeltemittelDruck;											// Byte 5, ???
		uint8_t frei1 : 2;													// Byte 6, Bit 0 und 1
		uint8_t GRALED : 1;													// Byte 6, Bit 2, ???
		uint8_t frei2 : 1;													// Byte 6, Bit 3
		uint8_t MotorText : 4;												// Byte 6, Bit 4 bis 7, ???
		uint8_t frei3;														// Byte 7
	};

	uint8_t motor480output[8];												// 8 Byte
} motor480_tag;
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t Checksum;													// Byte 0
		uint8_t SollMom;													// Byte 1, ???
		uint8_t IstMom;														// Byte 2, ???
		int16_t HoehenInfo;													// Byte 3, ???
		uint8_t GRASollBeschleunigung;										// Byte 4, ???
		uint8_t frei1;														// Byte 5
		uint8_t frei2;														// Byte 6
		uint8_t frei3 : 4;													// Byte 7, Bit 0 bis 3
		uint8_t Counter : 4;												// Byte 7, Bit 4 bis 7, Zaehler
	};

	uint8_t motor488output[8];												// 8 Byte
} motor488_tag;
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t Counter : 4;												// Byte 0, Bit 0 bis 3
		uint8_t frei1 : 4;													// Byte 0, Bit 4 bis 7
		uint8_t Russ;														// Byte 1, ???
		uint8_t Verschleiss;												// Byte 2, ???
	};

	uint8_t motor580output[3];												// 3 Byte
} motor580_tag;
//----------------------------------------------------------------------

// Definiere globale Variablen
//----------------------------------------------------------------------
extern motor280_tag motor280;												// Variable fuer Motor CAN-Nachricht 1 definieren
//extern motor288_tag motor288;												// Variable fuer Motor CAN-Nachricht 2 definieren
//extern motor380_tag motor380;												// Variable fuer Motor CAN-Nachricht 3 definieren
//extern motor388_tag motor388;												// Variable fuer Motor CAN-Nachricht 4 definieren
extern motor480_tag motor480;												// Variable fuer Motor CAN-Nachricht 5 definieren
//extern motor488_tag motor488;												// Variable fuer Motor CAN-Nachricht 6 definieren
//extern motor580_tag motor580;												// Variable fuer Motor CAN-Nachricht 7 definieren
//----------------------------------------------------------------------

#endif /* INC_MOTORSTEUERGERAET_H_ */
//----------------------------------------------------------------------
