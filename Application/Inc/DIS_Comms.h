#ifndef _DIS_COMMS_H_
#define _DIS_COMMS_H_
// TODO: Formatierung


uint8_t sendDIS(unsigned long id, uint8_t len, uint8_t *message); 	// send message and wait for ack
void waitDIS(unsigned long id, uint8_t *message); 				// wait for message and send ack
void readDIS(unsigned long id);
uint8_t disCommsOk(void);

#endif
