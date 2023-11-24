//----------------------------------------------------------------------
// Titel	:	Inputs.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	31.03.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_INPUTS_H_
#define INC_INPUTS_H_
//----------------------------------------------------------------------

// Define Debug Symbols
//----------------------------------------------------------------------
#define DEBUG_INPUT
//----------------------------------------------------------------------

// Eingangsstrukturen definieren
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t Kickdown : 1;					// 0						// Schalter Kickdown, Gaspedal
		uint8_t Leerlauf : 1;					// 1						// Schalter Leerlauf, Gaspedal
		uint8_t BremseNO : 1;					// 2						// Schalter Bremse normal Offen, Bremspedal
		uint8_t BremseNC : 1;					// 3						// Schalter Bremse normal geschlossen, Bremspedal
		uint8_t Kupplung : 1;					// 4						// Schalter Kupplung, Kupplungspedal
		uint8_t Recuperation : 1;				// 5						// Signal Recuperation
		uint8_t ECON : 1;						// 6						// Schalter ECON, Klimabedienteil
		uint8_t Anlasser : 1;					// 7						// Schalter Anlasser, Zuendanlassschalter
		uint8_t KL15 : 1;						// 8						// Schalter KL15, Zuendanlassschalter
		uint8_t DCDC_Inst : 1;					// 9						// Signal Working indicator, DCDC Wandler
		uint8_t Button1 : 1;					// A						// Schalter Button1
		uint8_t Button2 : 1;					// B						// Schalter Button2
		uint8_t Crash : 1;						// C						// Signal Crashsensor, Airbagsteuergeraet
		uint8_t Wakeup : 1;						// D						// Signal Wakeup
		uint8_t Bremsdruck_NO : 1;				// E						// Schalter Unterdruck normal Offen, Unterdrucksensor
		uint8_t Bremsdruck_NC : 1;				// F						// Schalter Unterdruck normal geschlossen, Unterdrucksensor
	};

	uint16_t systeminput;						// 2 Byte
} system_input_tag;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t EmergencyRun : 1;				// 0						// Signal Emergency Run
		uint8_t SDC0 : 1;						// 1						// Signal Sicherung, Shutdown-Circuit
		uint8_t AkkuSDC : 1;					// 2						// Signal Akku Ok, Shutdown-Circuit
		uint8_t BTB_SDC : 1;					// 3						// Signal BTB, Bamocar
		uint8_t DCDC_Fault : 1;					// 4						// Signal DCDC Wandler OK
		uint8_t SDC12V : 1;						// 5						// Sicherung von Shutdown-Circuit
		uint8_t Anlasser : 1;					// 6						// Abspeichern von Anlasser Signal
		uint8_t SDC_OK : 1;						// 7						// Shutdown-Circuit OK
	};

	uint8_t sdcinput;							// 1 Byte
} sdc_in_tag;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t ASR1 : 1;						// 0						// Schalter ASR1, Mittelkonsole
		uint8_t ASR2 : 1;						// 1						// Schalter ASR2, Mittelkonsole
		uint8_t ECO : 1;						// 2						// Schalter ECO, Mittelkonsole
		uint8_t BC_Rst_In : 1;					// 3						// Schalter BC-Reset, Lenkstockschalter Boardcomputer
		uint8_t BC_Up_In : 1;					// 4						// Schalter BC-Up, Lenkstockschalter Boardcomputer
		uint8_t BC_Down_In : 1;					// 5						// Schalter BC-Down, Lenkstockschalter Boardcomputer
		uint8_t BamoIn1 : 1;					// 6						// Signal Bamocar1, Bamocar
		uint8_t BamoIn2 : 1;					// 7						// Signal Bamocar2, Bamocar
		uint8_t Enter : 1;						// 8						// Schalter Enter, Navibedienteil
		uint8_t OutA : 1;						// 9						// Schalter OutA, Navibedienteil
		uint8_t OutB : 1;						// A						// Schalter OutB, Navibedienteil
		uint8_t GRA1 : 1;						// B						// Schalter GRA1, Lenkstockschalter Geschwindigkeitsregelanlage
		uint8_t GRA2 : 1;						// C						// Schalter GRA2, Lenkstockschalter Geschwindigkeitsregelanlage
		uint8_t GRA3 : 1;						// D						// Schalter GRA3, Lenkstockschalter Geschwindigkeitsregelanlage
		uint8_t GRA4 : 1;						// E						// Schalter GRA4, Lenkstockschalter Geschwindigkeitsregelanlage
		uint8_t Durchfluss : 1;					// F						// Signal Durchfluss, Durchflusssensor Wasserkreislauf
	};

	uint16_t komfortinput;						// 2 Byte
} komfort_in_tag;
//----------------------------------------------------------------------

// Definiere Konstanten
//----------------------------------------------------------------------
#define SYSTEM_INPUT					0b0000000000000000					// 16 Bit, 16 Systemeingaenge
#define KOMFORT_INPUT					0b0000000000000000					// 16 Bit, 16 Komforteingaenge
#define SDC_INPUT						0b00000000							// 8 Bit, 5 SDC-Eingaenge
//----------------------------------------------------------------------

// Definiere globale Variablen
//----------------------------------------------------------------------
extern system_input_tag system_in;											// Variable fuer Systemeingaenge definieren
extern sdc_in_tag sdc_in;													// Variable fuer SDC-Eingaenge definieren
extern komfort_in_tag komfort_in;											// Variable fuer Komforteingaenge definieren
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void readall_inputs(void);													// Alle Eingaenge einlesen und abspeichern
void readAnlasser(void);													// Anlasser einlesen und zwischenspeichern
//----------------------------------------------------------------------

#endif /* INC_INPUTS_H_ */
//----------------------------------------------------------------------
