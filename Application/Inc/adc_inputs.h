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

// Konstanten definieren
//----------------------------------------------------------------------
#define TEMP_SENSOR_AVG_SLOPE_MV_PER_CELSIUS			2.5f
#define TEMP_SENSOR_VOLTAGE_MV_AT_25					760.0f
#define ADC_REFERENCE_VOLTAGE_MV						3300.0f
#define ADC_MAX_OUTPUT_VALUE							4095.0f
#define TEMP110_CAL_VALUE								((uint16_t*)((uint32_t)0x1FF0F44E))
#define TEMP30_CAL_VALUE								((uint16_t*)((uint32_t)0x1FF0F44C))
#define TEMP110											110.0f
#define TEMP30											30.0f
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
