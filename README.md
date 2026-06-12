# EAuto Motor – Motorsteuergerät
 
Firmware für ein Motorsteuergerät zum Antrieb eines Elektrofahrzeugs auf Basis eines **STM32F767ZI**.
Das Steuergerät dient als Ersatz für das originale Motorsteuergerät eines Dieselfahrzeugs, dessen Motor
durch einen **EMRAX 228**-Elektromotor ersetzt wurde. Die Ansteuerung des Motors erfolgt über den
Motorcontroller **Bamocar D3** via CAN-Bus.
 
## Beschreibung
 
Das Motorsteuergerät übernimmt die zentrale Steuerung und Überwachung aller fahrzeugrelevanten Komponenten.
Es liest Fahrereingaben (Gaspedal, Bremse, Kupplungsschalter), wertet Sensordaten über ADC aus, kommuniziert
mit dem Bamocar-Motorcontroller, dem Batteriemanagement, dem ABS und weiteren Steuergeräten über den
Antriebs-CAN-Bus und steuert Aktoren wie Kühlpumpen, Lüfter und Klima.
 
Das Projekt ist in zwei Bereiche aufgeteilt:
 
- **Core/** – Grundlegende Systeminitialisierung, HAL-Treiber und CubeMX-generierter Code
- **Application/** – Fahrzeugspezifische Anwendungslogik: Zustandsmaschine, Pedalauswertung, CAN-Kommunikation,
Fehlerbehandlung
## Hardware
 
| Merkmal              | Beschreibung                                                        |
|----------------------|---------------------------------------------------------------------|
| Mikrocontroller      | STM32F767ZIT (Cortex-M7, 216 MHz, 2 MB Flash, 512 kB RAM)          |
| Elektromotor         | EMRAX 228                                                           |
| Motorcontroller      | Bamocar D3                                                          |
| Antriebs-CAN         | CAN3 – 500 kBit/s, sicherheitsrelevante Daten                       |
| Komfort-CAN          | CAN1/CAN2 – nicht sicherheitsrelevant, aktuell nicht ausgewertet    |
| ADC                  | 10 Kanäle, 12-Bit-Auflösung, APB2-Vorteiler 4 → 27 MHz ADC-Takt   |
| Eingänge             | 36 digitale Eingänge (3,3 V Logikpegel, kurzschlussfest, 0–24 V)   |
| Ausgänge             | 37 digitale Ausgänge (12 V / 24 V, zwei Stromklassen)              |
 
## Projektstruktur
 
| Ordner / Datei              | Beschreibung                                                        |
|-----------------------------|---------------------------------------------------------------------|
| `Core/`                     | CubeMX-generierter Code, HAL-Treiber, Systeminitialisierung         |
| `Application/`              | Fahrzeuglogik: Zustandsmaschine, ADC, CAN, Fehlerbehandlung         |
| `Drivers/`                  | STM32 HAL und CMSIS-Treiber                                         |
| `ADC.md`                    | Dokumentation aller 10 ADC-Kanäle mit Pinbelegung und Messwerten    |
| `CAN.md`                    | CAN-Bus-Dokumentation: Busse, Priorisierung, CAN-ID-Tabelle         |
| `INPUTS.md`                 | Dokumentation aller 36 digitalen Eingänge mit Pinbelegung           |
| `OUTPUTS.md`                | Dokumentation aller 37 digitalen Ausgänge mit Pinbelegung           |
| `REVISION.md`               | Revisionshistorie des Projekts                                      |
| `Motorsteuergeraet.ioc`     | STM32CubeMX-Projektdatei                                            |
| `STM32F767ZITX_FLASH.ld`    | Linker-Skript für Flash-Betrieb                                     |
| `STM32F767ZITX_RAM.ld`      | Linker-Skript für RAM-Betrieb (Debug)                               |
 
## CAN-Bus-Architektur
 
Am STM32F767 stehen drei CAN-Interfaces zur Verfügung, von denen zwei eine gemeinsame Registerbank teilen.
Die Buszuweisung erfolgt nach Sicherheitsrelevanz:
 
| Bus   | Interface | Baudrate     | Zweck                                                         |
|-------|-----------|--------------|---------------------------------------------------------------|
| CAN3  | CAN3      | 500 kBit/s   | Antriebs-CAN: Motorcontroller, BMS, ABS, DCDC, Ladegerät      |
| CAN1  | CAN1/CAN2 | –            | Komfort-CAN: Infotainment (aktuell nicht ausgewertet)         |
| CAN2  | CAN1/CAN2 | –            | Infotainment-CAN (aktuell nicht ausgewertet)                  |
 
CAN3 hat eine eigene Registerbank und erhält daher die höchste Priorisierung. Alle sicherheitsrelevanten
Daten laufen hier zusammen und werden zentral im Motorsteuergerät verarbeitet.
 
### CAN-IDs (Antriebs-CAN, CAN3)
 
| CAN-ID | Sender             | Empfänger          | Timing [ms] | DLC   |
|--------|--------------------|--------------------|-------------|-------|
| 0x0C2  | Lenkwinkelsensor   | –                  | 10          | 8     |
| 0x181  | Bamocar            | Motorsteuergerät   | 100         | 3–6   |
| 0x1A0  | Bremse             | –                  | 7           | 8     |
| 0x201  | Motorsteuergerät   | Bamocar            | 100         | 3–6   |
| 0x280  | Motorsteuergerät   | –                  | 20          | 8     |
| 0x288  | Motorsteuergerät   | –                  | 20          | 8     |
| 0x320  | Kombiinstrument    | –                  | 20          | 8     |
| 0x380  | Motorsteuergerät   | –                  | 20          | 8     |
| 0x388  | Motorsteuergerät   | –                  | 20          | 3     |
| 0x411  | Batteriemanagement | Stromsensor        | auf Anfrage | 8     |
| 0x420  | Kombiinstrument    | –                  | 200         | 8     |
| 0x480  | Motorsteuergerät   | –                  | 20          | 8     |
| 0x488  | Motorsteuergerät   | –                  | 20          | 8     |
| 0x4A0  | Bremse             | –                  | 14          | 8     |
| 0x4A8  | Bremse             | –                  | 20          | 8     |
| 0x511  | Stromsensor        | Batteriemanagement | auf Anfrage | 8     |
| 0x520  | Kombiinstrument    | –                  | 200         | 8     |
| 0x521  | Stromsensor        | Batteriemanagement | 100         | 8     |
| 0x580  | Motorsteuergerät   | –                  | 10          | 8     |
| 0x5A0  | Bremse             | –                  | 14          | 8     |
 
Eine vollständige Beschreibung der CAN-Kommunikation findet sich in [CAN.md](CAN.md).
 
## ADC-Kanäle
 
Der AD-Wandler läuft mit 27 MHz (APB2 108 MHz, Vorteiler 4) und gibt alle Ergebnisse mit 12-Bit-Auflösung aus.
Signale sind nach Sicherheitsrelevanz priorisiert (1 = höchste Priorität):
 
| Kanal      | Pin               | Funktion             | Timing  | Priorität |
|------------|-------------------|----------------------|---------|-----------|
| Channel 14 | PC4               | Bremsdruck           | 100 ms  | 1         |
| Channel 6  | PA6               | Gaspedal             | 100 ms  | 2         |
| Channel 4  | PA4               | Kühlwasser           | 5000 ms | 3         |
| Channel 5  | PA5               | Klima-Flap           | 1000 ms | 4         |
| Channel 15 | PC5               | Bremsdrucktemperatur | 5000 ms | 5         |
| Channel 3  | PA3               | KL15                 | 5000 ms | 6         |
| Channel 7  | PA7               | PCB Temperatur       | 5000 ms | 7         |
| Channel 18 | Temperatursensor  | STM32 Temperatur     | 1000 ms | 8         |
| Channel 8  | PB0               | Return               | 1000 ms | 9         |
| Channel 9  | PB1               | Info                 | 1000 ms | 10        |
 
Eine vollständige Beschreibung inkl. Messwerten findet sich in [ADC.md](ADC.md).
 
## Digitale Eingänge
 
36 digitale Eingänge, kurzschlussfest, ausgelegt für 0–12 V (sicher bis 24 V), intern auf 3,3 V Logikpegel
gewandelt. Die Eingänge sind in System- (sicherheitsrelevant) und Komforteingänge unterteilt.
Sicherheitsrelevante Eingänge werden häufiger abgefragt und zusätzlich über CAN übertragen.
 
Ausgewählte System-Eingänge:
 
| Funktionsgruppe  | Pin  | Funktion     |
|------------------|------|--------------|
| Shutdown Circuit | PA0  | Crash        |
| Fahrzeug         | PD8  | KL15         |
| Fahrzeug         | PB15 | Anlasser     |
| Pedale           | PE8  | Kickdown     |
| Pedale           | PE9  | Leerlauf     |
| Pedale           | PE10 | Kupplung NO  |
| Shutdown Circuit | PE14 | SDC0 Sense   |
 
Eine vollständige Pinbelegung findet sich in [INPUTS.md](INPUTS.md).
 
## Digitale Ausgänge
 
37 digitale Ausgänge in zwei Stromklassen, ausgelegt für 12 V / 24 V Fahrzeugspannung.
Sicherheitsrelevante Ausgänge werden häufiger überwacht und dürfen im Notbetrieb nicht ausfallen.
 
Ausgewählte System-Ausgänge:
 
| Funktionsgruppe  | Pin  | Funktion         |
|------------------|------|------------------|
| Shutdown Circuit | PE15 | Motorsteuergerät |
| Fahrzeug         | PB4  | Heizung 2        |
| Fahrzeug         | PB13 | Klima Out        |
| DCDC             | PF15 | Enable           |
| Fahrzeug         | PG11 | Pumpe Bremse     |
| Fahrzeug         | PG13 | Pumpe Kühlung    |
| Fahrzeug         | PG14 | Lüfter 2         |
| Fahrzeug         | PG15 | Lüfter 1         |
 
Eine vollständige Pinbelegung findet sich in [OUTPUTS.md](OUTPUTS.md).
 
## Voraussetzungen
 
- STM32CubeIDE
- STM32CubeMX (optional, zum Öffnen der `.ioc`-Datei)
- [EAuto_Bootloader](https://github.com/Diveturtle93/EAuto_Bootloader) – zuvor auf den Mikrocontroller geflasht

## Abhängigkeiten
 
- `main.h` – STM32 HAL
- [`basicuart.h`](https://github.com/Diveturtle93/STM32_Basicuart) – UART-Sende- und Empfangsfunktionen
- [STM32_Canbus](https://github.com/Diveturtle93/STM32_Canbus) – CAN-Bus-Kommunikation
- [STM32_Statemaschine](https://github.com/Diveturtle93/STM32_Statemaschine) – Zustandsmaschine
- [STM32_Hardfault](https://github.com/Diveturtle93/STM32_Hardfault) – Erweiterter HardFault-Handler
- [STM32_Resetreason](https://github.com/Diveturtle93/STM32_Resetreason) – Reset-Ursachen-Analyse
- [STM32_Systeminfo](https://github.com/Diveturtle93/STM32_Systeminfo) – Systeminformationen beim Start

## Lizenz
 
Dieses Projekt steht unter der [GPL-3.0 Lizenz](LICENSE).
