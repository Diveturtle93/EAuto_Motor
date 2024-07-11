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

CAN_message_t RxNavi, TxNavi;
uint8_t recCounter = 0, sendCounter = 0;

//----------------------------------------------------------------------
void readFIS (uint32_t id)
{
	uint8_t len = 0;

	if (CAN_available() >= 1)
	{
		CANread(&RxNavi);

		len = RxNavi.len;

		if (RxNavi.id == id)
		{
			if (len > 1)
			{
				recCounter++;

				if (RxNavi.buf[0] < 0x20)
				{
					TxNavi.buf[0] = (0xB0 + recCounter % 15);
					TxNavi.len = 1;

					CANwrite(&TxNavi, false);
				}
			}
		}
	}
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
uint8_t sendFIS (uint32_t id, uint8_t len, uint8_t *message)
{
	if (millis() >= time + wait)
	{
		uint8_t sendbuf[8] = {0};
		uint8_t ack = 0;

		for (uint8_t i = 0; i < len; i++)
		{
			sendbuf[i] = message[i];
		}

		if ((sendbuf[0] == 0xA3) || (sendbuf[0] == 0xA0))
		{
			expectedAck = LONG_ACK;
		}
		else
		{
			sendbuf[0] = (sendbuf[0] + (sendCounter & 16));
			sendCounter++;

			if (sendbuf[0] >= 0x20)
			{
				expectedAck = NO_ACK;
				ack = 1;
			}
			else
			{
				expectedAck = NORMAL_ACK;
			}
		}

		readFIS(DIS_REC_ID);

		TxNavi.len = len;

		HAL_CAN_AddTxMessage(&hcan2, &TxNavi, sendbuf, (uint32_t)CAN_TX_MAILBOX0);
		while(HAL_CAN_IsTxMessagePending(&hcan2, CAN_TX_MAILBOX0) == 1);

		uint8_t ackbuf[8];
		delayStart = millis();

		while(responseTime >= (millis() - delayStart) && (ack == 0))
		{
			if((HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0) && (ack == 0))
			{
				HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, ackbuf);
				len = RxNavi.len;

				if(RxNavi.id == DIS_REC_ID)
				{
					switch (expectedAck)
					{
						case LONG_ACK:
						{
							ack = 1;

							for(uint8_t i = 0; i < len; i++)
							{
								if(ackbuf[i] != A0_Response[i])
								{
									ack = 0;
								}
							}

							break;
						}
						case NORMAL_ACK:
						{
							if(ackbuf[0] == (0xB0 + (recCounter % 15)))
							{
								ack = 1;
							}
						}
					}
				}
			}
		}

		return ack;
	}
}
//----------------------------------------------------------------------

// Initialisiere FIS
//----------------------------------------------------------------------
void initFIS (void)
{
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
