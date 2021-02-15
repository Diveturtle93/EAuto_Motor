# **ADC Zuweisung**
====================

Es sind zehn Kanäle für die ADC Auswertung vorgesehen.

## Liste der AD-Kanäle
=======================

1. Channel 3		PA3			KL15
2. Channel 4		PA4			Kühlwasser
3. Channel 5		PA5			Klimaflap
4. Channel 6		PA6			Gaspedal
5. Channel 7		PA7			PCB
6. Channel 8		PB0			Return
7. Channel 9		PB1			Info
8. Channel 14		PC4			Bremsdruck
9. Channel 15		PC5			Bremsdrucktemperatur
10. Channel Temperatur Sensor	STM32 Temperatur

## Zeitliches Timing der einzelnen Konversationen
==================================================

Jeder Kanal hat ein anderes Timing bei dem er aufgerufen werden muss.

| Kanal | Timing |
|:----- | ------:|
| Channel 3 | 5000ms |
| Channel 4 | 5000ms |
| Channel 5 | 1000ms |
| Channel 6 | 100ms |
| Channel 7 | 5000ms |
| Channel 8 | 1000ms |
| Channel 9 | 1000ms |
| Channel 14 | 100ms |
| Channel 15 | 5000ms |
| Channel Temperatur Sensor | 1000ms |

## Priorisierung der AD-Kanäle
===============================

Die Priorisierung ist von eins bis zehn (Wichtig bis unwichtig) aufgelistet.

| Kanal | Prio |
|:----- | ----:|
| Channel 3 | 6 |
| Channel 4 | 3 |
| Channel 5 | 4 |
| Channel 6 | 2 |
| Channel 7 | 6 |
| Channel 8 | 9 |
| Channel 9 | 10 |
| Channel 14 | 1 |
| Channel 15 | 5 |
| Channel Temperatur Sensor | 8 |