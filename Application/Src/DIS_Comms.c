#include "main.h"
#include "Motorsteuergeraet.h"
// TODO: Formatierung

extern unsigned long 	DIS_REC_ID;
extern unsigned long 	DIS_SEND_ID;

unsigned long 	responseTime = 200; 	// 200 msec
unsigned long 	delayStart = 0; 		// the time the delay started
uint8_t 		sendCounter = 0;
uint8_t 		recCounter = 0;
#define 		LONG_ACK	1
#define			NORMAL_ACK	2
#define 		NO_ACK		3
uint8_t 		expectedAck;
uint8_t 		KA_MESSAGE[] =         {0xA3};
uint8_t 		KA_RESPONSE[] =        {0xA1, 0x0F, 0x8A, 0xFF, 0x4A, 0xFF};
uint8_t 		A0_RESPONSE[] =        {0xA1, 0x0F, 0x8A, 0xFF, 0x4A, 0xFF};

// CAN_TxHeaderTypeDef TxNavi = {0x6C0, 0, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE};
CAN_PaketTypeDef TxNavi;
CAN_RxHeaderTypeDef RxNavi;


void readDIS(unsigned long id) 					// read waiting message(s) and send ack
{
	uint8_t len = 0;
	uint8_t recBuf[8];
	while (HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0)
	{
		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, recBuf);    			// read data,  len: data length, buf: data buf
		len = RxNavi.DLC;
		if (RxNavi.StdId == id)
		{
			if (len > 1)							// if not an ack or A3
			{
				recCounter++;
				/* Send ack */
				if (recBuf[0] < 0x20)  					// Don't ack 2X message */
				{
					TxNavi.msg.buf[0] = (0xB0 + (recCounter % 15));
					TxNavi.msg.len = 1;
//					while (CANwrite2(&TxNavi.msg, false) == false);
					CANwrite2(&TxNavi.msg, false);
				}
			}
		}
	}
}

uint8_t sendDIS(unsigned long id, uint8_t len, uint8_t *message)
{
	uint8_t ack = 0;
	for(int i = 0; i < len; i++)   						// copy message to buffer
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
			HAL_Delay(50);  									// don't send multi-line messages too fast
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
		if((HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0) && (ack == 0))        // check if data coming
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

void waitDIS(unsigned long id, uint8_t *message) 			// wait for message
{
	uint8_t messageReceived = 0;
	delayStart = millis();
	uint8_t recBuf[8];

	while (millis() <= (delayStart + responseTime) && (messageReceived == 0))
	{
		if((HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0) && (messageReceived == 0))        // check if data coming
		{
			HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, recBuf);    				// read data,  len: data length, buf: data buf
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

				if (recBuf[0] < 0x20)  					// Don't ack 2X message */
				{
					TxNavi.msg.buf[0] = (0xB0 + (recCounter % 15));
					TxNavi.msg.len = 1;
					while (CANwrite2(&TxNavi.msg, false) == false);
				}
			}
		}
	}
}

void disCommsOk(void)
{
	uint8_t len = 0;
	uint8_t ack = 0;
	TxNavi = CAN_Nachricht(0x6C0, 8, 50, 10, false);
	TxNavi.msg.flags.extended = 0;

	sendCounter = 0;
	recCounter = 0;

//	/* check for waiting message */
//	readDIS(DIS_REC_ID);
//	/* send keepalives */
//
//	TxNavi.msg.len = sizeof(KA_MESSAGE);
//	CANwrite2(&TxNavi.msg, false);
//
//	/* check for keep alive response */
//	uint8_t ackBuf[8];
//	delayStart = millis();
//	while (millis() <= (delayStart + responseTime) && (ack == 0))
//	{
//		if((HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0) && (ack == 0))        // check if data coming
//		{
//			HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, ackBuf);    			// read data,  len: data length, buf: data buf
//			len = RxNavi.DLC;
//			if (RxNavi.StdId == DIS_REC_ID)
//			{
//				ack = 1;
//				for(int i = 0; i<len; i++)
//				{
//					if (ackBuf[i] != KA_RESPONSE[i])
//					{
//						ack = 0;
//					}
//				}
//			}
//		}
//	}
//	return ack;
}
