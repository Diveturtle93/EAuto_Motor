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
//#define BAMOCAR_REG_reserved					0x00
#define BAMOCAR_REG_USR_OPTIONS					0x01
#define BAMOCAR_REG_USR_SAFE					0x02
#define BAMOCAR_REG_USR_CMD						0x03
#define BAMOCAR_REG_USR_KEY						0x04
#define BAMOCAR_REG_MOTOR_FREQ					0x05
#define BAMOCAR_REG_MOTOR_VOLT					0x06
#define BAMOCAR_REG_TIME_DC						0x07
#define BAMOCAR_REG_DC_VOLT						0x08
#define BAMOCAR_REG_DC_FREQ						0x09
#define BAMOCAR_REG_MIN_VOLT					0x0A
#define BAMOCAR_REG_MIN_FREQ					0x0B
#define BAMOCAR_REG_VOLT_FREQ					0x0C
#define BAMOCAR_REG_FREQ_VOLT					0x0D
#define BAMOCAR_REG_COSPHI						0x0E
//#define BAMOCAR_REG_reserved					0x0F

#define BAMOCAR_REG_CHAN						0x10
#define BAMOCAR_REG_CTRL						0x11
#define BAMOCAR_REG_TRIG_LEVEL					0x12
#define BAMOCAR_REG_TRIG_EGDE					0x13
#define BAMOCAR_REG_TRIG_SCOURCE				0x14
#define BAMOCAR_REG_SCOURCE						0x15
#define BAMOCAR_REG_SKIP						0x16
#define BAMOCAR_REG_READ_CMD					0x17
#define BAMOCAR_REG_RUN_CMD						0x18
#define BAMOCAR_REG_PWM_FREQ					0x19
#define BAMOCAR_REG_LOOKUP						0x1A
#define BAMOCAR_REG_FIRMWARE					0x1B
#define BAMOCAR_REG_CURRENT_KP					0x1C
#define BAMOCAR_REG_CURRENT_TI					0x1D
#define BAMOCAR_REG_CUTOFF						0x1E
#define BAMOCAR_REG_OFFSET_I3					0x1F

#define BAMOCAR_REG_I_ACT						0x20
#define BAMOCAR_REG_I_SOLL						0x21
#define BAMOCAR_REG_I_CMD_RAMP					0x22
#define BAMOCAR_REG_ID_REF						0x23
#define BAMOCAR_REG_I_MAX						0x24
#define BAMOCAR_REG_I_RAMP						0x25
#define BAMOCAR_REG_I_CMD						0x26
#define BAMOCAR_REG_IQ_ACT						0x27
#define BAMOCAR_REG_ID_ACT						0x28
#define BAMOCAR_REG_VQ							0x29
#define BAMOCAR_REG_VD							0x2A
#define BAMOCAR_REG_I_INT_SAMPLE				0x2B
#define BAMOCAR_REG_SPEED_KP					0x2C
#define BAMOCAR_REG_SPEED_KI					0x2D
#define BAMOCAR_REG_SPEED_KD					0x2E
#define BAMOCAR_REG_OFFSET_ANALOG				0x2F

#define BAMOCAR_REG_SPEED_ACT					0x30
#define BAMOCAR_REG_SPEED_SET					0x31
#define BAMOCAR_REG_SPEED_CMD					0x32
#define BAMOCAR_REG_SPEED_ERROR					0x33
#define BAMOCAR_REG_SPEED_LIMIT					0x34
#define BAMOCAR_REG_ACCELERATION				0x35
#define BAMOCAR_REG_CMD							0x36
#define BAMOCAR_REG_SPEED_COUNT					0x37
#define BAMOCAR_REG_IQ_ERROR					0x38
#define BAMOCAR_REG_ID_ERROR					0x39
//#define BAMOCAR_REG_reserved					0x3A
#define BAMOCAR_REG_SPEED_INT_SAMPLE			0x3B
#define BAMOCAR_REG_CURRENT_DERATING_SPEED		0x3C
#define BAMOCAR_REG_READ						0x3D
#define BAMOCAR_REG_SPEED_LIMIT_NEG				0x3E
#define BAMOCAR_REG_SPEED_LIMIT_POR				0x3F

#define BAMOCAR_REG_STATUS						0x40
#define BAMOCAR_REG_INCR_DELTA					0x41
#define BAMOCAR_REG_M_POS_MECH_ACT				0x42
#define BAMOCAR_REG_M_POS_ELEC_ACT				0x43
#define BAMOCAR_REG_M_POS_OFFSET				0x44
#define BAMOCAR_REG_IT_RG_MONITOR				0x45
#define BAMOCAR_REG_I_LIMIT						0x46
//#define BAMOCAR_REG_reserved					0x47
#define BAMOCAR_REG_I_LIM_INUSE					0x48
#define BAMOCAR_REG_T_MOTOR						0x49
#define BAMOCAR_REG_T_IGBT						0x4A
#define BAMOCAR_REG_T_AIR						0x4B
#define BAMOCAR_REG_CURRENT_DERATING_TEMP		0x4C
#define BAMOCAR_REG_MOTOR_I_MAX					0x4D
#define BAMOCAR_REG_MOTOR_I_DAUER				0x4E
#define BAMOCAR_REG_MOTOR_POLE					0x4F

#define BAMOCAR_REG_AIN1_CUTOFF					0x50
#define BAMOCAR_REG_MODE						0x51
#define BAMOCAR_REG_STATUS_MASK					0x52
#define BAMOCAR_REG_AIN2_CUTOFF					0x53
#define BAMOCAR_REG_I1_IST						0x54
#define BAMOCAR_REG_I2_IST						0x55
#define BAMOCAR_REG_I3_IST						0x56
#define BAMOCAR_REG_I_LIMIT_INUSE				0x57
#define BAMOCAR_REG_I_RD_TD						0x58
#define BAMOCAR_REG_MOTOR_RPMMAX				0x59
#define BAMOCAR_REG_KERN_OPTIONS				0x5A
#define BAMOCAR_REG_SPEED_KS					0x5B
#define BAMOCAR_REG_ROTOR						0x5C
#define BAMOCAR_REG_SPEED_CMD_INT				0x5D
#define BAMOCAR_REG_SPEED_FILTER				0x5E
#define BAMOCAR_REG_I_IST_FILTER				0x5F

#define BAMOCAR_REG_AIN_FILTER					0x60
#define BAMOCAR_REG_IT_MONITOR					0x61
#define BAMOCAR_REG_SERIAL_NUMBER				0x62
#define BAMOCAR_REG_FPGA_STATUS					0x63
#define BAMOCAR_REG_MAINS						0x64
#define BAMOCAR_REG_REGEN_PR					0x65
#define BAMOCAR_REG_VDC_BATT					0x66
#define BAMOCAR_REG_TYPE						0x67
#define BAMOCAR_REG_CAN_RX_ID					0x68
#define BAMOCAR_REG_CAN_TX_ID					0x69
#define BAMOCAR_REG_POS_KP						0x6A
#define BAMOCAR_REG_POS_KI						0x6B
#define BAMOCAR_REG_POS_KD						0x6C
#define BAMOCAR_REG_POS_ACT						0x6D
#define BAMOCAR_REG_POS_DEST					0x6E
#define BAMOCAR_REG_POS_ACT2					0x6F

#define BAMOCAR_REG_POS_ERROR					0x70
#define BAMOCAR_REG_POS_ERROR_SUM				0x71
#define BAMOCAR_REG_POS_REF_OFFSET				0x72
#define BAMOCAR_REG_POS_BTR						0x73
#define BAMOCAR_REG_ZERO_CAPTURE				0x74
#define BAMOCAR_REG_RESO_EDGE					0x75
#define BAMOCAR_REG_SPEED1						0x76
#define BAMOCAR_REG_SPEED2						0x77
#define BAMOCAR_REG_START_PARK					0x78
#define BAMOCAR_REG_POS_WINDOW					0x79
#define BAMOCAR_REG_POS_PRESET					0x7A
#define BAMOCAR_REG_POS_VAR_OFFSET				0x7B
#define BAMOCAR_REG_ND_SCALE					0x7C
#define BAMOCAR_REG_ND_OFFSET					0x7D
#define BAMOCAR_REG_ENCODER_2_SCALE				0x7E
//#define BAMOCAR_REG_OFFSET_SLACK				0x7F

#define BAMOCAR_REG_POS_DIFF_SLACK				0x80
//#define BAMOCAR_REG_reserved					0x81
#define BAMOCAR_REG_DEVICE_SERIAL				0x82
#define BAMOCAR_REG_PARAREAD					0x83
#define BAMOCAR_REG_PARAWRITE					0x84
#define BAMOCAR_REG_SPECIAL						0x85
#define BAMOCAR_REG_READ_INFO					0x86
//#define BAMOCAR_REG_reserved					0x87
#define BAMOCAR_REG_CAN_RX_ID2					0x88
#define BAMOCAR_REG_CAN_TX_ID2					0x89
#define BAMOCAR_REG_VOUT						0x8A
#define BAMOCAR_REG_VRED						0x8B
#define BAMOCAR_REG_VKP							0x8C
#define BAMOCAR_REG_VTI							0x8D
#define BAMOCAR_REG_ERRCANCEL					0x8E
#define BAMOCAR_REG_ERROR_BITMAP1				0x8F

#define BAMOCAR_REG_TORQUE_SETPOINT				0x90
#define BAMOCAR_REG_POS_CMD						0x91
#define BAMOCAR_REG_CAN_ERROR_BUS				0x92
#define BAMOCAR_REG_CAN_ERRWRITE				0x93
#define BAMOCAR_REG_FPGA_ERROR					0x94
#define BAMOCAR_REG_CAN_COUNT_READ				0x95
#define BAMOCAR_REG_CAN_COUNT_WRITE				0x96
#define BAMOCAR_REG_CAN_COUNT_REJ				0x97
#define BAMOCAR_REG_LOG_O_BLOCK					0x98
#define BAMOCAR_REG_INFO_INTERRUPT				0x99
#define BAMOCAR_REG_TEMP						0x9A
#define BAMOCAR_REG_LOG_I_BLOCK					0x9B
#define BAMOCAR_REG_TEMP_PT1					0x9C
#define BAMOCAR_REG_TEMP_PT2					0x9D
#define BAMOCAR_REG_TEMP_PT3					0x9E
#define BAMOCAR_REG_TEMP_PT4					0x9F

#define BAMOCAR_REG_TORQUE_OUT					0xA0
#define BAMOCAR_REG_BALLAST_COUNT				0xA1
#define BAMOCAR_REG_I_RD_TM						0xA2
#define BAMOCAR_REG_MOTOR_MAX_TEMP				0xA3
#define BAMOCAR_REG_MOTOR_OPTIONS				0xA4
#define BAMOCAR_REG_DEVICE_DCBUS				0xA5
#define BAMOCAR_REG_MOTOR_GEBER_I				0xA6
#define BAMOCAR_REG_MOTOR_GEBER_P				0xA7
#define BAMOCAR_REG_SPEED_ACT_FILTER			0xA8
#define BAMOCAR_REG_I1_ADC						0xA9
#define BAMOCAR_REG_I2_ADC						0xAA
#define BAMOCAR_REG_LOGIC_FREQ					0xAB
#define BAMOCAR_REG_PWM1						0xAC
#define BAMOCAR_REG_PWM2						0xAD
#define BAMOCAR_REG_PWM3						0xAE
#define BAMOCAR_REG_TIMER_DELTA					0xAF

#define BAMOCAR_REG_SERIALBOOL					0xB0
#define BAMOCAR_REG_MOTOR_INDUCTANCE			0xB1
#define BAMOCAR_REG_ID_NOM						0xB2
#define BAMOCAR_REG_MOTOR_MAGN					0xB3
#define BAMOCAR_REG_MOTOR_ROTOR					0xB4
#define BAMOCAR_REG_ID_MIN						0xB5
#define BAMOCAR_REG_MOTOR_TR					0xB6
#define BAMOCAR_REG_TEMP1_PTR					0xB7
#define BAMOCAR_REG_TEMP1_PTR_IND				0xB8
#define BAMOCAR_REG_TEMP2_PTR					0xB9
#define BAMOCAR_REG_TEMP2_PTR_IND				0xBA
#define BAMOCAR_REG_LEAKAGE_INDUCTANCE			0xBB
#define BAMOCAR_REG_MOTOR_STATOR				0xBC
#define BAMOCAR_REG_MOTOR_SPECS					0xBD
#define BAMOCAR_REG_LOGIC_DEFINE1				0xBE
#define BAMOCAR_REG_LOGIC_DEFINE2				0xBF

#define BAMOCAR_REG_LOGIC_DEFINE3				0xC0
#define BAMOCAR_REG_LOGIC_DEFINE4				0xC1
#define BAMOCAR_REG_LOGIC_DEFINE5				0xC2
#define BAMOCAR_REG_LOGIC_DEFINE6				0xC3
#define BAMOCAR_REG_DEVICE_I_MAX				0xC4
#define BAMOCAR_REG_DEVICE_I_CNT				0xC5
#define BAMOCAR_REG_DEVICE_I					0xC6
#define BAMOCAR_REG_SPEED_DELTA_MAX				0xC7
#define BAMOCAR_REG_SPEED_RPMMAX1				0xC8
#define BAMOCAR_REG_I_KP2						0xC9
#define BAMOCAR_REG_POSI_KI						0xCA
#define BAMOCAR_REG_I_KF						0xCB
#define BAMOCAR_REG_POSI_ERR					0xCC
#define BAMOCAR_REG_POSI_ERRSUM					0xCD
#define BAMOCAR_REG_SPEED_RPMMAX2				0xCE
#define BAMOCAR_REG_POSI_KY						0xCF

#define BAMOCAR_REG_CAN_TIMEOUT					0xD0
#define BAMOCAR_REG_VAR1						0xD1
#define BAMOCAR_REG_VAR2						0xD2
#define BAMOCAR_REG_VAR3						0xD3
#define BAMOCAR_REG_VAR4						0xD4
#define BAMOCAR_REG_AIN1						0xD5
#define BAMOCAR_REG_AIN2						0xD6
#define BAMOCAR_REG_AIN2_OFFSET					0xD7
#define BAMOCAR_REG_LOGIC_READ_BI				0xD8
#define BAMOCAR_REG_KERN_I_200PC				0xD9
#define BAMOCAR_REG_LOGIC_DEFINE7				0xDA
#define BAMOCAR_REG_LOGIC_DEFINE8				0xDB
#define BAMOCAR_REG_DEFINE_DAC					0xDC
//#define BAMOCAR_REG_reserved					0xDD
#define BAMOCAR_REG_O_DOUT3						0xDE
#define BAMOCAR_REG_O_DOUT4						0xDF

#define BAMOCAR_REG_O_DOUT1						0xE0
#define BAMOCAR_REG_O_DOUT2						0xE1
#define BAMOCAR_REG_O_BTB						0xE2
#define BAMOCAR_REG_O_GO						0xE3
#define BAMOCAR_REG_I_END1						0xE4
#define BAMOCAR_REG_I_END2						0xE5
#define BAMOCAR_REG_I_DIN1						0xE6
#define BAMOCAR_REG_I_DIN2						0xE7
#define BAMOCAR_REG_I_FRG						0xE8
#define BAMOCAR_REG_I_FAULT						0xE9
#define BAMOCAR_REG_I_BALLAST					0xEA
#define BAMOCAR_REG_DC_BUS						0xEB
#define BAMOCAR_REG_I_LOS						0xEC
#define BAMOCAR_REG_TORGUE_DELTA_MAX			0xED
#define BAMOCAR_REG_I_IST_100PC					0xEE
#define BAMOCAR_REG_O_NOFAULT					0xEF

#define BAMOCAR_REG_TIME_IPEAK					0xF0
#define BAMOCAR_REG_USR_I_BRAKE					0xF1
#define BAMOCAR_REG_VO_BRAKE					0xF2
#define BAMOCAR_REG_VO_ICNS						0xF3
#define BAMOCAR_REG_VO_TOLER					0xF4
#define BAMOCAR_REG_VO_LESS_N0					0xF5
#define BAMOCAR_REG_POWER						0xF6
#define BAMOCAR_REG_WORK						0xF7
#define BAMOCAR_REG_ASCII_USER					0xF8
#define BAMOCAR_REG_ASCII_WR_EEP				0xF9
#define BAMOCAR_REG_ASCII_RD_EEP				0xFA
#define BAMOCAR_REG_AIN1_CALC					0xFB
#define BAMOCAR_REG_AIN2_CALC					0xFC
//#define BAMOCAR_REG_reserved					0xFD
//#define BAMOCAR_REG_reserved					0xFE
//#define BAMOCAR_REG_reserved					0xFF
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

// Funktionen definieren
//----------------------------------------------------------------------
void readBAMOReg(uint8_t REG);
void readBAMORegIntvl(uint8_t REG, uint8_t interval);
void BAMOCAN_ID(uint8_t* data);
//----------------------------------------------------------------------

#endif /* INC_BAMOCAR_H_ */
//----------------------------------------------------------------------
