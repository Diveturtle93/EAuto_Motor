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

// Variablen einbinden
//----------------------------------------------------------------------
bamocar_statusIO_tag bamocar_IOstatus;										// Variable fuer IO Status definieren
bamocar_status_tag bamocar_stat;											// Variable fuer Status definieren
bamocar_error_tag bamocar_error;											// Variable fuer Error definieren
bamocar_warnung_tag bamocar_warnung;										// Variable fuer Warnung definieren
bamocar_can_read_tag bamocar_data;											// Variable fuer CAN-Daten definieren
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
void BAMOCAN_ID(uint8_t* data, uint8_t dlc)
{
	uint8_t Reg = data[0];
	uint16_t speed = 0, strom;

	// Waehlen welches Register gesendet wurde
	switch (Reg)
	{
		// Drehzahl vom Bamocar bekommen
		case BAMOCAR_REG_N_ACT_FILTER:
			speed = ((data[2]<<8) + data[1]);
			motor1.Drehzahl = speed;
// Uart Ausgabe
#ifdef DEBUG_BAMOCAR
			uartTransmit("Motordrehzahl\n", 14);
			uartTransmitNumber(speed, 10);
			uartTransmit("\n", 1);
#endif
			break;

		// Stromwert von Bamocar bekommen
		case BAMOCAR_REG_I_ACT_FILTER:
			strom = ((data[2]<<8) + data[1]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Motorstrom\n", 11);
			uartTransmitNumber(strom, 10);
			uartTransmit("\n", 1);
#endif

			break;

		// Statusregister von Bamocar bekommen
		case BAMOCAR_REG_STATUS:
			bamocar_stat.status1 = ((data[4] << 24) + (data[3] << 16) + (data[2] << 8) + data[1]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Bamocar Status\n", 15);
			for (uint8_t i = 4; i > 0; i--)
			{
				uartTransmitNumber(bamocar_stat.status[i-1], 16);
				uartTransmit(" ", 1);
			}
			uartTransmit("\n", 1);
#endif

			break;

		// Errorregister von Bamocar bekommen
		case BAMOCAR_REG_ERROR:
			bamocar_error.error1 = ((data[2] << 8) + data[1]);
			bamocar_warnung.warnung1 = ((data[4] << 8) + data[3]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Bamocar Error\n", 14);
			for (uint8_t i = 0; i < 4; i++)
			{
				uartTransmitNumber(data[1+i], 16);
				uartTransmit(" ", 1);
			}
			uartTransmit("\n", 1);
#endif

			break;

		// Status IO Register von Bamocar bekommen
		case BAMOCAR_REG_STATUS_IO:
			bamocar_IOstatus.status1 = ((data[2] << 8) + data[1]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Bamocar IO Status\n", 18);
			for (uint8_t i = 0; i < 2; i++)
			{
				uartTransmitNumber(bamocar_IOstatus.status[i], 16);
				uartTransmit(" ", 1);
			}
			uartTransmit("\n", 1);
#endif

			break;

		// Firmware von Bamocar ausgelesen
		case BAMOCAR_REG_FIRMWARE:
			bamocar_data.data = ((data[2]<<8) + data[1]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Firmware\n", 9);
			uartTransmitNumber(bamocar_data.data, 16);
			uartTransmit("\n", 1);
#endif

			break;

		// Register fuer Bamocar nicht definiert, Fehler
		default:
			uartTransmit("Bamocar Register nicht definiert\n", 33);
			break;
	}
}
//----------------------------------------------------------------------

// Collect Bamocar Informationen
//----------------------------------------------------------------------
void BamocarInfo(void)
{
	#define STRING_BAMOCAR_FIRMWARE		"\nBAMOCAR Firmware:\t\t"
	#define STRING_BAMOCAR_SN_INTERN	"\nBAMOCAR Seriennummer Intern:\t\t"
	#define STRING_BAMOCAR_SN_EXTERN	"\nBAMOCAR Seriennummer Extern:\t\t"

	// Seriennummer auslesen und anzeigen (Intern)
	readBAMOReg(BAMOCAR_REG_SN_INTERN);
	uartTransmit(STRING_BAMOCAR_SN_INTERN, sizeof(STRING_BAMOCAR_SN_INTERN));
	uartTransmitNumber(bamocar_data.data, 16);								// Bamocar interne Seriennummer anzeigen
	uartTransmit("\n", 1);

	// Seriennummer auslesen und anzeigen (Extern)
	readBAMOReg(BAMOCAR_REG_SN_EXTERN);
	uartTransmit(STRING_BAMOCAR_SN_EXTERN, sizeof(STRING_BAMOCAR_SN_EXTERN));
	uartTransmitNumber(bamocar_data.data, 16);								// Bamocar externe Seriennummer anzeigen
	uartTransmit("\n", 1);

	// Firmware auslesen und anzeigen
	readBAMOReg(BAMOCAR_REG_FIRMWARE);
	uartTransmit(STRING_BAMOCAR_FIRMWARE, sizeof(STRING_BAMOCAR_FIRMWARE));
	uartTransmitNumber(bamocar_data.data, 16);								// Bamocar Firmware anzeigen
	uartTransmit("\n", 1);
}
//----------------------------------------------------------------------
