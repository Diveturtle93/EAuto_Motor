//----------------------------------------------------------------------
// Titel	:	Bamocar.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	21.05.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_BAMOCAR_H_
#define INC_BAMOCAR_H_
//----------------------------------------------------------------------

// Definiere CAN-IDs
//----------------------------------------------------------------------
#define BAMOCAR_RX_ID							0x181						// Empfangs-Adresse kann zwischen 0x181 und 0x1FF liegen
#define BAMOCAR_TX_ID							0x201						// Sende-Adresse kann zwischen 0x201 und 0x27F liegen
//----------------------------------------------------------------------

// Definiere RegIDs
//----------------------------------------------------------------------
//#define BAMOCAR_REG_reserved					0x00						// reserved
#define BAMOCAR_REG_USR_OPTIONS					0x01						// (Deif) Options
#define BAMOCAR_REG_USR_SAFE					0x02						// (Deif) Safety-State
#define BAMOCAR_REG_USR_CMD						0x03						// (Deif) Cmd-Specials
#define BAMOCAR_REG_USR_KEY						0x04						// ?? (User Key)
#define BAMOCAR_REG_MOTOR_FREQ					0x05						// Nominal Motor Frequenz
#define BAMOCAR_REG_MOTOR_VOLT					0x06						// Motor nominal Spannung
#define BAMOCAR_REG_TIME_DC						0x07						// Zeit DC pre-mag
#define BAMOCAR_REG_DC_VOLT						0x08						// DC Spannung
#define BAMOCAR_REG_DC_FREQ						0x09						// ??
#define BAMOCAR_REG_MIN_VOLT					0x0A						// Minimal Spannung
#define BAMOCAR_REG_MIN_FREQ					0x0B						// Minimal Frequenz
#define BAMOCAR_REG_VOLT_FREQ					0x0C						// Spannung fuer max. Frequenz
#define BAMOCAR_REG_FREQ_VOLT					0x0D						// Frequenz fuer max. Spannung
#define BAMOCAR_REG_COSPHI						0x0E						// Power Faktor
//#define BAMOCAR_REG_reserved					0x0F						// (...)

#define BAMOCAR_REG_CHAN						0x10						// Oszilloskop Trigger Kanal
#define BAMOCAR_REG_CTRL						0x11						// Control Status
#define BAMOCAR_REG_TRIG_LEVEL					0x12						// Oszilloskop Trigger Level
#define BAMOCAR_REG_TRIG_EGDE					0x13						// Oszilloskop Trigger Funktion
#define BAMOCAR_REG_TRIG_SCOURCE				0x14						// Oszilloskop Trigger Quelle
#define BAMOCAR_REG_SCOURCE						0x15						// Oszilloskop Quelle
#define BAMOCAR_REG_SKIP						0x16						// Oszilloskop Skip
#define BAMOCAR_REG_READ_CMD					0x17						// Oszilloskop Lesen
#define BAMOCAR_REG_RUN_CMD						0x18						// Oszilloskop Run
#define BAMOCAR_REG_PWM_FREQ					0x19						// Frequenz PWM Bereich
#define BAMOCAR_REG_LOOKUP						0x1A						// Lookup Fenster
#define BAMOCAR_REG_FIRMWARE					0x1B						// Firmware
#define BAMOCAR_REG_CURRENT_KP					0x1C						// KP-Glied Regelung
#define BAMOCAR_REG_CURRENT_TI					0x1D						// KI-Glied Regelung
#define BAMOCAR_REG_CUTOFF						0x1E						// Cutoff Digital Command
#define BAMOCAR_REG_OFFSET_I3					0x1F						// Offset aktueller Strom 3

#define BAMOCAR_REG_I_ACT						0x20						// Aktueller Stromwert
#define BAMOCAR_REG_I_SOLL						0x21						// D Strom Sollwert
#define BAMOCAR_REG_I_CMD_RAMP					0x22						// Nummerischer Sollwert Strom
#define BAMOCAR_REG_ID_REF						0x23						// D Referenz Sollwert
#define BAMOCAR_REG_I_MAX						0x24						// I max in Benutzung
#define BAMOCAR_REG_I_RAMP						0x25						// Command Strom Rampe
#define BAMOCAR_REG_I_CMD						0x26						// Command Strom
#define BAMOCAR_REG_IQ_ACT						0x27						// Q-Strom aktuell
#define BAMOCAR_REG_ID_ACT						0x28						// D-Strom aktuell
#define BAMOCAR_REG_VQ							0x29						// Q-Spannung aktuell
#define BAMOCAR_REG_VD							0x2A						// D-Spannung aktuell
#define BAMOCAR_REG_I_INT_SAMPLE				0x2B						// Max. Integrationswert Zaehler Strom
#define BAMOCAR_REG_SPEED_KP					0x2C						// KP-Glied Geschwindigkeit
#define BAMOCAR_REG_SPEED_KI					0x2D						// KI-Glied Geschwindigkeit
#define BAMOCAR_REG_SPEED_KD					0x2E						// KD-Glied Geschwindigkeit
#define BAMOCAR_REG_OFFSET_ANALOG				0x2F						// Offset Ain1

#define BAMOCAR_REG_N_ACT						0x30						// Aktuelle Drehzahl
#define BAMOCAR_REG_SPEED_SET					0x31						// Digitaler Geschwindigkeitssollwert
#define BAMOCAR_REG_SPEED_CMD					0x32						// Command Geschwindigkeit Rampe
#define BAMOCAR_REG_SPEED_ERROR					0x33						// Geschwindigkeit Error
#define BAMOCAR_REG_SPEED_LIMIT					0x34						// Geschwindigkeit Limit
#define BAMOCAR_REG_ACCELERATION				0x35						// Geschwindigkeit Rampe
#define BAMOCAR_REG_CMD							0x36						// Selection Command Geschwindigkeit
#define BAMOCAR_REG_SPEED_COUNT					0x37						// Strom zu Geschwindigkeit Faktor
#define BAMOCAR_REG_IQ_ERROR					0x38						// Strom Iq Fehler
#define BAMOCAR_REG_ID_ERROR					0x39						// Strom Id Fehler
//#define BAMOCAR_REG_reserved					0x3A						// ??
#define BAMOCAR_REG_SPEED_INT_SAMPLE			0x3B						// Max. Integrationswert Zaehler Geschwindigkeit
#define BAMOCAR_REG_CURRENT_DERATING_SPEED		0x3C						// Aktuelle Geschwindigkeitsreduzierung
#define BAMOCAR_REG_READ						0x3D						// Funktion Lese Register
#define BAMOCAR_REG_SPEED_LIMIT_NEG				0x3E						// Geschwindigkeit Limit negativ
#define BAMOCAR_REG_SPEED_LIMIT_POR				0x3F						// Geschwindigkeit Limit positiv

#define BAMOCAR_REG_STATUS						0x40						// Geraetestatus	
#define BAMOCAR_REG_INCR_DELTA					0x41						// ??
#define BAMOCAR_REG_M_POS_MECH_ACT				0x42						// Motor aktuelle Winkelposition mechanisch
#define BAMOCAR_REG_M_POS_ELEC_ACT				0x43						// Motor aktuelle Winkelposition elektrisch
#define BAMOCAR_REG_M_POS_OFFSET				0x44						// Offset Feedback Phasenwinkel
#define BAMOCAR_REG_IT_RG_MONITOR				0x45						// Monitor I2t Regeneration
#define BAMOCAR_REG_I_LIMIT						0x46						// Strom Limit digitaler Schalter
//#define BAMOCAR_REG_reserved					0x47						// ...
#define BAMOCAR_REG_I_LIM_INUSE					0x48						// Aktuelle Strom Limit
#define BAMOCAR_REG_T_MOTOR						0x49						// Motortemperatur
#define BAMOCAR_REG_T_IGBT						0x4A						// IGBT Temperatur
#define BAMOCAR_REG_T_AIR						0x4B						// Luft Temperatur
#define BAMOCAR_REG_CURRENT_DERATING_TEMP		0x4C						// Aktuelle Derating Temperatur
#define BAMOCAR_REG_MOTOR_I_MAX					0x4D						// Max. Motorstrom
#define BAMOCAR_REG_MOTOR_I_DAUER				0x4E						// Dauerstrom Motor
#define BAMOCAR_REG_MOTOR_POLE					0x4F						// Motor Polanzahl

#define BAMOCAR_REG_AIN1_CUTOFF					0x50						// Cutoff Fenster Ain1
#define BAMOCAR_REG_MODE						0x51						// Mode Status
#define BAMOCAR_REG_STATUS_MASK					0x52						// Status Maske
#define BAMOCAR_REG_AIN2_CUTOFF					0x53						// Cutoff Fenster Ain2
#define BAMOCAR_REG_I1_IST						0x54						// Aktueller Stromwert I1
#define BAMOCAR_REG_I2_IST						0x55						// Aktueller Stromwert I2
#define BAMOCAR_REG_I3_IST						0x56						// Aktueller Stromwert I3
#define BAMOCAR_REG_I_LIMIT_INUSE				0x57						// ??
#define BAMOCAR_REG_I_RD_TD						0x58						// ??
#define BAMOCAR_REG_MOTOR_RPMMAX				0x59						// Drehzahl Motor
#define BAMOCAR_REG_KERN_OPTIONS				0x5A						// Geraeteeinstellung (Options)
#define BAMOCAR_REG_SPEED_KS					0x5B						// Acceleration amplification
#define BAMOCAR_REG_ROTOR						0x5C						// Rotor Signal
#define BAMOCAR_REG_SPEED_CMD_INT				0x5D						// Command Geschwindigkeit intern
#define BAMOCAR_REG_SPEED_FILTER				0x5E						// Filter aktuelle Geschwindigkeitswerte
#define BAMOCAR_REG_I_ACT_FILTER				0x5F						// Aktuelle Stromwerte gefiltert (Zum Anzeigen / Monitoring)

#define BAMOCAR_REG_AIN_FILTER					0x60						//
#define BAMOCAR_REG_IT_MONITOR					0x61						// I_t Monitor
#define BAMOCAR_REG_SN_INTERN					0x62						// Geraete Seriennummer Intern
#define BAMOCAR_REG_FPGA_STATUS					0x63						// FPGA Status
#define BAMOCAR_REG_MAINS						0x64						// Spannung Versorungsspannung
#define BAMOCAR_REG_REGEN_PR					0x65						// Regeneration Power Widerstand
#define BAMOCAR_REG_VDC_BATT					0x66						// Batteriespannung
#define BAMOCAR_REG_TYPE						0x67						// Geraetetype
#define BAMOCAR_REG_CAN_RX_ID					0x68						// CAN-Bus RX Adresse
#define BAMOCAR_REG_CAN_TX_ID					0x69						// CAN-Bus TX Adresse
#define BAMOCAR_REG_POS_KP						0x6A						// KP-Glied Positionsregelung
#define BAMOCAR_REG_POS_KI						0x6B						// KI-Glied Positionsregelung
#define BAMOCAR_REG_POS_KD						0x6C						// KD-Glied Positionsregelung
#define BAMOCAR_REG_POS_ACT						0x6D						// Aktuelle Position Nummerisch
#define BAMOCAR_REG_POS_DEST					0x6E						// Positionsort
#define BAMOCAR_REG_POS_ACT2					0x6F						// Aktuelle Position 2

#define BAMOCAR_REG_POS_ERROR					0x70						// Position Fehler
#define BAMOCAR_REG_POS_ERROR_SUM				0x71						// Max. Integrationswert Zaehler Position 
#define BAMOCAR_REG_POS_REF_OFFSET				0x72						// Referenz Nulloffset
#define BAMOCAR_REG_POS_BTR						0x73						// CAN-Bus Uebertragungsrate
#define BAMOCAR_REG_ZERO_CAPTURE				0x74						// Absoluter Nullpunkt
#define BAMOCAR_REG_RESO_EDGE					0x75						// Resolver Position RAW
#define BAMOCAR_REG_SPEED1						0x76						// Referenzgeschwindigkeit schnell
#define BAMOCAR_REG_SPEED2						0x77						// Referenzgeschwindigkeit langsam
#define BAMOCAR_REG_START_PARK					0x78						// Start Parkzyklus
#define BAMOCAR_REG_POS_WINDOW					0x79						// Toleranzfenster fuer Position
#define BAMOCAR_REG_POS_PRESET					0x7A						// Preset Wert
#define BAMOCAR_REG_POS_VAR_OFFSET				0x7B						// Benutzer Nulloffset
#define BAMOCAR_REG_ND_SCALE					0x7C						// Anzeige Positionsfaktor
#define BAMOCAR_REG_ND_OFFSET					0x7D						// Verschiebefaktor Position Anzeige
#define BAMOCAR_REG_ENCODER_2_SCALE				0x7E						// Skaliere zweiten Faktor
//#define BAMOCAR_REG_OFFSET_SLACK				0x7F						// ??

#define BAMOCAR_REG_POS_DIFF_SLACK				0x80						// ??
//#define BAMOCAR_REG_reserved					0x81						// ...
#define BAMOCAR_REG_SN_EXTERN					0x82						// Geraete Seriennummer extern
#define BAMOCAR_REG_PARAREAD					0x83						// ??
#define BAMOCAR_REG_PARAWRITE					0x84						// ??
#define BAMOCAR_REG_SPECIAL						0x85						// Auto Funktion
#define BAMOCAR_REG_READ_INFO					0x86						// ??
//#define BAMOCAR_REG_reserved					0x87						// ...
#define BAMOCAR_REG_CAN_RX_ID2					0x88						// CAN-Bus RX Adresse ID2
#define BAMOCAR_REG_CAN_TX_ID2					0x89						// CAN-Bus TX Adresse ID2
#define BAMOCAR_REG_VOUT						0x8A						// Ausgangsspannung
#define BAMOCAR_REG_VRED						0x8B						// Startpunkt Feldreduktion
#define BAMOCAR_REG_VKP							0x8C						// KP-Glied Spannungsregelung
#define BAMOCAR_REG_VTI							0x8D						// Zeitkonstante Spannungsregelung
#define BAMOCAR_REG_ERRCANCEL					0x8E						// Zurueksetzen von Fehlern
#define BAMOCAR_REG_ERROR						0x8F						// Fehlerregister

#define BAMOCAR_REG_TORQUE_SETPOINT				0x90						// Digitaler Drehmoment Sollwert
#define BAMOCAR_REG_POS_CMD						0x91						// Command Position
#define BAMOCAR_REG_CAN_ERROR_BUS				0x92						// CAN-Bus Fehler
#define BAMOCAR_REG_CAN_ERRWRITE				0x93						// CAN-Bus ??
#define BAMOCAR_REG_FPGA_ERROR					0x94						// FPGA erster Fehler
#define BAMOCAR_REG_CAN_COUNT_READ				0x95						// CAN-Bus ??
#define BAMOCAR_REG_CAN_COUNT_WRITE				0x96						// CAN-Bus ??
#define BAMOCAR_REG_CAN_COUNT_REJ				0x97						// CAN-Bus
#define BAMOCAR_REG_LOG_O_BLOCK					0x98						// O-Block
#define BAMOCAR_REG_INFO_INTERRUPT				0x99						// Info Interrupt Zeit
#define BAMOCAR_REG_TEMP						0x9A						// Temp
#define BAMOCAR_REG_LOG_I_BLOCK					0x9B						// I-Block
#define BAMOCAR_REG_TEMP_PT1					0x9C						// Temperatursensor PT100 1
#define BAMOCAR_REG_TEMP_PT2					0x9D						// Temperatursensor PT100 2
#define BAMOCAR_REG_TEMP_PT3					0x9E						// Temperatursensor PT100 3
#define BAMOCAR_REG_TEMP_PT4					0x9F						// Temperatursensor PT100 4

#define BAMOCAR_REG_TORQUE_OUT					0xA0						// Digitales Drehmoment intern
#define BAMOCAR_REG_BALLAST_COUNT				0xA1						// Ballast Zaehler
#define BAMOCAR_REG_I_RD_TM						0xA2						// ??
#define BAMOCAR_REG_MOTOR_MAX_TEMP				0xA3						// Motortemperatur Abschaltpunkt
#define BAMOCAR_REG_MOTOR_OPTIONS				0xA4						// Motor Optionen
#define BAMOCAR_REG_DEVICE_DCBUS				0xA5						// DC Max & Min
#define BAMOCAR_REG_MOTOR_GEBER_I				0xA6						// Increments pro Rpm
#define BAMOCAR_REG_MOTOR_GEBER_P				0xA7						// Resolver Polanzahl
#define BAMOCAR_REG_N_ACT_FILTER				0xA8						// Aktuelle Drehzahl gefiltert (Zum Anzeigen / Monitoring)
#define BAMOCAR_REG_I1_ADC						0xA9						// Stromsensor M1
#define BAMOCAR_REG_I2_ADC						0xAA						// Stromsensor M3
#define BAMOCAR_REG_LOGIC_FREQ					0xAB						// Forerground Frequenz
#define BAMOCAR_REG_PWM1						0xAC						// PWM Phase 1
#define BAMOCAR_REG_PWM2						0xAD						// PWM Phase 2
#define BAMOCAR_REG_PWM3						0xAE						// PWM Phase 3
#define BAMOCAR_REG_TIMER_DELTA					0xAF						// Intr. Zeit

#define BAMOCAR_REG_SERIALBOOL					0xB0						// ??
#define BAMOCAR_REG_MOTOR_INDUCTANCE			0xB1						// Stator Leakage Induktivitaet
#define BAMOCAR_REG_ID_NOM						0xB2						// Nominal Magnetisierungsstrom
#define BAMOCAR_REG_MOTOR_MAGN					0xB3						// Magnetische Motorinduktivitaet
#define BAMOCAR_REG_MOTOR_ROTOR					0xB4						// Rotorwiderstand
#define BAMOCAR_REG_ID_MIN						0xB5						// Min. Magnetisierungsstrom
#define BAMOCAR_REG_MOTOR_TR					0xB6						// Zeitkonstante Rotor
#define BAMOCAR_REG_TEMP1_PTR					0xB7						// Ptr1
#define BAMOCAR_REG_TEMP1_PTR_IND				0xB8						// Ptr1
#define BAMOCAR_REG_TEMP2_PTR					0xB9						// Ptr2
#define BAMOCAR_REG_TEMP2_PTR_IND				0xBA						// Ptr2
#define BAMOCAR_REG_LEAKAGE_INDUCTANCE			0xBB						// Leakage Induktivitaet Phase zu Phase
#define BAMOCAR_REG_MOTOR_STATOR				0xBC						// Statorwiderstand Phase zu Phase
#define BAMOCAR_REG_MOTOR_SPECS					0xBD						// Zeitkonstante Stator
#define BAMOCAR_REG_LOGIC_DEFINE1				0xBE						//
#define BAMOCAR_REG_LOGIC_DEFINE2				0xBF						//

#define BAMOCAR_REG_LOGIC_DEFINE3				0xC0						//
#define BAMOCAR_REG_LOGIC_DEFINE4				0xC1						//
#define BAMOCAR_REG_LOGIC_DEFINE5				0xC2						//
#define BAMOCAR_REG_LOGIC_DEFINE6				0xC3						//
#define BAMOCAR_REG_DEVICE_I_MAX				0xC4						// Limit Spitzenstrom
#define BAMOCAR_REG_DEVICE_I_CNT				0xC5						// Limit Dauerstrom
#define BAMOCAR_REG_DEVICE_I					0xC6						// Geraetestrom
#define BAMOCAR_REG_SPEED_DELTA_MAX				0xC7						// Emergency Stop Zeit Rampe
#define BAMOCAR_REG_SPEED_RPMMAX1				0xC8						// Max. Geschwindigkeit
#define BAMOCAR_REG_I_KP2						0xC9						// KP-Glied2 Position
#define BAMOCAR_REG_POSI_KI						0xCA						// KI-Glied2 Position
#define BAMOCAR_REG_I_KF						0xCB						// ...
#define BAMOCAR_REG_POSI_ERR					0xCC						// 
#define BAMOCAR_REG_POSI_ERRSUM					0xCD						// Limit Spitzenwert Integral
#define BAMOCAR_REG_SPEED_RPMMAX2				0xCE						//
#define BAMOCAR_REG_POSI_KY						0xCF						//

#define BAMOCAR_REG_CAN_TIMEOUT					0xD0						// CAN Timeout
#define BAMOCAR_REG_VAR1						0xD1						// Vergleich Variable 1
#define BAMOCAR_REG_VAR2						0xD2						// Vergleich Variable 2
#define BAMOCAR_REG_VAR3						0xD3						// Vergleich Variable 3
#define BAMOCAR_REG_VAR4						0xD4						// Vergleich Variable 4
#define BAMOCAR_REG_AIN1						0xD5						// Analogeingang 1
#define BAMOCAR_REG_AIN2						0xD6						// Analogeingang 2
#define BAMOCAR_REG_AIN2_OFFSET					0xD7						// Offset Ain2
#define BAMOCAR_REG_STATUS_IO					0xD8						// IO-Status
#define BAMOCAR_REG_KERN_I_200PC				0xD9						//
#define BAMOCAR_REG_LOGIC_DEFINE7				0xDA						//
#define BAMOCAR_REG_LOGIC_DEFINE8				0xDB						//
#define BAMOCAR_REG_DEFINE_DAC					0xDC						// ??
//#define BAMOCAR_REG_reserved					0xDD						// ...
#define BAMOCAR_REG_O_DOUT3						0xDE						// Digitalausgang 3
#define BAMOCAR_REG_O_DOUT4						0xDF						// Digitalausgang 4

#define BAMOCAR_REG_O_DOUT1						0xE0						// Digitalausgang 1
#define BAMOCAR_REG_O_DOUT2						0xE1						// Digitalausgang 2
#define BAMOCAR_REG_O_BTB						0xE2						// Geraet Bereit
#define BAMOCAR_REG_O_GO						0xE3						// Internal Run
#define BAMOCAR_REG_I_END1						0xE4						// Digitaleingang END1
#define BAMOCAR_REG_I_END2						0xE5						// Digitaleingang END2
#define BAMOCAR_REG_I_DIN1						0xE6						// Digitaleingang Din1
#define BAMOCAR_REG_I_DIN2						0xE7						// Digitaleingang Din2
#define BAMOCAR_REG_I_FRG						0xE8						// Digitaleingang Run
#define BAMOCAR_REG_I_FAULT						0xE9						// Internal Error Nachricht
#define BAMOCAR_REG_I_BALLAST					0xEA						// Nachricht Regeneration
#define BAMOCAR_REG_DC_BUS						0xEB						// DC Spannung
#define BAMOCAR_REG_I_LOS						0xEC						// Resolver Incorrekt
#define BAMOCAR_REG_TORGUE_DELTA_MAX			0xED						// Geschwindigkeit / Drehmoment Ramp
#define BAMOCAR_REG_I_IST_100PC					0xEE						// Stromsensor Kalibrierung
#define BAMOCAR_REG_O_NOFAULT					0xEF						//

#define BAMOCAR_REG_TIME_IPEAK					0xF0						// Spitzenstrom Zeit
#define BAMOCAR_REG_USR_I_BRAKE					0xF1						// Bremse Zeitverzoegerung
#define BAMOCAR_REG_VO_BRAKE					0xF2						// Bremse ein
#define BAMOCAR_REG_VO_ICNS						0xF3						// Nachricht Dauerstrom
#define BAMOCAR_REG_VO_TOLER					0xF4						// Nachricht Position Toleranz
#define BAMOCAR_REG_VO_LESS_N0					0xF5						// Nachricht Geschwindigkeit < 1%
#define BAMOCAR_REG_POWER						0xF6						// Leistung
#define BAMOCAR_REG_WORK						0xF7						// Work
#define BAMOCAR_REG_ASCII_USER					0xF8						// Axis Label
#define BAMOCAR_REG_ASCII_WR_EEP				0xF9						// ??
#define BAMOCAR_REG_ASCII_RD_EEP				0xFA						// ??
#define BAMOCAR_REG_AIN1_CALC					0xFB						// Ain1 calc
#define BAMOCAR_REG_AIN2_CALC					0xFC						// Ain2 calc
//#define BAMOCAR_REG_reserved					0xFD						// ...
//#define BAMOCAR_REG_reserved					0xFE						// ...
//#define BAMOCAR_REG_reserved					0xFF						// reserved
//----------------------------------------------------------------------

// Aufloesung der Sollwerte
//----------------------------------------------------------------------
#define BAMOCAR_POSITION						12							// Aufloesung Position
#define BAMOCAR_DREHZAHL						15							// Aufloesung Drehzahl
#define BAMOCAR_POS_SOLL						31							// Aufloesung Sollwert Position
#define BAMOCAR_SPEED_SOLL						15							// Aufloesung Sollwert Speed
#define BAMOCAR_I_SOLL							9							// Aufloesung Sollwert Strom
//----------------------------------------------------------------------

// Zeitinterval fuer Antwortnachrichten
//----------------------------------------------------------------------
#define INTVL_IMMEDIATE   0x00
#define INTVL_SUSPEND     0xFF
#define INTVL_100MS       0x64
#define INTVL_200MS       0xC8
#define INTVL_250MS       0xFA
//----------------------------------------------------------------------

// Definiere Union Statusinformationen Ein- / Augaenge (NDrive S.21)
//----------------------------------------------------------------------
typedef union __bamocar_statusIO_tag {
	struct {
		uint8_t LMT1 : 1;													// Digitaler Eingang Limit 1 aktiv
		uint8_t LMT2 : 1;													// Digitaler Eingang Limit 2 aktiv
		uint8_t IN2 : 1;													// Digitaler Eingang Din 2 aktiv
		uint8_t IN1 : 1;													// Digitaler Eingang Din 1 aktiv
		uint8_t FRG : 1;													// Hardware-Freigabe aktive
		uint8_t RFE : 1;													// Drehfeld-Freigabe aktiv
		uint8_t reserve : 2;												// Zwei Bits reserved
		uint8_t OUT1 : 1;													// Digitaler Ausgang Dout 1 geschaltet
		uint8_t OUT2 : 1;													// Digitaler Ausgang Dout 2 geschaltet
		uint8_t BTB : 1;													// Hardware Relaisausgang BTB-Rdy geschaltet
		uint8_t GO : 1;														// Interne Freigabe GO aktiv
		uint8_t OUT3 : 1;													// Digitaler Ausgang Dout 3 geschaltet
		uint8_t OUT4 : 1;													// Digitaler Ausgang Dout 4 geschaltet
		uint8_t GOFF : 1;													// 
		uint8_t BRK1 : 1;													// Bremse erregt
	};

	uint16_t status1;														// Status in 16 Bit Variable

	uint8_t status[2];														// Status in Array
} bamocar_statusIO_tag;
//----------------------------------------------------------------------

// Definiere Union Status Geraeteinformationen (NDrive S. 22)
//----------------------------------------------------------------------
typedef union __bamocar_status_tag {
	struct {
		uint8_t Ena : 1;													// Antrieb freigegeben (Kombination Hardware RUN und Software)
		uint8_t NcR0 : 1;													// Drehzahl auf null begrenzt
		uint8_t LimPos : 1;													// Endschalter Plus belegt
		uint8_t LimNeg : 1;													// Endschalter Minus belegt
		uint8_t OK : 1;														// Antrieb in Ordnung
		uint8_t Icns : 1;													// Stromgrenze auf Dauerstrom reduziert
		uint8_t TNlim : 1;													// Drehzahlbegrenzter Drehmoment-Modus
		uint8_t PN : 1;														// Positionsregelung
		uint8_t NI : 1;														// Drehzahlregelung
		uint8_t NO : 1;														// Drehzahl kleiner als 0.1% (Stillstand)
		uint8_t Rsw : 1;													// Referenz-Eingang angewaehlt
		uint8_t Cal0 : 1;													// Referenzfahrt laeuft
		uint8_t Cal : 1;													// Referenzposition erkannt
		uint8_t Tol : 1;													// Position im Toleranzfenster
		uint8_t Rdy : 1;													// Betriebsbereit (BTB/RDY Kontakt geschlossen)
		uint8_t Brk0 : 1;													// Nicht erregte Bremse bei Motor aktiv
		uint8_t SignMag : 1;												// Sollwert invertiert
		uint8_t Nclip : 1;													// Drehzahlbegrenzung aktiviert (NLim < 90%)
		uint8_t NclipPos : 1;												// Drehzahlbegrenzung positiv ueber Schalter
		uint8_t NclipNeg : 1;												// Drehzahlbegrenzung negativ ueber Schalter
		uint8_t IrdDig : 1;													// Strombegrenzung ueber Schalter
		uint8_t IuseRchd : 1;												// Stromreduzierung aktuell
		uint8_t IrdN : 1;													// Stromreduzierung ueber Drehzahl
		uint8_t IrdTI : 1;													// Stromreduzierung ueber Endstufentemperatur
		uint8_t IrdTIR : 1;													// Strom reduziert auf Dauerstrom ueber Endstufentemperatur
		uint8_t Freq10Hz : 1;												// Stromreduzierung bei Frequenz kleiner 10 Hz
		uint8_t IrdTm : 1;													// Stromreduzierung ueber Motortemperatur
		uint8_t IrdAna : 1;													// Stromreduzierung ueber Analogeingang (wenn <= 90%)
		uint8_t Iwcns : 1;													// Stromspitzenwert Warnung
		uint8_t RFEPulse : 1;												// Gepulster RFE-Eingang Ueberwachung aktiv
		uint8_t M_D : 1;													// frei
		uint8_t HndWhl : 1;													// Handrad-Eingang angewaehlt
	};

	uint32_t status1;														// Status in 32 Bit Variable

	uint8_t status[4];														// Status in Array
} bamocar_status_tag;
//----------------------------------------------------------------------

// Definiere Union Bamocar Error (NDrive S. 23)
//----------------------------------------------------------------------
typedef union __bamocar_error_tag {
	struct {
		uint8_t BadParas : 1;												// Parameter beschaedigt
		uint8_t PowerFault : 1;												// Hardware-Fehler
		uint8_t RFE : 1;													// Sicherheitskreis fehlerhaft
		uint8_t BUSTimeout : 1;												// CAN-Bus Timeout, Zeitueberschreibung
		uint8_t Feedback : 1;												// Schlechtes oder falsches Gebersignal
		uint8_t PowerVoltage : 1;											// Leistungsspannung fehlt
		uint8_t MotorTemp : 1;												// Motortemperatur zu hoch
		uint8_t DeviceTemp : 1;												// Geraetetemperatur zu hoch
		uint8_t OverVoltage : 1;											// Ueberspannung > 1.8 x UN erreicht
		uint8_t IPeak : 1;													// Ueberstrom oder stark oszillierenden Strom erkannt
		uint8_t RaceAway : 1;												// Durchdrehen (oder Sollwert, falsche Richtung)
		uint8_t User : 1;													// Benutzer - Fehlerauswahl
		uint8_t reserved : 2;												// frei
		uint8_t HW_Err : 1;													// Strom-Messfehler
		uint8_t Ballast : 1;												// Ballastschaltung ueberlastet (ohne Funktion)
	};

	uint16_t error1;														// Status in 16 Bit Variable

	uint8_t error[2];														// Status in Array
} bamocar_error_tag;
//----------------------------------------------------------------------

// Definiere Union Bamocar Warnungen (NDrive S. 24)
//----------------------------------------------------------------------
typedef union __bamocar_warnung_tag {
	struct {
		uint8_t Warnung0 : 1;												// Geraeteerkennung inkonsistent
		uint8_t IllegalStatus : 1;											// RUN Signal gestoert, EMV
		uint8_t Warnung2 : 1;												// RFE Eingang inaktiv (ohne RUN Eingang aktiv)
		uint8_t reserve : 2;												// frei
		uint8_t PowerVoltage : 1;											// Leistungsspannung zu klein oder fehlt
		uint8_t MotorTemp : 1;												// Motortemperatur > (I-red-TM oder 93% von M-Temp)
		uint8_t DeviceTemp : 1;												// Geraetetemperatur > 87% vom Limit
		uint8_t VoutSat : 1;												// Grenze der vorhandenen Spannungsausgabe erreicht
		uint8_t IPeak : 1;													// Ueberstrom 200%
		uint8_t WaceAway : 1;												// Aufloesungsbereich der Drehzahlmessung ueberschritten
		uint8_t reserved : 4;												// frei
		uint8_t Ballast : 1;												// Ballastschaltung > 87% ueberlaster (ohne Funktion)
	};

	uint16_t warnung1;														// Status in 16 Bit Variable

	uint8_t warnung[2];														// Status in Array
} bamocar_warnung_tag;
//----------------------------------------------------------------------

// Daten gelesener Register
//----------------------------------------------------------------------
typedef union __bamocar_can_read_tag {
	uint32_t data;															// Status in 16 Bit Variable

	uint8_t can[4];															// Status in Array
} bamocar_can_read_tag;
//----------------------------------------------------------------------

// Definiere globale Variablen
//----------------------------------------------------------------------
extern bamocar_statusIO_tag bamocar_IOstatus;								// Variable fuer IO Status definieren
extern bamocar_status_tag bamocar_stat;										// Variable fuer Status definieren
extern bamocar_error_tag bamocar_error;										// Variable fuer Error definieren
extern bamocar_warnung_tag bamocar_warnung;									// Variable fuer Warnung definieren
extern bamocar_can_read_tag bamocar_data;									// Variable fuer CAN-Daten definieren
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void readBAMOReg(uint8_t REG);
void readBAMORegIntvl(uint8_t REG, uint8_t interval);
void BAMOCAN_ID(uint8_t* data, uint8_t dlc);
void BamocarInfo(void);
//----------------------------------------------------------------------

#endif /* INC_BAMOCAR_H_ */
//----------------------------------------------------------------------
