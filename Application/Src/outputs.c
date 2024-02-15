//----------------------------------------------------------------------
// Titel	:	Outputs.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	31.03.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "outputs.h"
#include "Motorsteuergeraet.h"
//----------------------------------------------------------------------

// Variablen einbinden
//----------------------------------------------------------------------
system_out_tag system_out;																			// Variable fuer Systemausgaenge definieren
highcurrent_out_tag highcurrent_out;																// Variable fuer Hochstromausgaenge definieren
leuchten_out_tag leuchten_out;																		// Variable fuer Leuchtenausgaenge definieren
komfort_out_tag komfort_out;																		// Variable fuer Komfortausgaenge definieren
//----------------------------------------------------------------------

// Initialisiere alle Ausgangsstrukturen auf default Werte
//----------------------------------------------------------------------
void init_outputs(void)
{
#ifdef DEBUG_OUTPUT
	ITM_SendString("Initialisiere Ausgaenge.\n");
#endif

	// Schreibe alle Variablen auf Null
	system_out.systemoutput = SYSTEM_OUTPUT;														// Alle System Ausgaenge auf null setzen
	highcurrent_out.high_out = HIGH_OUTPUT;															// Alle Hochstrom Ausgaenge auf null setzen
	leuchten_out.ledoutput = LED_OUTPUT;															// Alle Leuchten Ausgaenge auf null setzen
	komfort_out.komfortoutput = KOMFORT_OUTPUT;														// Alle Komfort Ausgaenge auf null setzen

	// Alle Ausgaenge setzen
	writeall_outputs();																				// Auf default setzen
}
//----------------------------------------------------------------------

// Schreibe alle Ausgaenge auf default Werte
//----------------------------------------------------------------------
void writeall_outputs(void)
{
	// Schreibe System Ausgaenge
	HAL_GPIO_WritePin(J317_GPIO_Port, J317_Pin, system_out.J317);									// Hauptrelais KL15
	HAL_GPIO_WritePin(F54_GPIO_Port, F54_Pin, system_out.F54);										// Thermoschalter Kuehlmittel, Luefter
	HAL_GPIO_WritePin(F18_GPIO_Port, F18_Pin, system_out.F18);										// Thermoschalter Kuehlmittel, Luefter
	HAL_GPIO_WritePin(DCDC_ENABLE_GPIO_Port, DCDC_ENABLE_Pin, system_out.DCDC_Enable);				// DCDC-Wandler
	HAL_GPIO_WritePin(GLUEHKERZEN_GPIO_Port, GLUEHKERZEN_Pin, system_out.Gluehkerzen);				// Gluehkerzenrelais J52
	HAL_GPIO_WritePin(MOTOR_SDC_OUT_GPIO_Port, MOTOR_SDC_OUT_Pin, system_out.MotorSDC);				// Shutdown-Circuit Motorsteuergeraet
	HAL_GPIO_WritePin(KLIMA_OUT_GPIO_Port, KLIMA_OUT_Pin, system_out.Klima);						// Klimaanlage
	HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, system_out.PowerOn);						// Selbsthaltung DCDC-Wandler Motorsteuergeraet

	// Schreibe Hochstromfaehige Ausgaenge
	HAL_GPIO_WritePin(DIGITAL1_GPIO_Port, DIGITAL1_Pin, highcurrent_out.Digital1);					// Digitaler Ausgang 1
	HAL_GPIO_WritePin(DIGITAL2_GPIO_Port, DIGITAL2_Pin, highcurrent_out.Digital2);					// Digitaler Ausgang 2
	HAL_GPIO_WritePin(PUMPE_BREMSE_GPIO_Port, PUMPE_BREMSE_Pin, highcurrent_out.Pumpe_Bremse);		// Ausgang Unterdruckpumpe Bremse
	HAL_GPIO_WritePin(PUMPE_KUEHLUNG_GPIO_Port, PUMPE_KUEHLUNG_Pin, highcurrent_out.Pumpe_Kuhlung);	// Ausgang Pumpe Kuehlkreislauf
	HAL_GPIO_WritePin(FAN1_GPIO_Port, FAN1_Pin, highcurrent_out.Fan1);								// Ausgang Luefter Kuehlergrill 1
	HAL_GPIO_WritePin(FAN2_GPIO_Port, FAN2_Pin, highcurrent_out.Fan2);								// Ausgang Luefter Kuehlergrill 2
	HAL_GPIO_WritePin(HEATER1_GPIO_Port, HEATER1_Pin, highcurrent_out.Heater1);						// Ausgang Heizung 1
	HAL_GPIO_WritePin(HEATER2_GPIO_Port, HEATER2_Pin, highcurrent_out.Heater2);						// Ausgang Heizung 2

	// Schreibe Leuchtdioden Ausgaenge
	HAL_GPIO_WritePin(BREMSLICHT_GPIO_Port, BREMSLICHT_Pin, leuchten_out.Bremslicht);				// Bremslichtrelais
	HAL_GPIO_WritePin(RUECKFAHRLICHT_GPIO_Port, RUECKFAHRLICHT_Pin, leuchten_out.Rueckfahrlicht);	// Rueckfahrlichtrelais
	HAL_GPIO_WritePin(GENERATOR_LED_GPIO_Port, GENERATOR_LED_Pin, leuchten_out.Generator);			// Generator LED Kombiinstrument
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, leuchten_out.Buzzer);							// Buzzer
	HAL_GPIO_WritePin(RUECKWARNUNG_GPIO_Port, RUECKWARNUNG_Pin, leuchten_out.Rueckwarn);			// Warnung Rueckfahrlicht Kombiinstrument
	HAL_GPIO_WritePin(LADELEUCHTE_GPIO_Port, LADELEUCHTE_Pin, leuchten_out.Ladeleuchte);			// ECO LED Kombiinstrument
	HAL_GPIO_WritePin(WISCHWARNUNG_GPIO_Port, WISCHWARNUNG_Pin, leuchten_out.Wischwarn);			// Warnung Wischwasser Kombiinstument
	HAL_GPIO_WritePin(BREMSWARNUNG_GPIO_Port, BREMSWARNUNG_Pin, leuchten_out.Bremswarn);			// Warnung Bremse Kombiinstrument
	HAL_GPIO_WritePin(OELDRUCK_GPIO_Port, OELDRUCK_Pin, leuchten_out.Oeldruck);						// Warnung Oelstand Kombiinstument
	HAL_GPIO_WritePin(NIVEAU_OUT_GPIO_Port, NIVEAU_OUT_Pin, leuchten_out.Niveau);					// Niveauregulierung LED Kombiinstrument
	HAL_GPIO_WritePin(ANHAENGER_GPIO_Port, ANHAENGER_Pin, leuchten_out.Anhaenger);					// Anhaenger LED Kombiinstrument
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);							// Rote LED Platine
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);					// Gruene LED Platine
	HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, leuchten_out.BlueLed);						// Blaue LED Platine

	// Schreibe Komfortausgaenge
	HAL_GPIO_WritePin(BC_RESET_OUT_GPIO_Port, BC_RESET_OUT_Pin, komfort_out.BC_Rst_Out);			// Boardcomputer Reset Ausgang, Steuerung Kombiinstrument
	HAL_GPIO_WritePin(BC_UP_OUT_GPIO_Port, BC_UP_OUT_Pin, komfort_out.BC_Up_Out);					// Boardcomputer Rauf Ausgang, Steuerung Kombiinstrument
	HAL_GPIO_WritePin(BC_DOWN_OUT_GPIO_Port, BC_DOWN_OUT_Pin, komfort_out.BC_Down_Out);				// Boardcomputer Runter Ausgang, Steuerung Kombiinstrument
	HAL_GPIO_WritePin(BAMOCAR_OUT1_GPIO_Port, BAMOCAR_OUT1_Pin, komfort_out.BamoOut1);				// Ausgang Bamocar 1
	HAL_GPIO_WritePin(BAMOCAR_OUT2_GPIO_Port, BAMOCAR_OUT2_Pin, komfort_out.BamoOut2);				// Ausgang Bamocar 2

#ifdef DEBUG_OUTPUT
	ITM_SendString("Ausgaenge gesetzt.\n");
	ITM_SendString("system_out:\t");
	ITM_SendNumber(system_out.systemoutput);
	ITM_SendChar('\n');
	ITM_SendString("highcurrent_out:\t");
	ITM_SendNumber(highcurrent_out.high_out);
	ITM_SendChar('\n');
	ITM_SendString("komfort_out:\t");
	ITM_SendNumber(komfort_out.komfortoutput);
	ITM_SendChar('\n');
	ITM_SendString("leuchten_out:\t");
	ITM_SendNumber(leuchten_out.ledoutput);
	ITM_SendChar('\n');
#endif
}
//----------------------------------------------------------------------

// Schreibe alle LED-Ausgaenge auf default Werte
//----------------------------------------------------------------------
void writeled_outputs(void)
{
}
//----------------------------------------------------------------------

// Teste Platinen LEDs
//----------------------------------------------------------------------
void testPCB_Leds(void)
{
	// Leds Testen
    HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);							// Teste Green LED, an
    HAL_Delay(1000);																				// Warte 1s
    HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);							// Teste Green LED, aus
    HAL_Delay(500);																					// Warte 0.5s
    HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_SET);								// Teste Blue LED, an
    HAL_Delay(1000);																				// Warte 1s
    HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_RESET);							// Teste Blue LED, aus
    HAL_Delay(500);																					// Warte 0.5s
    HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET);								// Teste Red LED, an
    HAL_Delay(1000);																				// Warte 1s
    HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_RESET);								// Teste Red LED, aus
    HAL_Delay(500);																					// Warte 0.5s
}
//----------------------------------------------------------------------

// Teste Cockpit LEDs
//----------------------------------------------------------------------
void testCockpit_Leds(void)
{
	// Leds Testen
    HAL_GPIO_WritePin(ANHAENGER_GPIO_Port, ANHAENGER_Pin, GPIO_PIN_SET);							// Teste Anhaenger LED, an (Cockpit ECO)
    HAL_Delay(1000);																				// Warte 1s
    HAL_GPIO_WritePin(ANHAENGER_GPIO_Port, ANHAENGER_Pin, GPIO_PIN_RESET);							// Teste Anhaenger LED, aus (Cockpit ECO)
    HAL_Delay(500);																					// Warte 0.5s
    HAL_GPIO_WritePin(NIVEAU_OUT_GPIO_Port, NIVEAU_OUT_Pin, GPIO_PIN_SET);							// Teste Reserve LED, an (Cockpit Niveauregulierung)
    HAL_Delay(1000);																				// Warte 1s
    HAL_GPIO_WritePin(NIVEAU_OUT_GPIO_Port, NIVEAU_OUT_Pin, GPIO_PIN_RESET);						// Teste Reserve LED, aus (Cockpit Niveauregulierung)
    HAL_Delay(500);																					// Warte 0.5s
}
//----------------------------------------------------------------------

// PWM fuer Oelstandsensor am Kombiinstrument
//----------------------------------------------------------------------
void pwm_oelstand(uint16_t time)
{
	// Auswahl wie viele Sekunden vergangen
	switch (time)																					// Zeit wird uebergeben
	{
		case 15: // 1x15 ms = 15 ms
			HAL_GPIO_WritePin(OELSTAND_TEMP_GPIO_Port, OELSTAND_TEMP_Pin, GPIO_PIN_SET);			// Bei 15ms Oelstandsensor Ausgang high
			break;
		case 45: // 3x15 ms = 45 ms
			HAL_GPIO_WritePin(OELSTAND_TEMP_GPIO_Port, OELSTAND_TEMP_Pin, GPIO_PIN_RESET);			// Bei 45ms Oelstandsensor Ausgang low
			break;
		case 75: // 5x15 ms = 75 ms
			HAL_GPIO_WritePin(OELSTAND_TEMP_GPIO_Port, OELSTAND_TEMP_Pin, GPIO_PIN_SET);			// Bei 75ms Oelstandsensor Ausgang high
			break;
		case 400: // 400ms
			HAL_GPIO_WritePin(OELSTAND_TEMP_GPIO_Port, OELSTAND_TEMP_Pin, GPIO_PIN_RESET);			// Bei 400ms Oelstandsensor Ausgang low
			break;
		default:
			break;
	}
	// Nach 405ms wird das ganze wiederholt
}
//----------------------------------------------------------------------

// Setze Cockpit auf default, alle Fehler OK
//----------------------------------------------------------------------
void cockpit_default(void)
{
	leuchten_out.Rueckwarn = 1;																		// Ruecklichtwarnung setzen
	leuchten_out.Wischwarn = 1;																		// Wischwasserwarnung setzen
	leuchten_out.Bremswarn = 1;																		// Bremslichtwarnung setzen
	leuchten_out.Oeldruck = 1;																		// Oeldruckwarnung setzen
	leuchten_out.Generator = 1;																		// Ladekontrolle setzen, invertiert
	HAL_GPIO_WritePin(RUECKWARNUNG_GPIO_Port, RUECKWARNUNG_Pin, leuchten_out.Rueckwarn);			// Fehlermeldung fuer Ruecklichtwarnung einschalten
	HAL_GPIO_WritePin(WISCHWARNUNG_GPIO_Port, WISCHWARNUNG_Pin, leuchten_out.Wischwarn);			// Fehlermeldung fuer Wischwasserwarnung einschalten
	HAL_GPIO_WritePin(BREMSWARNUNG_GPIO_Port, BREMSWARNUNG_Pin, leuchten_out.Bremswarn);			// Fehlermeldung fuer Bremslichtwarnung einschalten
	HAL_GPIO_WritePin(OELDRUCK_GPIO_Port, OELDRUCK_Pin, leuchten_out.Oeldruck);						// Fehlermeldung fuer Oeldruckwarnung einschalten
	HAL_GPIO_WritePin(GENERATOR_LED_GPIO_Port, GENERATOR_LED_Pin, leuchten_out.Generator);			// Fehlermeldung fuer Ladekontrolle ausschalten, invertiert
}
//----------------------------------------------------------------------

// Testen der Spannung am Shutdown-Circuit, Signal 1 = offen, Signal = 0 geschlossen
//----------------------------------------------------------------------
void testSDC(void)
{
	HAL_GPIO_WritePin(MOTOR_SDC_OUT_GPIO_Port, MOTOR_SDC_OUT_Pin, GPIO_PIN_SET);					// Einschalten des Shutdown-Circuit zum testen
	HAL_Delay(100);																					// Wartezeit zum setzen
	if (HAL_GPIO_ReadPin(SENSE_SDC_0_GPIO_Port, SENSE_SDC_0_Pin) == 1)								// Einlesen von SDC0 Eingang
	{
#ifndef DEBUG_SDC
		software_error(ERROR_SDC_SPANNUNG);															// Sollte Sicherung kaputt oder Kurzschluss, dann Fehlerausgeben
#else
#warning "Das Abschalten des Softwarefehlers kann unter Umstaenden zu Beschaedigung der HW fuehren."
		software_error_debug(ERROR_SDC_SPANNUNG);													// Errorfunktion stoppt Programm nicht
#endif
	}
	else
	{
	  	sdc_in.SDC12V = 1;																			// SDC Spannungsversorgung OK
	}
	HAL_Delay(100);																					// Wartezeit zum setzen
	HAL_GPIO_WritePin(MOTOR_SDC_OUT_GPIO_Port, MOTOR_SDC_OUT_Pin, GPIO_PIN_RESET);					// Ausschalten des Shutdown-Circuit zum testen
}
//----------------------------------------------------------------------
