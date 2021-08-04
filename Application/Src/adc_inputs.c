//----------------------------------------------------------------------
// Titel	:	adc_inputs.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	01.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfügen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfügen der STM Include-Dateien
//----------------------------------------------------------------------
#include "adc.h"
//----------------------------------------------------------------------

// Einfügen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "adc_inputs.h"
//----------------------------------------------------------------------

// Gaspedal einlesen
//----------------------------------------------------------------------
uint16_t ADC_Gaspedal(void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	// ADC Starten und Wert einlesen
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
	ADC_Data = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Bremsdruck einlesen
//----------------------------------------------------------------------
uint16_t ADC_Bremsdruck(void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_14;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	// ADC Starten und Wert einlesen
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
	ADC_Data = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------
