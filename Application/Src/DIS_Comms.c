#include "main.h"
#include "millis.h"
#include "can.h"
// TODO: Formatierung

extern 	unsigned long 	DIS_REC_ID;
extern 	unsigned long 	DIS_SEND_ID;
extern	uint8_t	reset;
extern	uint8_t	paused;

unsigned long 	responseTime = 200; 	// 200 msec
unsigned long 	delayStart = 0; 		// the time the delay started
uint8_t 		sendCounter = 0;
uint8_t 		recCounter = 0;
uint8_t			resetButtCount = 0;
#define 		LONG_ACK	1
#define			NORMAL_ACK	2
#define 		NO_ACK		3
uint8_t 		expectedAck;
uint8_t 		KA_MESSAGE[] =         {0xA3};
uint8_t 		KA_RESPONSE[] =        {0xA1, 0x0F, 0x8A, 0xFF, 0x4A, 0xFF};
uint8_t 		A0_RESPONSE[] =        {0xA1, 0x0F, 0x8A, 0xFF, 0x4A, 0xFF};
uint8_t 		RESET_BUTTON[] =       {0x00, 0x00, 0xC0, 0x00, 0x02};
uint8_t 		NO_BUTTON[] =   	   {0x00, 0x00, 0x80, 0x00, 0x02};

CAN_TxHeaderTypeDef TxNavi = {0x6C0, 0, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE};
CAN_RxHeaderTypeDef RxNavi;


void readDIS(unsigned long id) 					// read waiting message(s) and send ack
{
	uint8_t len = 0;
	uint8_t recBuf[8];
	uint8_t ackBuf[8];
	while (HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0)
	{
		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, recBuf);    			// read data,  len: data length, buf: data buf
		len = RxNavi.DLC;
		if (RxNavi.StdId == id)
		{
//			Serial.print("status message received");
//			Serial.print("\t");
//			Serial.print(id, HEX);
//			Serial.print("\t");
//			for(int i = 0; i<len; i++)  {  			// print the data
//				Serial.print(recBuf[i], HEX);
//				Serial.print("\t");
//			}
//			Serial.println();
			if (len > 1)							// if not an ack or A3
			{
				recCounter++;
				/* Send ack */
				if (recBuf[0] < 0x20)  					// Don't ack 2X message */
				{
					ackBuf[0] = (0xB0 + recCounter % 15);
					TxNavi.DLC = 1;
					HAL_CAN_AddTxMessage(&hcan2, &TxNavi, ackBuf, (uint32_t *)CAN_TX_MAILBOX0);
					while(HAL_CAN_IsTxMessagePending(&hcan2, CAN_TX_MAILBOX0) == 1)
					{

					}
//					Serial.print(DIS_SEND_ID, HEX);
//					Serial.print("\t");
//					Serial.print(ackBuf[0], HEX);
//					Serial.println();
				}
			}
		}
	}
}

uint8_t sendDIS(unsigned long id, uint8_t len, uint8_t *message)
{
	uint8_t sendBuf[8]={0};
	uint8_t ack = 0;
	for(int i = 0; i < len; i++)   						// copy message to buffer
	{
		sendBuf[i] = message[i];
	}
	if ((sendBuf[0] == 0xA3) || (sendBuf[0] == 0xA0))
	{
		expectedAck = LONG_ACK;
	}
	else
	{
		sendBuf[0] = (sendBuf[0]) + (sendCounter % 16);		// set sequence count
		sendCounter++;
		if (sendBuf[0] >= 0x20)
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
	TxNavi.DLC = len;
	HAL_CAN_AddTxMessage(&hcan2, &TxNavi, sendBuf, (uint32_t *)CAN_TX_MAILBOX0);
	while(HAL_CAN_IsTxMessagePending(&hcan2, CAN_TX_MAILBOX0) == 1)
	{

	}
//	Serial.print(id, HEX);
//	Serial.print("\t");
//	for(int i = 0; i < len; i++)    // print the data
//		{
//		Serial.print(sendBuf[i], HEX);
//		Serial.print("\t");
//	}
//	Serial.println();

/* Wait for Ack */
	uint8_t ackBuf[8];
	delayStart = millis();
	while (responseTime >=(millis() - delayStart) && (ack == 0))
	{
		if((HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0) && (ack == 0))        // check if data coming
		{
			HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, ackBuf);
			len = RxNavi.DLC;
			if (RxNavi.StdId == DIS_REC_ID)
			{
//				Serial.print(canId, HEX);
//				Serial.print("\t");
//				for(int i = 0; i<len; i++)  {  // print the data
//					Serial.print(ackBuf[i], HEX);
//					Serial.print("\t");
//				}
//				Serial.println();
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
	uint8_t ackBuf[8];

	while (responseTime >=(millis() - delayStart) && (messageReceived == 0))
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
//				Serial.print(id, HEX);
//				Serial.print("\t");
//				for(int i = 0; i<len; i++)  {  			// print the data
//					Serial.print(recBuf[i], HEX);
//					Serial.print("\t");
//				}
//				Serial.println();
				if (messageReceived)
				{
					recCounter++;
				}
				if (recBuf[0] < 0x20)  					// Don't ack 2X message */
				{
					ackBuf[0] = (0xB0 + recCounter % 15);
//					CAN.sendMsgBuf(DIS_SEND_ID, 0, 1, ackBuf);
					TxNavi.DLC = 1;
					HAL_CAN_AddTxMessage(&hcan2, &TxNavi, ackBuf, (uint32_t *)CAN_TX_MAILBOX0);
					while(HAL_CAN_IsTxMessagePending(&hcan2, CAN_TX_MAILBOX0) == 1)
					{

					}
//					Serial.print(DIS_SEND_ID, HEX);
//					Serial.print("\t");
//					Serial.print(ackBuf[0], HEX);
//					Serial.println();
				}
			}
		}
	}
}

uint8_t disCommsOk(void)
{
	uint8_t len = 0;
	uint8_t ack = 0;

	/* check for waiting message */
	readDIS(DIS_REC_ID);
	/* send keepalives */
//	CAN.sendMsgBuf(DIS_SEND_ID, 0, sizeof(KA_MESSAGE), KA_MESSAGE);
	TxNavi.DLC = sizeof(KA_MESSAGE);
	HAL_CAN_AddTxMessage(&hcan2, &TxNavi, KA_MESSAGE, (uint32_t *)CAN_TX_MAILBOX0);
	while(HAL_CAN_IsTxMessagePending(&hcan2, CAN_TX_MAILBOX0) == 1)
	{

	}
//	Serial.print(DIS_SEND_ID, HEX);
//	Serial.print("\t");
//	for(int i = 0; i < sizeof(KA_MESSAGE); i++)  {  // print the data
//		Serial.print(KA_MESSAGE[i], HEX);
//		Serial.print("\t");
//	}
//	Serial.println();

	/* check for keep alive response */
	uint8_t ackBuf[8];
	delayStart = millis();
	while (responseTime >=(millis() - delayStart) && (ack == 0))
	{
		if((HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) != 0) && (ack == 0))        // check if data coming
		{
			HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxNavi, ackBuf);    			// read data,  len: data length, buf: data buf
			len = RxNavi.DLC;
			if (RxNavi.StdId == DIS_REC_ID)
			{
//				Serial.print(canId, HEX);
//				Serial.print("\t");
//				for(int i = 0; i<len; i++)  {  // print the data
//					Serial.print(ackBuf[i], HEX);
//					Serial.print("\t");
//				}
//				Serial.println();
				ack = 1;
				for(int i = 0; i<len; i++)
				{
					if (ackBuf[i] != KA_RESPONSE[i])
					{
						ack = 0;
					}	
				}
			}
		}
	}
	return ack;
}
