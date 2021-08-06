//----------------------------------------------------------------------
// Titel	:	Error.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.01.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------
#include "string.h"
#include "stdlib.h"
#include "inttypes.h"
//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
#include "usart.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "BasicUart.h"
//----------------------------------------------------------------------

// Uart2 Transmit Funktion
//----------------------------------------------------------------------
void uartTransmit(const char *str, const size_t size)
{
	HAL_UART_Transmit(&huart2, (uint8_t *)str, size, 1000);
}
//----------------------------------------------------------------------

// Uart2 Transmit Nummer Funktion
//----------------------------------------------------------------------
void uartTransmitNumber(const uint32_t number, const uint32_t base)
{
	char str[11];

	utoa(number, str, base);
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 1000);
}
//----------------------------------------------------------------------

// Deinitialisieren des Uart2
//----------------------------------------------------------------------
void uartReInitBasicPolling(void)
{
	HAL_UART_DMAStop(&huart2);
	HAL_UART_DeInit(&huart2);
	HAL_UART_MspDeInit(&huart2);

	HAL_UART_Init(&huart2);
	HAL_UART_MspInit(&huart2);

	HAL_UART_DMAStop(&huart2);
	HAL_DMA_DeInit(huart2.hdmatx);
	HAL_DMA_DeInit(huart2.hdmarx);
}
//----------------------------------------------------------------------
