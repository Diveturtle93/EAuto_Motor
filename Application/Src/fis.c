//----------------------------------------------------------------------
// Titel	:	fis.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jun 25, 2024
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "fis.h"
#include "Motorsteuergeraet.h"
//----------------------------------------------------------------------
 
// CAN IDs
//----------------------------------------------------------------------
#define DIS_SEND_ID				0x6C0
#define DIS_REC_ID				0x6C1
//----------------------------------------------------------------------
 
// Protokoll-Konstanten
//----------------------------------------------------------------------
#define RESPONSE_TIME_MS		200								// Maximale Wartezeit auf ACK in ms
#define A3_LOOP_COUNT			4								// Anzahl A3-Nachrichten pro Schleife
#define A3_LOOP_DELAY_MS		25								// Pause zwischen A3-Nachrichten in ms
#define INTER_MSG_DELAY_MS		10								// Pause zwischen Nachrichten in ms
#define KEEPALIVE_INTERVAL_MS	100								// Keep-Alive Intervall in ms
//----------------------------------------------------------------------
 
// ACK-Typen
//----------------------------------------------------------------------
#define LONG_ACK				1								// Erwartet A0-Response
#define NORMAL_ACK				2								// Erwartet B0+Counter
#define NO_ACK					3								// Kein ACK erwartet
//----------------------------------------------------------------------
 
// Sende-Nachrichten
//----------------------------------------------------------------------
static uint8_t A0_MESSAGE[]		= {0xA0, 0x0F, 0x8A, 0xFF, 0x4A, 0xFF};
static uint8_t M15_SEND[]		= {0x10, 0x15, 0x02, 0x01, 0x02, 0x00, 0x00};
static uint8_t M01_02_00_SEND[]	= {0x10, 0x01, 0x02, 0x00};
static uint8_t M01_02_01_SEND[]	= {0x10, 0x01, 0x02, 0x01};
static uint8_t M01_01_00_SEND[]	= {0x10, 0x01, 0x01, 0x00};
static uint8_t M08_SEND[]		= {0x10, 0x08};
static uint8_t M24_SEND[]		= {0x10, 0x24};
static uint8_t M28_SEND[]		= {0x10, 0x28};
static uint8_t M09_1_SEND[]	= {0x20, 0x09, 0x20, 0x00, 0x50, 0x07, 0x12, 0x4E};
static uint8_t M09_2_SEND[]	= {0x20, 0x41, 0x56, 0x4C, 0x4C, 0x2D, 0x30, 0x32};
static uint8_t M09_3_SEND[]	= {0x10, 0x30, 0x30, 0x00};
static uint8_t M20_SEND[]		= {0x10, 0x20, 0x3B, 0xA0, 0x00};
static uint8_t M39_SEND[]		= {0x10, 0x39};
static uint8_t M2F_SEND[]		= {0x10, 0x2F};
static uint8_t R_CLAIM[]		= {0x10, 0x52, 0x05, 0x80, 0x00, 0x1B, 0x40, 0x30};
static uint8_t R_CLEAR[]		= {0x10, 0x52, 0x05, 0x02, 0x00, 0x1B, 0x40, 0x30};
static uint8_t A3_MESSAGE[]	= {0xA3};
//----------------------------------------------------------------------
 
// Draw-Nachrichten
//----------------------------------------------------------------------
static uint8_t DRAW_TEST1[]	= {0x20, 0x57, 0x0F, 0x06, 0x01, 0x01, 0x48, 0x41};
static uint8_t DRAW_TEST2[]	= {0x20, 0x4C, 0x4C, 0x4F, 0x65, 0x50, 0x08, 0x09};
static uint8_t DRAW_TEST3[]	= {0x10, 0x0C, 0x09, 0x10};
//----------------------------------------------------------------------
 
// Empfangs-Nachrichten
//----------------------------------------------------------------------
static uint8_t A0_RESPONSE[]	= {0xA1, 0x0F, 0x8A, 0xFF, 0x4A, 0xFF};
static uint8_t M00_01_REC[]	= {0x10, 0x00, 0x01};
static uint8_t M09_1_REC[]	= {0x20, 0x09, 0x20, 0x0B, 0x50, 0x00, 0x32, 0x44};
static uint8_t M09_2_REC[]	= {0x10, 0x30, 0x34, 0x00, 0x31, 0x00};
static uint8_t M05_1_REC[]	= {0x20, 0x29, 0x02, 0x39, 0x1E, 0xD0, 0x07, 0x01};
static uint8_t M05_2_REC[]	= {0x10, 0x01};
static uint8_t M21_REC[]		= {0x10, 0x21, 0x3B, 0xA0, 0x00};
static uint8_t M53_05_REC[]	= {0x10, 0x53, 0x05};
static uint8_t M53_84_REC[]	= {0x10, 0x53, 0x84};
static uint8_t M53_85_REC[]	= {0x10, 0x53, 0x85};
static uint8_t M2E_REC[]		= {0x10, 0x2E};
//----------------------------------------------------------------------
 
// State-Machine Zustaende
//----------------------------------------------------------------------
typedef enum
{
	// Initialisierung: Vorbereitung
	FIS_IDLE = 0,
 
	// initDIS: Verbindungsaufbau (Zustaende 1-22)
	FIS_INIT_A0_SEND,								// 1:  Sende A0_MESSAGE
	FIS_INIT_A0_DELAY,								// 2:  Warte 10ms
	FIS_INIT_M15_SEND,								// 3:  Sende M15
	FIS_INIT_M00_01_WAIT_1,							// 4:  Warte auf M00_01
	FIS_INIT_DELAY_1,								// 5:  Warte 10ms
	FIS_INIT_M01_02_00_SEND,						// 6:  Sende M01_02_00
	FIS_INIT_M00_01_WAIT_2,							// 7:  Warte auf M00_01
	FIS_INIT_DELAY_2,								// 8:  Warte 10ms
	FIS_INIT_A3_LOOP_1,								// 9:  4x A3 senden mit 25ms Pause
	FIS_INIT_A3_LOOP_1_DELAY,						// 10: Pause zwischen A3-Nachrichten
	FIS_INIT_DELAY_3,								// 11: Warte 10ms
	FIS_INIT_M01_02_01_SEND,						// 12: Sende M01_02_01
	FIS_INIT_M00_01_WAIT_3,							// 13: Warte auf M00_01
	FIS_INIT_DELAY_4,								// 14: Warte 10ms
	FIS_INIT_M01_01_00_SEND,						// 15: Sende M01_01_00
	FIS_INIT_DELAY_5,								// 16: Warte 10ms
	FIS_INIT_M08_SEND,								// 17: Sende M08
	FIS_INIT_M09_1_WAIT,							// 18: Warte auf M09_1
	FIS_INIT_M09_2_WAIT,							// 19: Warte auf M09_2
	FIS_INIT_DELAY_6,								// 20: Warte 10ms
	FIS_INIT_M09_SEND_1,							// 21: Sende M09_1_SEND
	FIS_INIT_M09_SEND_2,							// 22: Sende M09_2_SEND
	FIS_INIT_M09_SEND_3,							// 23: Sende M09_3_SEND
	FIS_INIT_DELAY_7,								// 24: Warte 10ms
	FIS_INIT_M24_SEND,								// 25: Sende M24
	FIS_INIT_DELAY_8,								// 26: Warte 10ms
	FIS_INIT_A3_LOOP_2,								// 27: 4x A3 senden mit 25ms Pause
	FIS_INIT_A3_LOOP_2_DELAY,						// 28: Pause zwischen A3-Nachrichten
	FIS_INIT_M28_SEND,								// 29: Sende M28
	FIS_INIT_M05_1_WAIT,							// 30: Warte auf M05_1
	FIS_INIT_M05_2_WAIT,							// 31: Warte auf M05_2
	FIS_INIT_DELAY_9,								// 32: Warte 10ms
	FIS_INIT_M20_SEND,								// 33: Sende M20
	FIS_INIT_M21_WAIT,								// 34: Warte auf M21
 
	// claimScreen: Display beanspruchen (Zustaende 35-44)
	FIS_CLAIM_R_CLAIM_1_SEND,						// 35: Sende R_CLAIM
	FIS_CLAIM_M53_84_WAIT,							// 36: Warte auf M53_84
	FIS_CLAIM_M53_05_WAIT,							// 37: Warte auf M53_05
	FIS_CLAIM_M2E_WAIT,								// 38: Warte auf M2E
	FIS_CLAIM_DELAY_1,								// 39: Warte 10ms
	FIS_CLAIM_M2F_SEND,								// 40: Sende M2F
	FIS_CLAIM_DELAY_2,								// 41: Warte 10ms
	FIS_CLAIM_R_CLAIM_2_SEND,						// 42: Sende R_CLAIM (zweites Mal)
	FIS_CLAIM_M53_85_WAIT,							// 43: Warte auf M53_85
	FIS_CLAIM_DELAY_3,								// 44: Warte 10ms
	FIS_CLAIM_R_CLEAR_SEND,							// 45: Sende R_CLEAR
	FIS_CLAIM_DELAY_4,								// 46: Warte 10ms
	FIS_CLAIM_M39_SEND,								// 47: Sende M39
 
	// drawFrame: Inhalt zeichnen (Zustaende 48-53)
	FIS_DRAW_SEND_1,								// 48: Sende DRAW_TEST1
	FIS_DRAW_SEND_2,								// 49: Sende DRAW_TEST2
	FIS_DRAW_SEND_3,								// 50: Sende DRAW_TEST3
	FIS_DRAW_A3_1,									// 51: Sende A3
	FIS_DRAW_M39,									// 52: Sende M39
	FIS_DRAW_A3_2,									// 53: Sende A3 (abschliessend)
 
	// Betrieb: Keep-Alive (Zustande 54-55)
	FIS_RUNNING,									// 54: Warte auf naechsten Keep-Alive
	FIS_KEEPALIVE_SEND,								// 55: Sende A3 Keep-Alive
	FIS_KEEPALIVE_WAIT,								// 56: Warte auf A0-Response
 
	// Fehler
	FIS_ERROR										// 57: Fehler — Neustart
} FIS_State_t;
//----------------------------------------------------------------------
 
// Interne Zustandsvariablen
//----------------------------------------------------------------------
static FIS_State_t	fis_state		= FIS_IDLE;
static uint32_t		fis_timer		= 0;			// Zeitstempel fuer Verzoegerungen und Timeouts
static uint8_t		fis_loop_cnt	= 0;			// Zaehler fuer A3-Schleifen
static uint8_t		sendCounter		= 0;			// Sendesequenz-Zaehler
static uint8_t		recCounter		= 0;			// Empfangssequenz-Zaehler
static uint8_t		expectedAck		= NO_ACK;		// Erwarteter ACK-Typ
//----------------------------------------------------------------------
 
// CAN-Strukturen
//----------------------------------------------------------------------
static CAN_TxHeaderTypeDef	TxNavi	= {DIS_SEND_ID, 0, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE};
static CAN_RxHeaderTypeDef	RxNavi;
//----------------------------------------------------------------------
 
// Interne Hilfsfunktion: Sende ACK auf empfangene Nachricht
//----------------------------------------------------------------------
static void fis_send_ack (void)
{
	uint8_t ackBuf[1];
	ackBuf[0] = (uint8_t)(0xB0 + (recCounter % 15));
	TxNavi.DLC = 1;
	HAL_CAN_AddTxMessage(&hcan2, &TxNavi, ackBuf, (uint32_t *)CAN_TX_MAILBOX0);
	while (HAL_CAN_IsTxMessagePending(&hcan2, CAN_TX_MAILBOX0) == 1)
	{
		// Warte bis Mailbox frei
	}
}
//----------------------------------------------------------------------
 
// Interne Hilfsfunktion: Lese alle wartenden Nachrichten und sende ACK
//----------------------------------------------------------------------
static void fis_read_pending (void)
{
	uint8_t recBuf[8];
	uint8_t rxLen;
 
	while (HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0)
	{
		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, recBuf);
		rxLen = RxNavi.DLC;
 
		if (RxNavi.StdId == DIS_REC_ID)
		{
			if (rxLen > 1)									// Kein ACK oder A3
			{
				recCounter++;
				if (recBuf[0] < 0x20)						// Keine 2X-Nachricht
				{
					fis_send_ack();
				}
			}
		}
	}
}
//----------------------------------------------------------------------
 
// Interne Hilfsfunktion: Sende eine Nachricht (nicht-blockierend)
// Setzt sendCounter, expectedAck und schickt die Nachricht ab.
// Kehrt sofort zurueck — kein Warten auf ACK.
//----------------------------------------------------------------------
static void fis_send_msg (uint8_t *message, uint8_t len)
{
	uint8_t sendBuf[8] = {0};
 
	for (int i = 0; i < len; i++)
	{
		sendBuf[i] = message[i];
	}
 
	if ((sendBuf[0] == 0xA3) || (sendBuf[0] == 0xA0))
	{
		// A0/A3: LONG_ACK erwartet, Sequenzbyte unveraendert
		expectedAck = LONG_ACK;
	}
	else
	{
		// Regulaere Nachricht: Sequenzbyte setzen
		sendBuf[0] = (uint8_t)(sendBuf[0] + (sendCounter % 16));
		sendCounter++;
 
		if (sendBuf[0] >= 0x20)
		{
			// 2X-Nachricht: kein ACK erwartet
			expectedAck = NO_ACK;
		}
		else
		{
			// 1X-Nachricht: normaler ACK erwartet
			expectedAck = NORMAL_ACK;
		}
	}
 
	// Wartende Nachrichten vorab leeren
	fis_read_pending();
 
	// Nachricht senden
	TxNavi.DLC = len;
	HAL_CAN_AddTxMessage(&hcan2, &TxNavi, sendBuf, (uint32_t *)CAN_TX_MAILBOX0);
	while (HAL_CAN_IsTxMessagePending(&hcan2, CAN_TX_MAILBOX0) == 1)
	{
		// Warte bis Mailbox frei
	}
 
	// Timer fuer ACK-Timeout starten
	fis_timer = millis();
}
//----------------------------------------------------------------------
 
// Interne Hilfsfunktion: Pruefe ob ACK empfangen wurde (nicht-blockierend)
// Rueckgabe:
//   0   = noch kein ACK, weiter warten
//   1   = ACK korrekt empfangen
//   255 = Timeout
//----------------------------------------------------------------------
static uint8_t fis_check_ack (void)
{
	uint8_t ackBuf[8];
	uint8_t rxLen;
 
	// Timeout pruefen
	if ((millis() - fis_timer) > RESPONSE_TIME_MS)
	{
		return 255;
	}
 
	// Kein ACK noetig
	if (expectedAck == NO_ACK)
	{
		return 1;
	}
 
	// FIFO leer — noch warten
	if (HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) == 0)
	{
		return 0;
	}
 
	HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, ackBuf);
	rxLen = RxNavi.DLC;
 
	if (RxNavi.StdId != DIS_REC_ID)
	{
		return 0;
	}
 
	switch (expectedAck)
	{
		case LONG_ACK:
		{
			// Vergleiche Byte fuer Byte mit A0_RESPONSE
			for (int i = 0; i < rxLen; i++)
			{
				if (ackBuf[i] != A0_RESPONSE[i])
				{
					return 0;
				}
			}
			return 1;
		}
		case NORMAL_ACK:
		{
			if (ackBuf[0] == (uint8_t)(0xB0 + (recCounter % 15)))
			{
				return 1;
			}
			return 0;
		}
		default:
		{
			return 0;
		}
	}
}
//----------------------------------------------------------------------
 
// Interne Hilfsfunktion: Warte auf bestimmte eingehende Nachricht (nicht-blockierend)
// Rueckgabe:
//   0   = Nachricht noch nicht empfangen
//   1   = Nachricht korrekt empfangen und ACK gesendet
//   255 = Timeout
//----------------------------------------------------------------------
static uint8_t fis_wait_msg (uint8_t *expected)
{
	uint8_t recBuf[8];
 
	// Timeout pruefen
	if ((millis() - fis_timer) > RESPONSE_TIME_MS)
	{
		return 255;
	}
 
	// FIFO leer — noch warten
	if (HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) == 0)
	{
		return 0;
	}
 
	HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, recBuf);
 
	if (RxNavi.StdId != DIS_REC_ID)
	{
		return 0;
	}
 
	// Erstes Byte mit Sequenznummer vergleichen
	if (recBuf[0] == (uint8_t)(expected[0] + (recCounter % 15)))
	{
		recCounter++;
 
		// ACK senden falls keine 2X-Nachricht
		if (recBuf[0] < 0x20)
		{
			fis_send_ack();
		}
		return 1;
	}
 
	return 0;
}
//----------------------------------------------------------------------
 
// Interne Hilfsfunktion: Warte auf Keep-Alive Response (nicht-blockierend)
// Prueft ob die empfangene Nachricht der A0_RESPONSE entspricht.
// Rueckgabe:
//   0   = Antwort noch nicht empfangen
//   1   = Antwort korrekt empfangen
//   255 = Timeout
//----------------------------------------------------------------------
static uint8_t fis_wait_ka_response (void)
{
	uint8_t recBuf[8];
	uint8_t rxLen;
 
	// Timeout pruefen
	if ((millis() - fis_timer) > RESPONSE_TIME_MS)
	{
		return 255;
	}
 
	// FIFO leer — noch warten
	if (HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) == 0)
	{
		return 0;
	}
 
	HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, recBuf);
	rxLen = RxNavi.DLC;
 
	if (RxNavi.StdId != DIS_REC_ID)
	{
		return 0;
	}
 
	// Vergleiche Byte fuer Byte mit A0_RESPONSE
	for (int i = 0; i < rxLen; i++)
	{
		if (recBuf[i] != A0_RESPONSE[i])
		{
			return 0;
		}
	}
 
	return 1;
}
//----------------------------------------------------------------------
 
// Oeffentliche Funktion: FIS zuruecksetzen und Kommunikation neu starten
//----------------------------------------------------------------------
void FIS_Start (void)
{
	fis_state		= FIS_IDLE;
	fis_timer		= 0;
	fis_loop_cnt	= 0;
	sendCounter		= 0;
	recCounter		= 0;
	expectedAck		= NO_ACK;
}
//----------------------------------------------------------------------
 
// Oeffentliche Funktion: Aktuellen Zustand der State-Machine abfragen
//----------------------------------------------------------------------
FIS_Status_t FIS_GetStatus (void)
{
	if (fis_state == FIS_IDLE)
	{
		return FIS_STATUS_IDLE;
	}
	else if (fis_state == FIS_ERROR)
	{
		return FIS_STATUS_ERROR;
	}
	else if (fis_state == FIS_RUNNING || fis_state == FIS_KEEPALIVE_SEND || fis_state == FIS_KEEPALIVE_WAIT)
	{
		return FIS_STATUS_RUNNING;
	}
	else
	{
		return FIS_STATUS_INIT;
	}
}
//----------------------------------------------------------------------
 
// Hauptfunktion: FIS Task — muss zyklisch im Hauptloop aufgerufen werden
// Verarbeitet pro Aufruf genau einen Schritt und kehrt sofort zurueck.
//----------------------------------------------------------------------
void FIS_Task (void)
{
	uint8_t result;
 
	switch (fis_state)
	{
		//--------------------------------------------------------------
		// IDLE: Initialisierung starten
		//--------------------------------------------------------------
		case FIS_IDLE:
		{
			sendCounter		= 0;
			recCounter		= 0;
			fis_loop_cnt	= 0;
			fis_state		= FIS_INIT_A0_SEND;
			break;
		}
 
		//--------------------------------------------------------------
		// INIT: Verbindungsaufbau
		//--------------------------------------------------------------
 
		// Schritt 1: Sende A0_MESSAGE, starte 10ms Pause
		case FIS_INIT_A0_SEND:
		{
			fis_send_msg(A0_MESSAGE, sizeof(A0_MESSAGE));
			fis_timer	= millis();
			fis_state	= FIS_INIT_A0_DELAY;
			break;
		}
 
		// Schritt 2: Warte 10ms
		case FIS_INIT_A0_DELAY:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_INIT_M15_SEND;
			}
			break;
		}
 
		// Schritt 3: Sende M15, starte Timeout fuer Antwort
		case FIS_INIT_M15_SEND:
		{
			fis_send_msg(M15_SEND, sizeof(M15_SEND));
			fis_timer	= millis();
			fis_state	= FIS_INIT_M00_01_WAIT_1;
			break;
		}
 
		// Schritt 4: Warte auf M00_01 Antwort
		case FIS_INIT_M00_01_WAIT_1:
		{
			result = fis_wait_msg(M00_01_REC);
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_INIT_DELAY_1;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		// Schritt 5: Warte 10ms
		case FIS_INIT_DELAY_1:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_INIT_M01_02_00_SEND;
			}
			break;
		}
 
		// Schritt 6: Sende M01_02_00
		case FIS_INIT_M01_02_00_SEND:
		{
			fis_send_msg(M01_02_00_SEND, sizeof(M01_02_00_SEND));
			fis_timer	= millis();
			fis_state	= FIS_INIT_M00_01_WAIT_2;
			break;
		}
 
		// Schritt 7: Warte auf M00_01 Antwort
		case FIS_INIT_M00_01_WAIT_2:
		{
			result = fis_wait_msg(M00_01_REC);
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_INIT_DELAY_2;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		// Schritt 8: Warte 10ms
		case FIS_INIT_DELAY_2:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_loop_cnt	= 0;
				fis_state		= FIS_INIT_A3_LOOP_1;
			}
			break;
		}
 
		// Schritt 9: Sende eine A3-Nachricht der ersten Schleife
		case FIS_INIT_A3_LOOP_1:
		{
			if (fis_loop_cnt < A3_LOOP_COUNT)
			{
				fis_send_msg(A3_MESSAGE, sizeof(A3_MESSAGE));
				fis_timer	= millis();
				fis_state	= FIS_INIT_A3_LOOP_1_DELAY;
			}
			else
			{
				fis_loop_cnt	= 0;
				fis_timer		= millis();
				fis_state		= FIS_INIT_DELAY_3;
			}
			break;
		}
 
		// Schritt 10: 25ms Pause zwischen A3-Nachrichten, lese Eingang
		case FIS_INIT_A3_LOOP_1_DELAY:
		{
			fis_read_pending();
			if ((millis() - fis_timer) >= A3_LOOP_DELAY_MS)
			{
				fis_loop_cnt++;
				fis_state = FIS_INIT_A3_LOOP_1;
			}
			break;
		}
 
		// Schritt 11: Warte 10ms
		case FIS_INIT_DELAY_3:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_INIT_M01_02_01_SEND;
			}
			break;
		}
 
		// Schritt 12: Sende M01_02_01
		case FIS_INIT_M01_02_01_SEND:
		{
			fis_send_msg(M01_02_01_SEND, sizeof(M01_02_01_SEND));
			fis_timer	= millis();
			fis_state	= FIS_INIT_M00_01_WAIT_3;
			break;
		}
 
		// Schritt 13: Warte auf M00_01 Antwort
		case FIS_INIT_M00_01_WAIT_3:
		{
			result = fis_wait_msg(M00_01_REC);
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_INIT_DELAY_4;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		// Schritt 14: Warte 10ms
		case FIS_INIT_DELAY_4:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_INIT_M01_01_00_SEND;
			}
			break;
		}
 
		// Schritt 15: Sende M01_01_00
		case FIS_INIT_M01_01_00_SEND:
		{
			fis_send_msg(M01_01_00_SEND, sizeof(M01_01_00_SEND));
			fis_timer	= millis();
			fis_state	= FIS_INIT_DELAY_5;
			break;
		}
 
		// Schritt 16: Warte 10ms
		case FIS_INIT_DELAY_5:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_INIT_M08_SEND;
			}
			break;
		}
 
		// Schritt 17: Sende M08
		case FIS_INIT_M08_SEND:
		{
			fis_send_msg(M08_SEND, sizeof(M08_SEND));
			fis_timer	= millis();
			fis_state	= FIS_INIT_M09_1_WAIT;
			break;
		}
 
		// Schritt 18: Warte auf M09_1 Antwort
		case FIS_INIT_M09_1_WAIT:
		{
			result = fis_wait_msg(M09_1_REC);
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_INIT_M09_2_WAIT;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		// Schritt 19: Warte auf M09_2 Antwort
		case FIS_INIT_M09_2_WAIT:
		{
			result = fis_wait_msg(M09_2_REC);
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_INIT_DELAY_6;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		// Schritt 20: Warte 10ms
		case FIS_INIT_DELAY_6:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_INIT_M09_SEND_1;
			}
			break;
		}
 
		// Schritt 21: Sende M09_1_SEND (2X-Nachricht, kein ACK)
		case FIS_INIT_M09_SEND_1:
		{
			fis_send_msg(M09_1_SEND, sizeof(M09_1_SEND));
			fis_state = FIS_INIT_M09_SEND_2;
			break;
		}
 
		// Schritt 22: Sende M09_2_SEND (2X-Nachricht, kein ACK)
		case FIS_INIT_M09_SEND_2:
		{
			fis_send_msg(M09_2_SEND, sizeof(M09_2_SEND));
			fis_state = FIS_INIT_M09_SEND_3;
			break;
		}
 
		// Schritt 23: Sende M09_3_SEND, starte ACK-Warten
		case FIS_INIT_M09_SEND_3:
		{
			fis_send_msg(M09_3_SEND, sizeof(M09_3_SEND));
			fis_timer	= millis();
			fis_state	= FIS_INIT_DELAY_7;
			break;
		}
 
		// Schritt 24: Warte 10ms
		case FIS_INIT_DELAY_7:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_INIT_M24_SEND;
			}
			break;
		}
 
		// Schritt 25: Sende M24
		case FIS_INIT_M24_SEND:
		{
			fis_send_msg(M24_SEND, sizeof(M24_SEND));
			fis_timer	= millis();
			fis_state	= FIS_INIT_DELAY_8;
			break;
		}
 
		// Schritt 26: Warte 10ms
		case FIS_INIT_DELAY_8:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_loop_cnt	= 0;
				fis_state		= FIS_INIT_A3_LOOP_2;
			}
			break;
		}
 
		// Schritt 27: Sende eine A3-Nachricht der zweiten Schleife
		case FIS_INIT_A3_LOOP_2:
		{
			if (fis_loop_cnt < A3_LOOP_COUNT)
			{
				fis_send_msg(A3_MESSAGE, sizeof(A3_MESSAGE));
				fis_timer	= millis();
				fis_state	= FIS_INIT_A3_LOOP_2_DELAY;
			}
			else
			{
				fis_loop_cnt	= 0;
				fis_state		= FIS_INIT_M28_SEND;
			}
			break;
		}
 
		// Schritt 28: 25ms Pause zwischen A3-Nachrichten, lese Eingang
		case FIS_INIT_A3_LOOP_2_DELAY:
		{
			fis_read_pending();
			if ((millis() - fis_timer) >= A3_LOOP_DELAY_MS)
			{
				fis_loop_cnt++;
				fis_state = FIS_INIT_A3_LOOP_2;
			}
			break;
		}
 
		// Schritt 29: Sende M28
		case FIS_INIT_M28_SEND:
		{
			fis_send_msg(M28_SEND, sizeof(M28_SEND));
			fis_timer	= millis();
			fis_state	= FIS_INIT_M05_1_WAIT;
			break;
		}
 
		// Schritt 30: Warte auf M05_1 Antwort
		case FIS_INIT_M05_1_WAIT:
		{
			result = fis_wait_msg(M05_1_REC);
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_INIT_M05_2_WAIT;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		// Schritt 31: Warte auf M05_2 Antwort
		case FIS_INIT_M05_2_WAIT:
		{
			result = fis_wait_msg(M05_2_REC);
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_INIT_DELAY_9;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		// Schritt 32: Warte 10ms
		case FIS_INIT_DELAY_9:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_INIT_M20_SEND;
			}
			break;
		}
 
		// Schritt 33: Sende M20
		case FIS_INIT_M20_SEND:
		{
			fis_send_msg(M20_SEND, sizeof(M20_SEND));
			fis_timer	= millis();
			fis_state	= FIS_INIT_M21_WAIT;
			break;
		}
 
		// Schritt 34: Warte auf M21 Antwort
		case FIS_INIT_M21_WAIT:
		{
			result = fis_wait_msg(M21_REC);
			if (result == 1)
			{
				fis_state = FIS_CLAIM_R_CLAIM_1_SEND;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		//--------------------------------------------------------------
		// CLAIM: Display beanspruchen
		//--------------------------------------------------------------
 
		// Schritt 35: Sende R_CLAIM
		case FIS_CLAIM_R_CLAIM_1_SEND:
		{
			fis_send_msg(R_CLAIM, sizeof(R_CLAIM));
			fis_timer	= millis();
			fis_state	= FIS_CLAIM_M53_84_WAIT;
			break;
		}
 
		// Schritt 36: Warte auf M53_84
		case FIS_CLAIM_M53_84_WAIT:
		{
			result = fis_wait_msg(M53_84_REC);
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_CLAIM_M53_05_WAIT;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		// Schritt 37: Warte auf M53_05
		case FIS_CLAIM_M53_05_WAIT:
		{
			result = fis_wait_msg(M53_05_REC);
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_CLAIM_M2E_WAIT;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		// Schritt 38: Warte auf M2E
		case FIS_CLAIM_M2E_WAIT:
		{
			result = fis_wait_msg(M2E_REC);
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_CLAIM_DELAY_1;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		// Schritt 39: Warte 10ms
		case FIS_CLAIM_DELAY_1:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_CLAIM_M2F_SEND;
			}
			break;
		}
 
		// Schritt 40: Sende M2F
		case FIS_CLAIM_M2F_SEND:
		{
			fis_send_msg(M2F_SEND, sizeof(M2F_SEND));
			fis_timer	= millis();
			fis_state	= FIS_CLAIM_DELAY_2;
			break;
		}
 
		// Schritt 41: Warte 10ms
		case FIS_CLAIM_DELAY_2:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_CLAIM_R_CLAIM_2_SEND;
			}
			break;
		}
 
		// Schritt 42: Sende R_CLAIM (zweites Mal)
		case FIS_CLAIM_R_CLAIM_2_SEND:
		{
			fis_send_msg(R_CLAIM, sizeof(R_CLAIM));
			fis_timer	= millis();
			fis_state	= FIS_CLAIM_M53_85_WAIT;
			break;
		}
 
		// Schritt 43: Warte auf M53_85
		case FIS_CLAIM_M53_85_WAIT:
		{
			result = fis_wait_msg(M53_85_REC);
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_CLAIM_DELAY_3;
			}
			else if (result == 255)
			{
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		// Schritt 44: Warte 10ms
		case FIS_CLAIM_DELAY_3:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_CLAIM_R_CLEAR_SEND;
			}
			break;
		}
 
		// Schritt 45: Sende R_CLEAR
		case FIS_CLAIM_R_CLEAR_SEND:
		{
			fis_send_msg(R_CLEAR, sizeof(R_CLEAR));
			fis_timer	= millis();
			fis_state	= FIS_CLAIM_DELAY_4;
			break;
		}
 
		// Schritt 46: Warte 10ms
		case FIS_CLAIM_DELAY_4:
		{
			if ((millis() - fis_timer) >= INTER_MSG_DELAY_MS)
			{
				fis_state = FIS_CLAIM_M39_SEND;
			}
			break;
		}
 
		// Schritt 47: Sende M39 — claimScreen abgeschlossen
		case FIS_CLAIM_M39_SEND:
		{
			fis_send_msg(M39_SEND, sizeof(M39_SEND));
			fis_state = FIS_DRAW_SEND_1;
			break;
		}
 
		//--------------------------------------------------------------
		// DRAW: Inhalt auf Display zeichnen
		//--------------------------------------------------------------
 
		// Schritt 48: Sende DRAW_TEST1 (2X-Nachricht)
		case FIS_DRAW_SEND_1:
		{
			fis_send_msg(DRAW_TEST1, sizeof(DRAW_TEST1));
			fis_state = FIS_DRAW_SEND_2;
			break;
		}
 
		// Schritt 49: Sende DRAW_TEST2 (2X-Nachricht)
		case FIS_DRAW_SEND_2:
		{
			fis_send_msg(DRAW_TEST2, sizeof(DRAW_TEST2));
			fis_state = FIS_DRAW_SEND_3;
			break;
		}
 
		// Schritt 50: Sende DRAW_TEST3
		case FIS_DRAW_SEND_3:
		{
			fis_send_msg(DRAW_TEST3, sizeof(DRAW_TEST3));
			fis_state = FIS_DRAW_A3_1;
			break;
		}
 
		// Schritt 51: Sende A3
		case FIS_DRAW_A3_1:
		{
			fis_send_msg(A3_MESSAGE, sizeof(A3_MESSAGE));
			fis_state = FIS_DRAW_M39;
			break;
		}
 
		// Schritt 52: Sende M39
		case FIS_DRAW_M39:
		{
			fis_send_msg(M39_SEND, sizeof(M39_SEND));
			fis_state = FIS_DRAW_A3_2;
			break;
		}
 
		// Schritt 53: Sende A3 abschliessend — drawFrame abgeschlossen
		case FIS_DRAW_A3_2:
		{
			fis_send_msg(A3_MESSAGE, sizeof(A3_MESSAGE));
			fis_timer	= millis();
			fis_state	= FIS_RUNNING;
			break;
		}
 
		//--------------------------------------------------------------
		// RUNNING: Keep-Alive im Intervall senden
		//--------------------------------------------------------------
 
		// Warte auf naechsten Keep-Alive Zeitpunkt
		case FIS_RUNNING:
		{
			if ((millis() - fis_timer) >= KEEPALIVE_INTERVAL_MS)
			{
				fis_state = FIS_KEEPALIVE_SEND;
			}
			break;
		}
 
		// Sende A3 als Keep-Alive
		case FIS_KEEPALIVE_SEND:
		{
			fis_read_pending();
			fis_send_msg(A3_MESSAGE, sizeof(A3_MESSAGE));
			fis_timer	= millis();
			fis_state	= FIS_KEEPALIVE_WAIT;
			break;
		}
 
		// Warte auf A0-Response als Keep-Alive Bestaetigung
		case FIS_KEEPALIVE_WAIT:
		{
			result = fis_wait_ka_response();
			if (result == 1)
			{
				fis_timer	= millis();
				fis_state	= FIS_RUNNING;
			}
			else if (result == 255)
			{
				// Kein Keep-Alive — Verbindung neu aufbauen
				fis_state = FIS_ERROR;
			}
			break;
		}
 
		//--------------------------------------------------------------
		// ERROR: Fehler — Neustart der Kommunikation
		//--------------------------------------------------------------
		case FIS_ERROR:
		{
			sendCounter		= 0;
			recCounter		= 0;
			fis_loop_cnt	= 0;
			fis_state		= FIS_IDLE;
			break;
		}
 
		default:
		{
			fis_state = FIS_ERROR;
			break;
		}
	}
}
//----------------------------------------------------------------------