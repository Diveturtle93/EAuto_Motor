//----------------------------------------------------------------------
// Titel	:	Outputs.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	31.03.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_OUTPUTS_H_
#define INC_OUTPUTS_H_
//----------------------------------------------------------------------

// Define Debug Symbols
//----------------------------------------------------------------------
#define DEBUG_OUTPUT
#define DEBUG_SDC
//----------------------------------------------------------------------

// Strukturen definieren
//----------------------------------------------------------------------
typedef union __system_out_tag {
	struct {
		uint8_t J317 : 1;						// 0
		uint8_t F54 : 1;						// 1
		uint8_t F18 : 1;						// 2
		uint8_t DCDC_Enable : 1;				// 3
		uint8_t Gluehkerzen : 1;				// 4
		uint8_t MotorSDC : 1;					// 5
		uint8_t Klima : 1;						// 6
		uint8_t Power_On : 1;					// 7
	};

	uint8_t systemoutput;						// Byte
} system_out_tag;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
typedef union __highcurrent_out_tag {
	struct {
		uint8_t Digital1 : 1;					// 0
		uint8_t Digital2 : 1;					// 1
		uint8_t Pumpe_Bremse : 1;				// 2
		uint8_t Pumpe_Kuhlung : 1;				// 3
		uint8_t Fan1 : 1;						// 4
		uint8_t Fan2 : 1;						// 5
		uint8_t Heater1 : 1;					// 6
		uint8_t Heater2 : 1;					// 7
	};

	uint8_t high_out;							// Byte
} highcurrent_out_tag;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
typedef union __leuchten_out_tag {
	struct {
		uint8_t Bremslicht : 1;					// 0
		uint8_t Rueckfahrlicht : 1;				// 1
		uint8_t Generator : 1;					// 2
		uint8_t Buzzer : 1;						// 3
		uint8_t Rueckwarn : 1;					// 4
		uint8_t Ladeleuchte : 1;				// 5
		uint8_t Wischwarn : 1;					// 6
		uint8_t Bremswarn : 1;					// 7
		uint8_t Oeldruck : 1;					// 8
		uint8_t Niveau : 1;						// 9
		uint8_t Anhaenger : 1;					// A
		uint8_t RedLed : 1;						// B
		uint8_t GreenLed : 1;					// C
		uint8_t BlueLed : 1;					// D
		uint8_t Reserve : 1;					// E
	};

	uint16_t ledoutput;							// 2 Byte
} leuchten_out_tag;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
typedef union __komfort_out_tag {
	struct {
		uint8_t BC_Rst_Out : 1;					// 0
		uint8_t BC_Up_Out : 1;					// 1
		uint8_t BC_Down_Out : 1;				// 2
		uint8_t BamoOut1 : 1;					// 3
		uint8_t BamoOut2 : 1;					// 4
	};

	uint8_t komfortoutput;						// Byte
} komfort_out_tag;
//----------------------------------------------------------------------

// Definiere Konstanten
//----------------------------------------------------------------------
#define SYSTEM_OUTPUT				0b00000000								// 8 Bit, 8 Systemausgaenge
#define HIGH_OUTPUT					0b00000000								// 8 Bit, 8 Hochstromfaehige Ausgaenge
#define LED_OUTPUT					0b0011100011010000						// 16 Bit, 14 Leuchtdioden
#define KOMFORT_OUTPUT				0b00000000								// 8 Bit, 5 Komfortausgaenge
//----------------------------------------------------------------------

// Definiere globale Variablen
//----------------------------------------------------------------------
extern system_out_tag system_out;											// Variable fuer Systemausgaenge definieren
extern highcurrent_out_tag highcurrent_out;									// Variable fuer Hochstromausgaenge definieren
extern leuchten_out_tag leuchten_out;										// Variable fuer Leuchtenausgaenge definieren
extern komfort_out_tag komfort_out;											// Variable fuer Komfortausgaenge definieren
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void init_outputs(void);													// Initialisiere Ausgaenge
void writeall_outputs(void);												// Schreibe alle Ausgaenge
void writeled_outputs(void);												// Schreibe alle LED-Ausgaenge
void testPCB_Leds(void);													// Teste PCB LEDs fuer je 1s
void testCockpit_Leds(void);												// Teste Cockpit LEDs fuer je 1s
void pwm_oelstand(uint16_t time);											// Oelstandsensor simulieren, Fehler in Cockpit unterdruecken
void cockpit_default(void);													// Fehler am Cockpit deaktivieren
void testSDC(void);															// Teste SDC Spannung
//----------------------------------------------------------------------

#endif /* INC_OUTPUTS_H_ */
//----------------------------------------------------------------------
