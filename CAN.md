# CAN Bus – EAuto Motor
 
Für die Programmierung am Mikrocontroller und zur Kommunikation mit dem Fahrzeug
stehen auf der Platine drei CAN-Busse zur Verfügung. Diese laufen auf unterschiedlichen
Baudraten und sind für verschiedene Einsatzzwecke vorgesehen.
 
---
 
Am Mikrocontroller sind nur zwei Registerbänke für die CAN-Interfaces vorhanden. Da
CAN1 und CAN2 am Mikrocontroller die Registerbank teilen, werden diese für die niedriger
priorisierten CAN-Busse genutzt. Im Fahrzeug sind das der Komfort- und Infotainment-CAN.
 
Der Antriebs-CAN erhält eine höhere Priorisierung und bekommt deshalb den CAN-Bus,
welcher eine eigene Registerbank hat (CAN3). Dieser ist für die Kommunikation aller
sicherheitsrelevanten Daten zuständig. Hier werden Informationen vom Motorcontroller,
Batteriemanagement, ABS, Lenkwinkelsensor, Ladegerät, DCDC-Wandler und Motorsteuergerät
übertragen. Alle Informationen laufen im Motorsteuergerät zusammen und werden dort
verarbeitet.
 
Des Weiteren werden die Informationen auch im Kombiinstrument genutzt und angezeigt.
Dieses zeigt die Drehzahl, die Geschwindigkeit, den Tankfüllstand / Akkustand und die
Motortemperatur an.
 
---
 
Auf dem Komfort-CAN sind weitere Informationen vom Fahrzeug. Diese sind zum jetzigen
Zeitpunkt nicht relevant und werden derzeit in der Programmierung nicht berücksichtigt.
 
---
 
## Liste aller CAN-IDs
 
Die nachfolgenden CAN-IDs sind auf dem Antriebs-CAN aktuell messbar.
 
| CAN-Bus | CAN-ID | Sender             | Empfänger        | Timing [ms] | DLC   |
|:--------|:------:|:-------------------|:-----------------|:-----------:|:-----:|
| CAN3    | 0x0C2  | Lenkwinkelsensor   | …                | 10          | 8     |
| CAN3    | 0x181  | Bamocar            | Motorsteuergerät | 100         | 3 – 6 |
| CAN3    | 0x1A0  | Bremse             | …                | 7           | 8     |
| CAN3    | 0x201  | Motorsteuergerät   | Bamocar          | 100         | 3 – 6 |
| CAN3    | 0x280  | Motorsteuergerät   | …                | 20          | 8     |
| CAN3    | 0x288  | Motorsteuergerät   | …                | 20          | 8     |
| CAN3    | 0x2A0  | Bremse             | …                | …           | …     |
| CAN3    | 0x320  | Kombiinstrument    | …                | 20          | 8     |
| CAN3    | 0x380  | Motorsteuergerät   | …                | 20          | 8     |
| CAN3    | 0x388  | Motorsteuergerät   | …                | 20          | 3     |
| CAN3    | 0x3D0  | …                  | …                | 20          | 2     |
| CAN3    | 0x411  | Batteriemanagement | Stromsensor      | xxx         | 8     |
| CAN3    | 0x420  | Kombiinstrument    | …                | 200         | 8     |
| CAN3    | 0x480  | Motorsteuergerät   | …                | 20          | 8     |
| CAN3    | 0x488  | Motorsteuergerät   | …                | 20          | 8     |
| CAN3    | 0x4A0  | Bremse             | …                | 14          | 8     |
| CAN3    | 0x4A8  | Bremse             | …                | 20          | 8     |
| CAN3    | 0x511  | Stromsensor        | Batteriemanagement | xxx       | 8     |
| CAN3    | 0x520  | Kombiinstrument    | …                | 200         | 8     |
| CAN3    | 0x521  | Stromsensor        | Batteriemanagement | 100       | 8     |
| CAN3    | 0x580  | Motorsteuergerät   | …                | 10          | 8     |
| CAN3    | 0x5A0  | Bremse             | …                | 14          | 8     |
| CAN3    | 0x5D0  | …                  | …                | 100         | 6     |
| CAN3    | 0x5DE  | …                  | …                | 200         | 5     |
| CAN3    | 0x5E0  | …                  | …                | 110         | 8     |
 
**…** – Aktuell keine Erkenntnis über den Wert vorhanden.
**xxx** – Timing nicht vorhanden. CAN-ID auf dem Bus nur messbar nach Aufforderung durch manuelles Senden.
