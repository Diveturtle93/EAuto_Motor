//----------------------------------------------------------------------
// Titel	:	adc_inputs.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	14.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_ADC_INPUTS_H_
#define INC_ADC_INPUTS_H_
//----------------------------------------------------------------------

// Define Debug Symbols
//----------------------------------------------------------------------
#define DEBUG_ADC_INPUTS
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
// STM32 interner Temperatur Sensor
//----------------------------------------------------------------------
//#define TEMP_SENSOR_AVG_SLOPE_MV_PER_CELSIUS			2.5f
//#define TEMP_SENSOR_VOLTAGE_MV_AT_25					760.0f
//#define ADC_REFERENCE_VOLTAGE_MV						3300.0f
//#define ADC_MAX_OUTPUT_VALUE							4095.0f
#define TEMP110_CAL_VALUE								((uint16_t*)((uint32_t)0x1FF0F44E))
#define TEMP30_CAL_VALUE								((uint16_t*)((uint32_t)0x1FF0F44C))
#define TEMP110											110.0f
#define TEMP30											30.0f
//----------------------------------------------------------------------
// Spannungsmessung KL15
//----------------------------------------------------------------------
#define KL15_UVOLT										2208				// Unterspannung bei 9V
#define KL15_OVOLT										3925				// Ueberspannung bei 16V
#define KL15_RES0										2200				// Unterer Widerstand Spannungsteiler
#define KL15_RES1										10000				// Oberer Parallelwiderstand Spannungsteiler
#define KL15_RES2										10000				// Oberer Parallelwiderstand SPannungsteiler
//----------------------------------------------------------------------
// Klimaflap Auswertung
//----------------------------------------------------------------------
#define KLIMAFLAP_OPENWIRE								10					// Wenn Sensor nicht angesteckt, dann Wert kleiner 10
#define KLIMAFLAP_UVOLT									2208				// Unterspannung bei 9V
#define KLIMAFLAP_OVOLT									3925				// Ueberspannung bei 16V
#define KLIMAFLAP_RES0									INF				// Oberer Widerstand Spannungsteiler
#define KLIMAFLAP_RES1									100000				// Unterer Widerstand Spannungsteiler
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
uint16_t ADC_Bremsdruck(void);
uint16_t ADC_Gaspedal (void);
uint16_t ADC_Kuhlwassertemperatur(void);
uint16_t ADC_Klimaflap(void);
uint16_t ADC_Bremsdrucktemperatur(void);
uint16_t ADC_KL15(void);
uint16_t ADC_PCBTemperatur(void);
uint16_t ADC_STMTemperatur(void);
uint16_t ADC_Return(void);
uint16_t ADC_Info(void);
//----------------------------------------------------------------------

#endif /* INC_ADC_INPUTS_H_ */
//----------------------------------------------------------------------
