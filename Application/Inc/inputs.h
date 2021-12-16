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
union system_input_tag {
	struct {
		uint8_t Kickdown : 1;					// 0
		uint8_t Leerlauf : 1;					// 1
		uint8_t BremseNO : 1;					// 2
		uint8_t BremseNC : 1;					// 3
		uint8_t Kupplung : 1;					// 4
		uint8_t Recuperation : 1;				// 5
		uint8_t ECON : 1;						// 6
		uint8_t Anlasser : 1;					// 7
		uint8_t KL15 : 1;						// 8
		uint8_t DCDC_Inst : 1;					// 9
		uint8_t Button1 : 1;					// A
		uint8_t Button2 : 1;					// B
		uint8_t Crash : 1;						// C
		uint8_t Wakeup : 1;						// D
		uint8_t Bremsdruck_NO : 1;				// E
		uint8_t Bremsdruck_NC : 1;				// F
	};

	uint16_t systeminput;						// 2 Byte
} system_in;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
union sdc_in_tag {
	struct {
		uint8_t EmergencyRun : 1;				// 0
		uint8_t SDC0 : 1;						// 1
		uint8_t AkkuSDC : 1;					// 2
		uint8_t BTB_SDC : 1;					// 3
		uint8_t DCDC_Fault : 1;					// 4
	};

	uint8_t sdcinput;							// 1 Byte
} sdc_in;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
union komfort_in_tag {
	struct {
		uint8_t ASR1 : 1;						// 0
		uint8_t ASR2 : 1;						// 1
		uint8_t ECO : 1;						// 2
		uint8_t BC_Rst_In : 1;					// 3
		uint8_t BC_Up_In : 1;					// 4
		uint8_t BC_Down_In : 1;					// 5
		uint8_t BamoIn1 : 1;					// 6
		uint8_t BamoIn2 : 1;					// 7
		uint8_t Enter : 1;						// 8
		uint8_t OutA : 1;						// 9
		uint8_t OutB : 1;						// A
		uint8_t GRA1 : 1;						// B
		uint8_t GRA2 : 1;						// C
		uint8_t GRA3 : 1;						// D
		uint8_t GRA4 : 1;						// E
		uint8_t Durchfluss : 1;					// F
	};

	uint16_t komfortinput;						// 2 Byte
} komfort_in;
//----------------------------------------------------------------------

// Definiere Konstanten
//----------------------------------------------------------------------
#define SYSTEM_INPUT					0b0000000000000000					// 16 Bit, 16 Systemeingaenge
#define KOMFORT_INPUT					0b0000000000000000					// 16 Bit, 16 Komforteingaenge
#define SDC_INPUT						0b00000000							// 8 Bit, 5 SDC-Eingaenge
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void readall_inputs(void);
//----------------------------------------------------------------------

#endif /* INC_INPUTS_H_ */
//----------------------------------------------------------------------
