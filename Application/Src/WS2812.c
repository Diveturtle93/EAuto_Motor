//----------------------------------------------------------------------
// Titel	:	WS2812.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Dec 1, 2023
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "tim.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "WS2812.h"
//----------------------------------------------------------------------

// Variablen definieren
//----------------------------------------------------------------------
uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];  // for brightness
uint16_t pwmData[(24*MAX_LED)+50];
uint8_t datasentflag = 0;
//----------------------------------------------------------------------

// Setze LEDs
//----------------------------------------------------------------------
void Set_LED (uint8_t LED_Num, uint8_t green, uint8_t red, uint8_t blue)
{
	LED_Data[LED_Num][0] = green;
	LED_Data[LED_Num][1] = red;
	LED_Data[LED_Num][2] = blue;
}
//----------------------------------------------------------------------

// Setze Helligkeit
//----------------------------------------------------------------------
// TODO Math includieren oder Tan Funktione schreiben
/*void Set_Brightness (uint8_t brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45)
		brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod[i][j] = (LED_Data[i][j])/(tan(angle));
		}
	}

#endif
}*/
//----------------------------------------------------------------------

// Sende Daten an LEDs
//----------------------------------------------------------------------
void WS2812_Send (void)
{
	uint32_t indx=0;
	uint32_t color;


	for (int i = 0; i < MAX_LED; i++)
	{
/*#if USE_BRIGHTNESS
		color = ((LED_Mod[i][0]<<16) | (LED_Mod[i][1]<<8) | (LED_Mod[i][2]));
#else*/
		color = ((LED_Data[i][0]<<16) | (LED_Data[i][1]<<8) | (LED_Data[i][2]));
//#endif

		for (int i = 23; i >= 0; i--)
		{
			if (color & (1 << i))
			{
				pwmData[indx] = 45;  // 2/3 of 135
			}

			else pwmData[indx] = 90;  // 1/3 of 135

			indx++;
		}

	}

	for (int i = 0; i < 50; i++)
	{
		pwmData[indx] = 255;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_2, (uint32_t *)pwmData, indx);
	while (!datasentflag){};
	datasentflag = 0;
}
//----------------------------------------------------------------------

// Timer Callback fuer DMA
//----------------------------------------------------------------------
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim3)
	{
		HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_2);
		datasentflag = 1;
	}
}
//----------------------------------------------------------------------
