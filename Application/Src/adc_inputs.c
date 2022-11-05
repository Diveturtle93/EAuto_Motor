//----------------------------------------------------------------------
// Titel	:	adc_inputs.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	01.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "adc.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "adc_inputs.h"
#include "error.h"
//----------------------------------------------------------------------

// Gaspedal einlesen
//----------------------------------------------------------------------
uint16_t ADC_Gaspedal(void)
{
#ifdef DEBUG_ADC_INPUTS
	ITM_SendString("ADC von Gaspedal einlesen\n");
#endif

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

#ifdef DEBUG_ADC_INPUTS
	ITM_SendString("ADC-Wert Gaspedal:\t");
	ITM_SendNumber(ADC_Data);
	ITM_SendChar('\n');
#endif

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Bremsdruck einlesen
//----------------------------------------------------------------------
uint16_t ADC_Bremsdruck(void)
{
#ifdef DEBUG_ADC_INPUTS
	ITM_SendString("ADC von Bremsdruck einlesen\n");
#endif

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

#ifdef DEBUG_ADC_INPUTS
	ITM_SendString("ADC-Wert Bremsdruck:\t");
	ITM_SendNumber(ADC_Data);
	ITM_SendChar('\n');
#endif

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------
