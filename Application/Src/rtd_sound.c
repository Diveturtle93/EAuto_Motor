//----------------------------------------------------------------------
// Titel	:	rtd_sound.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	06.07.2023
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
#include "rtd_sound.h"
#include "Motorsteuergeraet.h"
//----------------------------------------------------------------------


// Aktiviere Ready To Drive Sound
//----------------------------------------------------------------------
bool playRTDS(void)
{
	uartTransmit("Spiele RTDS !!!\n", 16);

	bool abort = true;
	leuchten_out.Buzzer = 1;
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, leuchten_out.Buzzer);

	uint32_t starttime = millis();
	uint32_t checktime = 0;

	while (checktime < RTDSTIME)
	{
		if (sdc_in.EmergencyRun == 1)
		{
			uartTransmit("Abbruch RTDS !!!\n", 17);
			abort = false;
			break;
		}

		CANwork();

		checktime = millis() - starttime;
	}

	leuchten_out.Buzzer = 0;
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, leuchten_out.Buzzer);

	if (abort == true)
	{
		leuchten_out.Anhaenger = 1;
	}
	else
	{
		leuchten_out.Anhaenger = 0;
	}

	return abort;
}
