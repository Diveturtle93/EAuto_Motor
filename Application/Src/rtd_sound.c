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
#include "inputs.h"
#include "outputs.h"
#include "BasicUart.h"
#include "millis.h"
//----------------------------------------------------------------------


// Aktiviere Ready To Drive Sound
//----------------------------------------------------------------------
bool playRTDS(void)
{
	uartTransmit("* playing RTD Sound *\n", 22);

	bool abort = false;
//	bool rtdsActive = true;
	leuchten_out.Buzzer = 1;

	unsigned long starttime = millis();
	unsigned long checktime = 0;

	while (checktime < RTDSTIME)
	{
		if (sdc_in.EmergencyRun == 1)
		{
			abort = true;
			break;
		}

		checktime = millis() - starttime;
	}

	leuchten_out.Buzzer = 0;
//	rtdsActive = false;

	if (abort == false)
	{
		leuchten_out.Buzzer = 1;
	}
	else
	{
		leuchten_out.Buzzer = 0;
	}

	return abort;
}
