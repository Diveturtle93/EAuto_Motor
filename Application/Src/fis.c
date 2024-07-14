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

//----------------------------------------------------------------------
uint32_t DIS_REC_ID = 0x6C1;
uint32_t DIS_SEND_ID = 0x6C0;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
uint32_t responseTime = 100;												// 100 msec
uint32_t delayStart = 0;
uint8_t sendCounter = 0, recCounter = 0;
uint8_t expectedAck;
//----------------------------------------------------------------------

// Sende Nachrichten
//----------------------------------------------------------------------
uint8_t A0_MESSAGE[] =				{0xA0, 0x0F, 0x8A, 0xFF, 0x4A, 0xFF};
uint8_t M15_SEND[] =				{0x10, 0x15, 0x02, 0x01, 0x02, 0x00, 0x00};
uint8_t M01_02_00_SEND[] =			{0x10, 0x01, 0x02, 0x00};
uint8_t M01_02_01_SEND[] =			{0x10, 0x01, 0x02, 0x01};
uint8_t M01_01_00_SEND[] =			{0x10, 0x01, 0x01, 0x00};
uint8_t M08_SEND[] =				{0x10, 0x08};
uint8_t M24_SEND[] =				{0x10, 0x24};
uint8_t M28_SEND[] =				{0x10, 0x28};
uint8_t M09_1_SEND[] =				{0x20, 0x09, 0x20, 0x00, 0x50, 0x07, 0x12,  0x4E};
uint8_t M09_2_SEND[] =				{0x20, 0x41, 0x56, 0x4C, 0x4C, 0x2D, 0x30,  0x32};
uint8_t M09_3_SEND[] =				{0x10, 0x30, 0x30, 0x00};
uint8_t M20_SEND[] =				{0x10, 0x20, 0x3B, 0xA0, 0x00};
uint8_t M39_SEND[] =				{0x10, 0x39};
uint8_t M2F_SEND[] =				{0x10, 0x2F};

uint8_t R_CLAIM[] =					{0x10, 0x52, 0x05, 0x80, 0x00, 0x1B, 0x40, 0x30};
uint8_t R_CLEAR[] =					{0x10, 0x52, 0x05, 0x02, 0x00, 0x1B, 0x40, 0x30};

uint8_t A3_MESSAGE[] =				{0xA3};
//----------------------------------------------------------------------

// Empfangs Nachrichten
//----------------------------------------------------------------------
uint8_t  M09_1_REC[] =				{0x20, 0x09, 0x20, 0x0B, 0x50, 0x00, 0x32, 0x44};
uint8_t  M09_2_REC[] =				{0x10, 0x30, 0x34, 0x00, 0x31, 0x00};
uint8_t  M05_1_REC[] =				{0x20, 0x29, 0x02, 0x39, 0x1E, 0xD0, 0x07, 0x01};
uint8_t  M05_2_REC[] =				{0x10, 0x01};

uint8_t  M00_01_REC[] =				{0x10, 0x00, 0x01};
uint8_t  M21_REC[] =				{0x10, 0x21, 0x3B, 0xA0, 0x00};
uint8_t  M53_05_REC[] =				{0x10, 0x53, 0x05};
uint8_t  M53_84_REC[] =				{0x10, 0x53, 0x84};
uint8_t  M53_85_REC[] =				{0x10, 0x53, 0x85};
uint8_t  M2E_REC[] =				{0x10, 0x2E};
uint8_t  M2F_REC[] =				{0x10, 0x2F};
uint8_t  M39_REC[] =				{0x10, 0x39};
uint8_t  M00_02_REC[] =				{0x10, 0x00, 0x02};
uint8_t  M0B_REC[] =				{0x0B, 0x01, 0x00};
//----------------------------------------------------------------------

// Status und Wartezeit
//----------------------------------------------------------------------
uint8_t fis_state = 1;
uint32_t fis_time = 0;
//----------------------------------------------------------------------

// Navi CAN-Nachrichten
//----------------------------------------------------------------------
CAN_PaketTypeDef TxNavi;
CAN_RxHeaderTypeDef RxNavi;
//----------------------------------------------------------------------

// Lese FIS Daten
//----------------------------------------------------------------------
void readFIS (uint32_t id)
{
	uint8_t len = 0;
	uint8_t recBuf[8];
	while (HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0)
	{
		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, recBuf);
		len = RxNavi.DLC;
		if (RxNavi.StdId == id)
		{
			if (len > 1)													// if not an ack or A3
			{
				recCounter++;
				/* Send ack */
				if (recBuf[0] < 0x20)										// Don't ack 2X message */
				{
					TxNavi.msg.buf[0] = (0xB0 + (recCounter % 15));
					TxNavi.msg.len = 1;
					CANwrite2(&TxNavi.msg, false);
				}
			}
		}
	}
}
//----------------------------------------------------------------------

// Sende FIS Daten
//----------------------------------------------------------------------
uint8_t sendFIS (uint8_t len, uint8_t *message)
{
	uint8_t ack = 0;
	for(int i = 0; i < len; i++)											// copy message to buffer
	{
		TxNavi.msg.buf[i] = message[i];
	}
	if ((TxNavi.msg.buf[0] == 0xA3) || (TxNavi.msg.buf[0] == 0xA0))
	{
		expectedAck = LONG_ACK;
	}
	else
	{
		TxNavi.msg.buf[0] = (TxNavi.msg.buf[0]) + (sendCounter % 16);		// set sequence count
		sendCounter++;
		if (TxNavi.msg.buf[0] >= 0x20)
		{
			expectedAck = NO_ACK;
			ack = 1;
			delayStart = millis();
			while (millis() <= (delayStart + 50))
			{
				readDIS(DIS_REC_ID);
			}
		}
		else
		{
			expectedAck = NORMAL_ACK;
		}
	}

	/* Check for waiting message */
	readDIS(DIS_REC_ID);
	/* Send the message */
	TxNavi.msg.len = len;
	while (CANwrite2(&TxNavi.msg, false) == false);

	/* Wait for Ack */
	uint8_t ackBuf[8];
	delayStart = millis();
	while (millis() <= (delayStart + responseTime) && (ack == 0))
	{
		if((HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0) && (ack == 0))	// check if data coming
		{
			HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, ackBuf);
			len = RxNavi.DLC;
			if (RxNavi.StdId == DIS_REC_ID)
			{
				switch (expectedAck)
				{
					case LONG_ACK:
						ack = 1;
						for(int i = 0; i<len; i++)
						{
							if (ackBuf[i] != A0_RESPONSE[i])
							{
								ack = 0;
							}
						}
					break;
					case NORMAL_ACK :
						if (ackBuf[0] == (0xB0 + (recCounter % 15)))
						{
							ack = 1;
						}
					break;
				}
			}
		}
	}
	return ack;
}
//----------------------------------------------------------------------

// Warten bis FIS Daten empfangen
//----------------------------------------------------------------------
void waitFIS(uint32_t id, uint8_t *message)									// wait for message
{
	uint8_t messageReceived = 0;
	delayStart = millis();
	uint8_t recBuf[8];

	while (millis() <= (delayStart + responseTime) && (messageReceived == 0))
	{
		if((HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0) && (messageReceived == 0))	// check if data coming
		{
			HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, recBuf);	// read data,  len: data length, buf: data buf
			if (RxNavi.StdId == id)
			{
				if (recBuf[0] == (message[0] + (recCounter % 15)))
				{
					messageReceived = 1;
				}

				if (messageReceived)
				{
					recCounter++;
				}

				if (recBuf[0] < 0x20)										// Don't ack 2X message */
				{
					TxNavi.msg.buf[0] = (0xB0 + (recCounter % 15));
					TxNavi.msg.len = 1;
					while (CANwrite2(&TxNavi.msg, false) == false);
				}
			}
		}
	}
}
//----------------------------------------------------------------------

// Initialisiere FIS
//----------------------------------------------------------------------
void initFIS (void)
{
	TxNavi = CAN_Nachricht(0x6C0, 8, 50, 10, false);
	TxNavi.msg.flags.extended = 0;

	sendCounter = 0;
	recCounter = 0;
}
//----------------------------------------------------------------------

// Starte Kommunikation
//----------------------------------------------------------------------
void startComms (void)
{
	initFis();
	claimScreen();
	drawFrame();
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
void initDIS(void)
{
	switch (fis_state)
	{
		case 1:
		{
		    sendDIS(DIS_SEND_ID, sizeof(A0_MESSAGE), A0_MESSAGE);			// {0xA0, 0x0F, 0x8A, 0xFF, 0x4A, 0xFF}
		    fis_state = 2;
		    fis_time = millis();
			break;
		}
		case 2:
		{
			if (millis() >= (fis_time + 5))
			{
			    sendDIS(DIS_SEND_ID, sizeof(M15_SEND), M15_SEND);			// {0x10, 0x15, 0x02, 0x01, 0x02, 0x00, 0x00}
			    fis_state = 3;
			}
			break;
		}
		case 3:
		{
		    waitDIS(DIS_REC_ID, M00_01_REC);								// {0x10, 0x00, 0x01}
		    fis_state = 4;
		    fis_time = millis();
			break;
		}
		case 4:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(M01_02_00_SEND), M01_02_00_SEND);	// {0x10, 0x01, 0x02, 0x00}
			    fis_state = 5;
			}
			break;
		}
		case 5:
		{
		    waitDIS(DIS_REC_ID, M00_01_REC);								// {0x10, 0x00, 0x01}
		    fis_state = 6;
		    fis_time = millis();
			break;
		}
		case 6:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(A3_MESSAGE), A3_MESSAGE);		// {0xA3}
				fis_state = 7;
				fis_time = millis();
			}
			break;
		}
		case 7:
		{
		    for(int i = 0; i < 3; i++)
		    {
				sendDIS(DIS_SEND_ID, sizeof(A3_MESSAGE), A3_MESSAGE);		// {0xA3}
				fis_time = millis();
				while (millis() <= (fis_time + 5))
				{
					readDIS(DIS_REC_ID);
				}
		    }
		    fis_state = 8;
		    fis_time = millis();
		    break;
		}
		case 8:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(M01_02_01_SEND), M01_02_01_SEND);	// {0x10, 0x01, 0x02, 0x01}
				fis_state = 9;
			}
			break;
		}
		case 9:
		{
		    waitDIS(DIS_REC_ID, M00_01_REC);								// {0x10, 0x00, 0x01}
		    fis_state = 10;
		    fis_time = millis();
			break;
		}
		case 10:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(M01_01_00_SEND), M01_01_00_SEND);	// {0x10, 0x01, 0x01, 0x00}
				fis_state = 11;
			    fis_time = millis();
			}
			break;
		}
		case 11:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(M08_SEND), M08_SEND);			// {0x10, 0x08}
				fis_state = 12;
			}
			break;
		}
		case 12:
		{
			waitDIS(DIS_REC_ID, M09_1_REC);									// {0x20, 0x09, 0x20, 0x0B, 0x50, 0x00, 0x32, 0x44}
			fis_state = 13;
			break;
		}
		case 13:
		{
		    waitDIS(DIS_REC_ID, M09_2_REC);									// {0x10, 0x30, 0x34, 0x00, 0x31, 0x00}
		    fis_state = 14;
		    fis_time = millis();
			break;
		}
		case 14:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(M09_1_SEND), M09_1_SEND);		// {0x20, 0x09, 0x20, 0x00, 0x50, 0x07, 0x12,  0x4E}
				sendDIS(DIS_SEND_ID, sizeof(M09_2_SEND), M09_2_SEND);		// {0x20, 0x41, 0x56, 0x4C, 0x4C, 0x2D, 0x30,  0x32}
				sendDIS(DIS_SEND_ID, sizeof(M09_3_SEND), M09_3_SEND);		// {0x10, 0x30, 0x30, 0x00}
				fis_state = 15;
			    fis_time = millis();
			}
			break;
		}
		case 15:
		{
			if (millis() >= (fis_time + 5))
			{
			    sendDIS(DIS_SEND_ID, sizeof(M24_SEND), M24_SEND);			// {0x10, 0x24}
				fis_state = 16;
			    fis_time = millis();
			}
			break;
		}
		case 16:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(A3_MESSAGE), A3_MESSAGE);		// {0xA3}
				fis_state = 17;
				fis_time = millis();
			}
			break;
		}
		case 17:
		{
		    for(int i = 0; i < 3; i++)
		    {
				sendDIS(DIS_SEND_ID, sizeof(A3_MESSAGE), A3_MESSAGE);		// {0xA3}
				fis_time = millis();
				while (millis() <= (fis_time + 5))
				{
					readDIS(DIS_REC_ID);
				}
		    }
		    fis_state = 18;
		    fis_time = millis();
		    break;
		}
		case 18:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(M28_SEND), M28_SEND);			// {0x10, 0x28}
				fis_state = 19;
			}
			break;
		}
		case 19:
		{
			waitDIS(DIS_REC_ID, M05_1_REC);									// {0x20, 0x29, 0x02, 0x39, 0x1E, 0xD0, 0x07, 0x01}
			fis_state = 20;
			break;
		}
		case 20:
		{
			waitDIS(DIS_REC_ID, M05_2_REC);									// {0x10, 0x01}
		    fis_state = 21;
		    fis_time = millis();
			break;
		}
		case 21:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(M20_SEND), M20_SEND);			// {0x10, 0x20, 0x3B, 0xA0, 0x00}
				fis_state = 22;
			}
			break;
		}
		case 22:
		{
			waitDIS(DIS_REC_ID, M21_REC);									// {0x10, 0x21, 0x3B, 0xA0, 0x00}
			fis_state = 23;
			break;
		}
		default:
		{
			break;
		}
	}
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
uint8_t claimScreen(void)
{
	switch (fis_state)
	{
		case 23:
		{
			sendDIS(DIS_SEND_ID, sizeof(R_CLAIM), R_CLAIM);					// {0x10, 0x52, 0x05, 0x80, 0x00, 0x1B, 0x40, 0x30}
			fis_state = 24;
			break;
		}
		case 24:
		{
			waitDIS(DIS_REC_ID, M53_84_REC);								// {0x10, 0x53, 0x84}
			fis_state = 25;
			break;
		}
		case 25:
		{
			waitDIS(DIS_REC_ID, M53_05_REC);								// {0x10, 0x53, 0x05}
		    fis_state = 26;
			break;
		}
		case 26:
		{
			waitDIS(DIS_REC_ID, M2E_REC);									// {0x10, 0x2E}
		    fis_state = 27;
		    fis_time = millis();
			break;
		}
		case 27:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(M2F_SEND), M2F_SEND);			// {0x10, 0x2F}
				fis_state = 28;
				fis_time = millis();
			}
			break;
		}
		case 28:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(R_CLAIM), R_CLAIM);				// {0x10, 0x52, 0x05, 0x80, 0x00, 0x1B, 0x40, 0x30}
				fis_state = 29;
			}
			break;
		}
		case 29:
		{
			waitDIS(DIS_REC_ID, M53_85_REC);								// {0x10, 0x53, 0x85}
		    fis_state = 30;
		    fis_time = millis();
			break;
		}
		case 30:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(R_CLEAR), R_CLEAR);				// {0x10, 0x52, 0x05, 0x02, 0x00, 0x1B, 0x40, 0x30}
				fis_state = 31;
				fis_time = millis();
			}
			break;
		}
		case 31:
		{
			if (millis() >= (fis_time + 5))
			{
				sendDIS(DIS_SEND_ID, sizeof(M39_SEND), M39_SEND);			// {0x10, 0x39}
				fis_state = 32;
				return 1;
			}
			break;
		}
	}

	return 0;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
void drawFrame(void)
{
//	sendDIS(DIS_SEND_ID,  sizeof(DRAW_1), DRAW_1);

	uint8_t test1[8] = {0x20, 0x57, 0x0F, 0x06, 0x01, 0x01, 0x48, 0x41};
	uint8_t test2[8] = {0x20, 0x4C, 0x4C, 0x4F, 0x65, 0x50, 0x08, 0x09};
	uint8_t test3[4] = {0x10, 0x0C, 0x09, 0x10};
	sendDIS(DIS_SEND_ID, sizeof(test1), test1);
	sendDIS(DIS_SEND_ID, sizeof(test2), test2);
	sendDIS(DIS_SEND_ID, sizeof(test3), test3);

    sendDIS(DIS_SEND_ID, sizeof(A3_MESSAGE), A3_MESSAGE);					// {0xA3}
    sendDIS(DIS_SEND_ID, sizeof(M39_SEND), M39_SEND);						// {0x10, 0x39}
    sendDIS(DIS_SEND_ID, sizeof(A3_MESSAGE), A3_MESSAGE);					// {0xA3}
//    waitDIS(DIS_REC_ID, M0B_REC);											// {0x0B, 0x01, 0x00}
}
//----------------------------------------------------------------------
