//----------------------------------------------------------------------
// Titel	:	Bamocar.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	21.05.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "can.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "Bamocar.h"
#include "BasicUart.h"
#include "error.h"
#include "Motorsteuergeraet.h"
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

	// Daten zusammenfuegen
	BamoTxData[0] = BAMOCAR_REG_READ;										// Einstellung fuer lesen des Registers
	BamoTxData[1] = REG;													// Register das gelesen werden soll
	BamoTxData[2] = INTVL_IMMEDIATE;										// Register sofort senden, einmalig

	// Bamocar Register ueber CAN abrufen
	status = HAL_CAN_AddTxMessage(&hcan3, &BamoTxMsg, BamoTxData, (uint32_t *)CAN_TX_MAILBOX0);
	hal_error(status);
}
//----------------------------------------------------------------------

// Lese Bamocar Register, Zeitinterval für wiederholten Rueckgabewert
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

	// Daten zusammenfuegen
	BamoTxData[0] = BAMOCAR_REG_READ;										// Einstellung fuer lesen des Registers
	BamoTxData[1] = REG;													// Register das gelesen werden soll
	BamoTxData[2] = interval;												// Interval wie oft das Register gelesen werden soll

	// Bamocar Zeitinterval einstellen ueber CAN
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

	// Waehlen welches Register gesendet wurde
	switch (Reg)
	{
		// Register fuer aktuelle Drehzahl, speed = n
		case BAMOCAR_REG_SPEED_ACT:
			speed = ((data[2]<<8) + data[1]);
			motor1.Drehzahl = speed;
// Uart Ausgabe
#ifdef DEBUG_BAMOCAR
			ITM_SendString("Aktuelle Drehzahl\n");
#endif
			break;

		// Default Mitteilung falls Auwertung fuer Register noch nicht definiert ist
		default:
			uartTransmit("Bamocar Register nicht definiert\n", 33);
			break;
	}
}
//----------------------------------------------------------------------
