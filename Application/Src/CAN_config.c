//----------------------------------------------------------------------
// Titel	:	CAN_config.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Aug 25, 2022
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "CAN_Bus.h"
#include "Motorsteuergeraet.h"
//----------------------------------------------------------------------

// Konfiguriere CAN Nachrichten
//----------------------------------------------------------------------
void CAN_config(void)
{
	CAN_Output_PaketListe[0] = CAN_Nachricht(MOTOR_CAN_SAFETY, 6, 100, 17, true);
	CAN_Output_PaketListe[1] = CAN_Nachricht(MOTOR_CAN_DIGITAL_OUT, 6, 200, 13, true);
	CAN_Output_PaketListe[2] = CAN_Nachricht(MOTOR_CAN_DIGITAL_IN, 6, 200, 14, true);
	CAN_Output_PaketListe[3] = CAN_Nachricht(MOTOR_CAN_ANALOG_IN, 8, 500, 7, true);
	CAN_Output_PaketListe[4] = CAN_Nachricht(MOTOR_CAN_DREHZAHL, 8, 20, 32, true);
	CAN_Output_PaketListe[5] = CAN_Nachricht(MOTOR_CAN_LEUCHTEN, 8, 200, 65, true);
	CAN_Output_PaketListe[6] = CAN_Nachricht(MOTOR_CAN_TEMPERATUR, 8, 500, 24, true);
	CAN_Output_PaketListe[7] = CAN_Nachricht(MOTOR_CAN_STATUS, 1, 200, 5, true);
	CAN_Output_PaketListe[8] = CAN_Nachricht(BAMOCAR_CAN_TX, 3, 100, 45, false);
}
//----------------------------------------------------------------------
