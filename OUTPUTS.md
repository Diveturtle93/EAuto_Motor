# **Output Zuweisung**

Es stehen für die Programmierung unterschiedlichste Ausgänge am Mikrocontroller zur
Verfügung. Diese sind alle über eine entsprechende Logiklevel Schaltung nach aussen
geführt.

---

Es stehen für die Ansteuerung zwei unterschiedlicher Schaltungen zur Verfügung.
Unterschieden werden die beiden Ausgangsschaltungen nur in ihrer Stromtragfähigkeit.
Die beiden Ausgangsstuffen haben unterschiedliche Leistungsmosfets verbaut, welche
somit eine unterschiedliche Stromtragfähigkeit besitzen. Somit kann man
unterschiedlichste Periferie ansteueren und schalten.

---

## Liste der Ausgänge
Nachfolgend ist eine Auflistung aller Ausgangspins vom Mikrocontroller.

| Funktionsgruppe | Pin | Funktion | Relevanz | Getestet |
|:--------------- |:---:|:-------- |:-------- | --------:|
| Fahrzeug | PA12 | Crash | Komfort | No |
| STM32 | PB2 | LED Red | Komfort | Ja |
| Fahrzeug | PB4 | Heizung 2 | System | No |
| STM32 | PB7 | LED Green | Komfort | Ja |
| Fahrzeug | PB11 | F54 | System | No |
| Fahrzeug | PB12 | F18 | System | No |
| Fahrzeug | PB13 | Klima Out | System | No |
| STM32 | PB14 | LED Blue | Komfort | Ja |
| ASR | PC3 | WS2812 LED | Komfort | Ja |
| Fahrzeug | PD3 | Ladeleuchte | Komfort | No |
| Fahrzeug | PD7 | Öltemp | Komfort | No |
| Fahrzeug | PD9 | Bremslicht | Komfort | No |
| Fahrzeug | PD11 | Rücklicht | Komfort | No |
| Fahrzeug | PD13 | Klima PWM Out | System | No |
| Fahrzeug | PD14 | Anhänger | Komfort | No |
| Fahrzeug | PD15 | Reserve | Komfort | No |
| Fahrzeug | PE0 | Heizung 1 | System | No |
| Fahrzeug | PE1 | Digital 2 | Komfort | No |
| Fahrzeug | PE2 | Digital 1 | Komfort | No |
| Fahrzeug | PE7 | Glühkerzenrelais | Komfort | No |
| Shutdown Circuit | PE15 | Motorsteuergerät | System | No |
| Fahrzeug | PF2 | Öldruck | Komfort | No |
| Board Computer | PF3 | Down Out | Komfort | No |
| Board Computer | PF4 | Up Out | Komfort | No |
| Board Computer | PF5 | Reset Out | Komfort | No |
| Bamocar | PF12 | Bamo Out 1 | Komfort | No |
| Bamocar | PF13 | Bamo Out 2 | Komfort | No |
| Fahrzeug | PF14 | J317 | System | No |
| DCDC | PF15 | Enable | System | No |
| Fahrzeug | PG2 | Buzzer | System | No |
| Fahrzeug | PG3 | Generator LED | System | No |
| Fahrzeug | PG9 | Wischwarn | Komfort | No |
| Fahrzeug | PG10 | Bremswarn | Komfort | No |
| Fahrzeug | PG11 | Pumpe Bremse | System | No |
| Fahrzeug | PG13 | Pumpe Kühlung | System | No |
| Fahrzeug | PG14 | Lüfter 2 | System | No |
| Fahrzeug | PG15 | Lüfter 1 | System | No |

---

## Besondere Eingänge
Bei mehreren Eingängen gibt es noch zusätzliche Eigenschaften, weshal diese nicht als
reine Logik IO betrachtet werden können. Dies liegt daran, dass sie entsprechend wichtig
sind oder noch eine andere Aufgabe haben, als nur einen Logikpegel einzulesen.

---

## System relevante Eingänge
Alle System relevanten Eingänge haben etwas mit der Auswertung der Daten zum Fahren mit
dem Fahrzeug zu tun. Diese Eingänge werden deshalb öfter grprüft als Komforteingänge.
Zudem geben die System relevanten Eingänge aufschluss auf Komponentenzustände die zum
Fahren benötigt werden. Sie werden ebenfalls über den CAN-Bus als Nachricht versendet,
um die Zustände für Debug-Zwecke mitloggen zu können.

---

## Komfort Eingänge
Alls Komfort Eingänge sind zusätzlich vorhanden und dienen nur der Steuerung von Periferie,
die nicht zum Fahren wichtig ist aber mit im Fahrzeug verbaut werden soll. Diese Komponenten
werden erstmal nicht mit ihren eigentlichen Funktionen belegt und werden erst einmal für
Debug-Zwecke verwendet.

Im weiteren Verlauf werden diese Eingänge mit ihrer eigentlichen Funktion belegt.