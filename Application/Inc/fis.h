//----------------------------------------------------------------------
// Titel	:	fis.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jun 25, 2024
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Sicherheitssymbol
//----------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_FIS_H_
#define INC_FIS_H_
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Define Debug Symbols
//----------------------------------------------------------------------
#ifdef DEBUG
#define DEBUG_FIS
#endif
//----------------------------------------------------------------------

// Version definieren
//----------------------------------------------------------------------
#define FIS_MAJOR							    0
#define FIS_MINOR							    0
#define FIS_PATCH							    0
#define FIS_DEV								    0
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
#define 		LONG_ACK						1
#define			NORMAL_ACK						2
#define 		NO_ACK							3
//----------------------------------------------------------------------

// Status-Rueckgabewerte fuer FIS_GetStatus()
//----------------------------------------------------------------------
typedef enum
{
	FIS_STATUS_IDLE		= 0,						// Noch nicht gestartet
	FIS_STATUS_INIT		= 1,						// Initialisierung laeuft
	FIS_STATUS_RUNNING	= 2,						// Betrieb (Keep-Alive aktiv)
	FIS_STATUS_ERROR	= 3							// Fehler aufgetreten
} FIS_Status_t;
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
void			FIS_Start		(void);										// Kommunikation starten / neu starten
void			FIS_Task		(void);										// Zyklisch im Hauptloop aufrufen
FIS_Status_t	FIS_GetStatus	(void);										// Aktuellen Status abfragen

//----------------------------------------------------------------------

#endif /* INC_FIS_H_ */
//----------------------------------------------------------------------
