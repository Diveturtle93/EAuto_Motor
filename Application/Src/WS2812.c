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
uint16_t pwmData[20 + (24 * MAX_LED) + 20 + 1];
uint8_t datasentflag = 0;
//----------------------------------------------------------------------

// Setze LEDs
//----------------------------------------------------------------------
void Set_LED (uint8_t LED_Num, uint8_t red, uint8_t green, uint8_t blue)
{
	LED_Data[LED_Num][0] = LED_Num;
	LED_Data[LED_Num][1] = red;
	LED_Data[LED_Num][2] = green;
	LED_Data[LED_Num][3] = blue;
}
//----------------------------------------------------------------------

// Sende Daten an LEDs
//----------------------------------------------------------------------
void WS2812_Send (void)
{
	uint32_t indx=0;
	uint32_t color;

	for (int i = 0; i < 20; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}

	for (int i = 0; i < MAX_LED; i++)
	{
		color = ((LED_Data[i][1] << 16) | (LED_Data[i][2] << 8) | (LED_Data[i][3]));

		for (int i = 23; i >= 0; i--)
		{
			if (color & (1 << i))
			{
				pwmData[indx] = 90;  // 2/3 of 135
			}

			else pwmData[indx] = 45;  // 1/3 of 135

			indx++;
		}

	}

	for (int i = 0; i < 20; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}
	pwmData[indx] = 255;
	indx++;

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
