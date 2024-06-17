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

// Schreibe Bamocar Register mit zwei Byte Daten
//----------------------------------------------------------------------
void writeBamoReg16(uint8_t REG, uint16_t data)
{
	CAN_message_t BamoTxMsg;

	// Sendenachricht erstellen
	BamoTxMsg.id = BAMOCAR_CAN_TX;											// Bamocar Sende ID
	BamoTxMsg.len = 3;														// Laenge Daten
	BamoTxMsg.flags.extended = 0;											// Extended ID = false

	// Daten zusammenfuegen
	BamoTxMsg.buf[0] = REG;													// Register welches beschrieben wird
	BamoTxMsg.buf[1] = data;												// Datenbyte 0, Bit 0 - 7
	BamoTxMsg.buf[2] = (data >> 8);											// Datenbyte 1, Bit 8 - 15

	// Bamocar Register ueber CAN abrufen
	CANwrite(&BamoTxMsg, true);
}
//----------------------------------------------------------------------

// Schreibe Bamocar Register mit vier Byte Daten
//----------------------------------------------------------------------
void writeBamoReg32(uint8_t REG, uint32_t data)
{
	CAN_message_t BamoTxMsg;

	// Sendenachricht erstellen
	BamoTxMsg.id = BAMOCAR_CAN_TX;											// Bamocar Sende ID
	BamoTxMsg.len = 5;														// Laenge Daten
	BamoTxMsg.flags.extended = 0;											// Extended ID = false

	// Daten zusammenfuegen
	BamoTxMsg.buf[0] = REG;													// Register welches beschrieben wird
	BamoTxMsg.buf[1] = data;												// Datenbyte 0, Bit 0 - 7
	BamoTxMsg.buf[2] = (data >> 8);											// Datenbyte 1, Bit 8 - 15
	BamoTxMsg.buf[3] = (data >> 16);										// Datenbyte 2, Bit 16 - 23
	BamoTxMsg.buf[4] = (data >> 24);										// Datenbyte 3, Bit 24 - 31

	// Bamocar Register ueber CAN abrufen
	CANwrite(&BamoTxMsg, true);
}
//----------------------------------------------------------------------

// Lese Bamocar Register
//----------------------------------------------------------------------
void readBamoReg(uint8_t REG)
{
	CAN_message_t BamoTxMsg;

	// Sendenachricht erstellen
	BamoTxMsg.id = BAMOCAR_CAN_TX;											// Bamocar Sende ID
	BamoTxMsg.len = 3;														// Laenge Daten

	// Daten zusammenfuegen
	BamoTxMsg.buf[0] = BAMOCAR_REG_READ;									// Einstellung fuer lesen des Registers
	BamoTxMsg.buf[1] = REG;													// Register das gelesen werden soll
	BamoTxMsg.buf[2] = INTVL_IMMEDIATE;										// Register sofort senden, einmalig

	// Bamocar Register ueber CAN abrufen
	CANwrite(&BamoTxMsg, true);
}
//----------------------------------------------------------------------

// Lese Bamocar Register, Zeitinterval für wiederholten Rueckgabewert
//----------------------------------------------------------------------
void readBamoRegIntvl(uint8_t REG, uint8_t interval)
{
	CAN_message_t BamoTxMsg;

	// Sendenachricht erstellen
	BamoTxMsg.id = BAMOCAR_CAN_TX;											// Bamocar Sende ID
	BamoTxMsg.len = 3;														// Laenge Daten

	// Daten zusammenfuegen
	BamoTxMsg.buf[0] = BAMOCAR_REG_READ;									// Einstellung fuer lesen des Registers
	BamoTxMsg.buf[1] = REG;													// Register das gelesen werden soll
	BamoTxMsg.buf[2] = interval;											// Interval wie oft das Register gelesen werden soll

	// Bamocar Zeitinterval einstellen ueber CAN
	CANwrite(&BamoTxMsg, true);
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
			motor280.Drehzahl = (speed / 4);
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
#ifdef DEBUG_BAMOCAR
			uartTransmit("Motorstrom\n", 11);
			uartTransmitNumber(strom, 10);
			uartTransmit("\n", 1);
#endif

			break;

		// Statusregister von Bamocar bekommen
		case BAMOCAR_REG_STATUS:
			bamocar_stat.status1 = ((data[4] << 24) + (data[3] << 16) + (data[2] << 8) + data[1]);

// Uart Ausgabe
#ifdef DEBUG_BAMOCAR
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
#ifdef DEBUG_BAMOCAR
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
#ifdef DEBUG_BAMOCAR
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
#ifdef DEBUG_BAMOCAR
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
	readBamoReg(BAMOCAR_REG_SN_INTERN);
	uartTransmit(STRING_BAMOCAR_SN_INTERN, sizeof(STRING_BAMOCAR_SN_INTERN));
	uartTransmitNumber(bamocar_data.data, 16);								// Bamocar interne Seriennummer anzeigen
	uartTransmit("\n", 1);

	// Seriennummer auslesen und anzeigen (Extern)
	readBamoReg(BAMOCAR_REG_SN_EXTERN);
	uartTransmit(STRING_BAMOCAR_SN_EXTERN, sizeof(STRING_BAMOCAR_SN_EXTERN));
	uartTransmitNumber(bamocar_data.data, 16);								// Bamocar externe Seriennummer anzeigen
	uartTransmit("\n", 1);

	// Firmware auslesen und anzeigen
	readBamoReg(BAMOCAR_REG_FIRMWARE);
	uartTransmit(STRING_BAMOCAR_FIRMWARE, sizeof(STRING_BAMOCAR_FIRMWARE));
	uartTransmitNumber(bamocar_data.data, 16);								// Bamocar Firmware anzeigen
	uartTransmit("\n", 1);
}
//----------------------------------------------------------------------

// IGBT Temperatur umrechnen
//----------------------------------------------------------------------
int8_t convert_IGBT_TEMP(uint16_t num)
{
	if (num > 26702)
	{
		return 100 ;
	}
	else if (num > 26261)
	{
		return 95 + 0.0113378684807256 * (num - 26261);
	}
	else if (num > 25792)
	{
		return 90 + 0.0106609808102345 * (num - 25792);
	}
	else if (num > 25296)
	{
		return 85 + 0.0100806451612903 * (num - 25296);
	}
	else if (num > 24775)
	{
		return 80 + 0.00959692898272553 * (num - 24775);
	}
	else if (num > 24232)
	{
		return 75 + 0.00920810313075507 * (num - 24232);
	}
	else if (num > 23671)
	{
		return 70 + 0.0089126559714795 * (num - 23671);
	}
	else if (num > 23097)
	{
		return 65 + 0.00871080139372822 * (num - 23097);
	}
	else if (num > 22515)
	{
		return 60 + 0.00859106529209622 * (num - 22515);
	}
	else if (num > 21933)
	{
		return 55 + 0.00859106529209622 * (num - 21933);
	}
	else if (num > 21357)
	{
		return 50 + 0.00868055555555556 * (num - 21357);
	}
	else if (num > 20793)
	{
		return 45 + 0.00886524822695036 * (num - 20793);
	}
	else if (num > 20250)
	{
		return 40 + 0.00920810313075507 * (num - 20250);
	}
	else if (num > 19733)
	{
		return 35 + 0.00967117988394584 * (num - 19733);
	}
	else if (num > 19247)
	{
		return 30 + 0.0102880658436214 * (num - 19247);
	}
	else if (num > 18797)
	{
		return 25 + 0.0111111111111111 * (num - 18797);
	}
	else if (num > 18387)
	{
		return 20 + 0.0121951219512195 * (num - 18387);
	}
	else if (num > 18017)
	{
		return 15 + 0.0135135135135135 * (num - 18017);
	}
	else if (num > 17688)
	{
		return 10 + 0.0151975683890578 * (num - 17688);
	}
	else if (num > 17400)
	{
		return 5 + 0.0173611111111111 * (num - 17400);
	}
	else if (num > 17151)
	{
		return 0 + 0.0200803212851406 * (num - 17151);
	}
	else if (num > 16938)
	{
		return -5 + 0.0234741784037559 * (num - 16938);
	}
	else if (num > 16759)
	{
		return -10 + 0.0279329608938547 * (num - 16759);
	}
	else if (num > 16609)
	{
		return -15 + 0.0333333333333333 * (num - 16609);
	}
	else if (num > 16487)
	{
		return -20 + 0.040983606557377 * (num - 16487);
	}
	else if (num > 16387)
	{
		return -25 + 0.05 * (num - 16387);
	}
	else if (num > 16308)
	{
		return -30 + 0.0632911392405063 * (num - 16308);
	}
	else if (num > 16245)
	{
		return -35;
	}
	else
	{
		return -124;
	}
}
//----------------------------------------------------------------------
