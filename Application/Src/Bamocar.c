//----------------------------------------------------------------------
// Titel	:	Bamocar.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	21.05.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfügen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfügen der STM Include-Dateien
//----------------------------------------------------------------------
#include "can.h"
//----------------------------------------------------------------------

// Einfügen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "Bamocar.h"
#include "BasicUart.h"
#include "error.h"
//----------------------------------------------------------------------

// Lese Bamocar Register
//----------------------------------------------------------------------
void readBAMOReg(uint8_t REG)
{
	CAN_TxHeaderTypeDef BamoTxMsg;
	uint8_t BamoTxData[3], status;

	// Sendenachricht erstellen
	BamoTxMsg.StdId = BAMOCAR_TX_ID;
	BamoTxMsg.ExtId = 0;
	BamoTxMsg.RTR = CAN_RTR_DATA;
	BamoTxMsg.IDE = CAN_ID_STD;
	BamoTxMsg.DLC = 3;
	BamoTxMsg.TransmitGlobalTime=DISABLE;

	BamoTxData[0] = BAMOCAR_REG_READ;
	BamoTxData[1] = REG;
	BamoTxData[2] = INTVL_IMMEDIATE;

	status = HAL_CAN_AddTxMessage(&hcan3, &BamoTxMsg, BamoTxData, (uint32_t *)CAN_TX_MAILBOX0);
	hal_error(status);
}
//----------------------------------------------------------------------

// Lese Bamocar Register, Zeitinterval für wiederholten Rückgabewert
//----------------------------------------------------------------------
void readBAMORegIntvl(uint8_t REG, uint8_t interval)
{
	CAN_TxHeaderTypeDef BamoTxMsg;
	uint8_t BamoTxData[3], status;

	// Sendenachricht erstellen
	BamoTxMsg.StdId = BAMOCAR_TX_ID;
	BamoTxMsg.ExtId = 0;
	BamoTxMsg.RTR = CAN_RTR_DATA;
	BamoTxMsg.IDE = CAN_ID_STD;
	BamoTxMsg.DLC = 3;
	BamoTxMsg.TransmitGlobalTime=DISABLE;

	BamoTxData[0] = BAMOCAR_REG_READ;
	BamoTxData[1] = REG;
	BamoTxData[2] = interval;

	status = HAL_CAN_AddTxMessage(&hcan3, &BamoTxMsg, BamoTxData, (uint32_t *)CAN_TX_MAILBOX0);
	hal_error(status);
}
//----------------------------------------------------------------------

// Ermittle Register nach Empfang Bamocar CAN-ID
//----------------------------------------------------------------------
void BAMOCAN_ID(uint8_t* data)
{
	uint8_t Reg = data[0];
	uint16_t speed = 0;

	switch (Reg)
	{
		case BAMOCAR_REG_SPEED_ACT:
			speed = ((data[2]<<8) + data[1]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Motorspeed\n", 11);
#endif

			break;
		default:
			uartTransmit("Bamocar Reg nicht definiert\n", 28);
			break;
	}
}
//----------------------------------------------------------------------
