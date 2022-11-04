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
//----------------------------------------------------------------------

// Schreibe alle Ausgaenge auf default Werte
//----------------------------------------------------------------------
void writeall_outputs(void)
{
	/*system_out = SYSTEM_OUTPUT;
	highcurrent_out = HIGHCURRENT_OUT;
	leuchten_out = LED_OUTPUT;
	komfort_out = KOMFORT_OUTPUT;*/

/*	// Schreibe System Ausgaenge
	HAL_GPIO_WritePin(J317_GPIO_Port, J317_Pin, system_out.J317);
	HAL_GPIO_WritePin(F54_GPIO_Port, F54_Pin, system_out.F54);
	HAL_GPIO_WritePin(F18_GPIO_Port, F18_Pin, system_out.F18);
	HAL_GPIO_WritePin(DCDC_ENABLE_GPIO_Port, DCDC_ENABLE_Pin, system_out.DCDC_Enable);
	HAL_GPIO_WritePin(GLUEHKERZEN_GPIO_Port, GLUEHKERZEN_Pin, system_out.Gluehkerzen);
	HAL_GPIO_WritePin(MOTOR_SDC_OUT_GPIO_Port, MOTOR_SDC_OUT_Pin, system_out.MotorSDC);
	HAL_GPIO_WritePin(KLIMA_OUT_GPIO_Port, KLIMA_OUT_Pin, system_out.Klima);
	HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, system_out.Power_On);

	// Schreibe Hochstromfaehige Ausgaenge
	HAL_GPIO_WritePin(DIGITAL1_GPIO_Port, DIGITAL1_Pin, highcurrent_out.Digital1);
	HAL_GPIO_WritePin(DIGITAL2_GPIO_Port, DIGITAL2_Pin, highcurrent_out.Digital2);
	HAL_GPIO_WritePin(PUMPE_BREMSE_GPIO_Port, PUMPE_BREMSE_Pin, highcurrent_out.Pumpe_Bremse);
	HAL_GPIO_WritePin(PUMPE_KUEHLUNG_GPIO_Port, PUMPE_KUEHLUNG_Pin, highcurrent_out.Pumpe_Kuhlung);
	HAL_GPIO_WritePin(FAN1_GPIO_Port, FAN1_Pin, highcurrent_out.Fan1);
	HAL_GPIO_WritePin(FAN2_GPIO_Port, FAN2_Pin, highcurrent_out.Fan2);
	HAL_GPIO_WritePin(HEATER1_GPIO_Port, HEATER1_Pin, highcurrent_out.Heater1);
	HAL_GPIO_WritePin(HEATER2_GPIO_Port, HEATER2_Pin, highcurrent_out.Heater2);

	// Schreibe Leuchtdioden Ausgaenge
	HAL_GPIO_WritePin(BREMSLICHT_GPIO_Port, BREMSLICHT_Pin, leuchten_out.Bremslicht);
	HAL_GPIO_WritePin(RUECKFAHRLICHT_GPIO_Port, RUECKFAHRLICHT_Pin, leuchten_out.Rueckfahrlicht);
	HAL_GPIO_WritePin(GENERATOR_LED_GPIO_Port, GENERATOR_LED_Pin, leuchten_out.Generator);
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, leuchten_out.Buzzer);
	HAL_GPIO_WritePin(RUECKWARNUNG_GPIO_Port, RUECKWARNUNG_Pin, leuchten_out.Ruechwarn);
	HAL_GPIO_WritePin(LADELEUCHTE_GPIO_Port, LADELEUCHTE_Pin, leuchten_out.Ladeleuchte);
	HAL_GPIO_WritePin(WISCHWARNUNG_GPIO_Port, WISCHWARNUNG_Pin, leuchten_out.Wischwarn);
	HAL_GPIO_WritePin(BREMSWARNUNG_GPIO_Port, BREMSWARNUNG_Pin, leuchten_out.Bremswarn);
	HAL_GPIO_WritePin(OELSTAND_TEMP_GPIO_Port, OELSTAND_TEMP_Pin, leuchten_out.Oelstand);
	HAL_GPIO_WritePin(RESERVE_OUT_GPIO_Port, RESERVE_OUT_Pin, leuchten_out.Reserve);
	HAL_GPIO_WritePin(ANHAENGER_GPIO_Port, ANHAENGER_Pin, leuchten_out.Anhaenger);
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);
	HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, leuchten_out.BlueLed);

	// Schreibe Komfortausgaenge
	HAL_GPIO_WritePin(BC_RESET_OUT_GPIO_Port, BC_RESET_OUT_Pin, komfort_out.BC_Rst_Out);
	HAL_GPIO_WritePin(BC_UP_OUT_GPIO_Port, BC_UP_OUT_Pin, komfort_out.BC_Up_Out);
	HAL_GPIO_WritePin(BC_DOWN_OUT_GPIO_Port, BC_DOWN_OUT_Pin, komfort_out.BC_Down_Out);
	HAL_GPIO_WritePin(BAMOCAR_OUT1_GPIO_Port, BAMOCAR_OUT1_Pin, komfort_out.BamoOut1);
	HAL_GPIO_WritePin(BAMOCAR_OUT2_GPIO_Port, BAMOCAR_OUT2_Pin, komfort_out.BamoOut2);*/
}
//----------------------------------------------------------------------
