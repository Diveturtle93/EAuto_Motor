//----------------------------------------------------------------------
// Titel	:	adc_inputs.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	14.08.2021
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
#include "error.h"
//----------------------------------------------------------------------

// Gaspedal einlesen
//----------------------------------------------------------------------
uint16_t ADC_Gaspedal(void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_6;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

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
	sConfig.Channel = ADC_CHANNEL_14;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Spannung KL15 einlesen
//----------------------------------------------------------------------
uint16_t ADC_KL15 (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_3;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Kuehlwassertemperatur einlesen
//----------------------------------------------------------------------
uint16_t ADC_Kuhlwassertemperatur (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_4;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Klimaflapstellung einlesen (Position ueber Poti)
//----------------------------------------------------------------------
uint16_t ADC_Klimaflap (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_5;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// PCB Temperatur einlesen
//----------------------------------------------------------------------
uint16_t ADC_PCBTemperatur (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_7;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Navibedienelement Return einlesen (2 Schalter mit unterschiedlichen Widerstaenden)
//----------------------------------------------------------------------
uint16_t ADC_Return (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_8;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Navibedienelement Info einlesen (2 Schalter mit unterschiedlichen Widerstaenden)
//----------------------------------------------------------------------
uint16_t ADC_Info (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_9;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Bremsdrucktemperatur einlesen
//----------------------------------------------------------------------
uint16_t ADC_Bremsdrucktemperatur (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_15;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// STM32 Temperatur einlesen
//----------------------------------------------------------------------
uint16_t ADC_STMTemperatur (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;								// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------
