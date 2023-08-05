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
	CAN_Output_PaketListe[0] = CAN_Nachricht(MOTOR_CAN_SAFETY, 6, 100, 17);
	CAN_Output_PaketListe[1] = CAN_Nachricht(MOTOR_CAN_DIGITAL_OUT, 6, 200, 13);
	CAN_Output_PaketListe[2] = CAN_Nachricht(MOTOR_CAN_DIGITAL_IN, 6, 200, 14);
	CAN_Output_PaketListe[3] = CAN_Nachricht(MOTOR_CAN_ANALOG_IN, 8, 500, 7);
	CAN_Output_PaketListe[4] = CAN_Nachricht(MOTOR_CAN_DREHZAHL, 8, 20, 32);
	CAN_Output_PaketListe[5] = CAN_Nachricht(MOTOR_CAN_LEUCHTEN, 8, 200, 65);
	CAN_Output_PaketListe[6] = CAN_Nachricht(MOTOR_CAN_TEMPERATUR, 8, 500, 24);
}
//----------------------------------------------------------------------
