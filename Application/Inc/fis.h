//----------------------------------------------------------------------
// Titel	:	fis.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jun 25, 2024
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_FIS_H_
#define INC_FIS_H_
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
#define 		LONG_ACK						1
#define			NORMAL_ACK						2
#define 		NO_ACK							3
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void readFIS (uint32_t id);
uint8_t sendFIS (uint8_t len, uint8_t *message);
void waitFIS(uint32_t id, uint8_t *message);
void initFIS (void);
void startComms (void);

void initFIS(void);
uint8_t claimScreen(void);
void drawFrame(void);
//----------------------------------------------------------------------

#endif /* INC_FIS_H_ */
//----------------------------------------------------------------------
