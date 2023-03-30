# **Output Zuweisung**

Es stehen für die Programmierung unterschiedlichste Ausgänge am Mikrocontroller zur
Verfügung. Diese sind alle über eine entsprechende Logiklevel Schaltung nach aussen
geführt.

---

Es stehen für die Ansteuerung zwei unterschiedlicher Schaltungen zur Verfügung.
Unterschieden werden die beiden Ausgangsschaltungen nur in ihrer Stromtragfähigkeit.
Die beiden Ausgangsstufen haben unterschiedliche Leistungsmosfets verbaut, welche
somit eine unterschiedliche Stromtragfähigkeit besitzen. Somit kann man
unterschiedlichste Periferie ansteueren und schalten.

---

Alle Ausgänge arbeiten mir der angelegten Fahrzeugspannung. Sie sind alle ausgelegt
für 12V, können aber auch mit 24V betrieben werden.


## Liste der Ausgänge

Nachfolgend ist eine Auflistung aller Ausgangspins vom Mikrocontroller.

| Funktionsgruppe | Pin | Funktion | Relevanz | Getestet |
|:--------------- |:---:|:-------- |:-------- | --------:|
| Fahrzeug | PA12 | Rücklichtwarnung | Komfort | Ja |
| STM32 | PB2 | LED Red | Komfort | Ja |
| Fahrzeug | PB4 | Heizung 2 | System | No |
| STM32 | PB7 | LED Green | Komfort | Ja |
| Fahrzeug | PB11 | F54 | System | No |
| Fahrzeug | PB12 | F18 | System | No |
| Fahrzeug | PB13 | Klima Out | System | No |
| STM32 | PB14 | LED Blue | Komfort | Ja |
| ASR | PC3 | WS2812 LED | Komfort | Ja |
| Fahrzeug | PD3 | Ladeleuchte | Komfort | No |
| Fahrzeug | PD7 | Öltemp | Komfort | Ja |
| Fahrzeug | PD9 | Bremslicht | Komfort | No |
| Fahrzeug | PD11 | Rücklicht | Komfort | No |
| Fahrzeug | PD13 | Klima PWM Out | System | No |
| Fahrzeug | PD14 | Anhänger | Komfort | Ja |
| Fahrzeug | PD15 | Reserve | Komfort | Ja |
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
| Fahrzeug | PG9 | Wischwarn | Komfort | Ja |
| Fahrzeug | PG10 | Bremswarn | Komfort | Ja |
| Fahrzeug | PG11 | Pumpe Bremse | System | No |
| Fahrzeug | PG13 | Pumpe Kühlung | System | No |
| Fahrzeug | PG14 | Lüfter 2 | System | No |
| Fahrzeug | PG15 | Lüfter 1 | System | No |


## System relevante Ausgänge

Alle System relevanten Ausgänge sind für die Ansteuerung von Komponenten, die etwas mit dem
Fahren des Fahrzeug zu tun haben. Diese Ausgänge werden deshalb öfter betrachtet als
Komfortausgänge. Zudem dürfen die System relevanten Ausgänge nicht ausfallen und müssen
auch im Notfall funktionieren. Sie werden ebenfalls über den CAN-Bus als Nachricht versendet,
um die Zustände für Debug-Zwecke mitloggen zu können.


## Besondere Ausgänge

Bei mehreren Ausgängen gibt es noch zusätzliche Eigenschaften, weshalb diese nicht als
reine Logik IO betrachtet werden können. Dies liegt daran, dass sie mit einer PWM ein
Gerät ansteuern müssen.


## Komfort Ausgänge
Alle Komfort Ausgänge sind zusätzlich vorhanden und dienen nur der Steuerung von Periferie,
die nicht zum Fahren wichtig ist, aber mit im Fahrzeug verbaut werden soll. Diese Komponenten
werden erstmal nicht mit ihren eigentlichen Funktionen belegt und können aktuell für
Debug-Zwecke verwendet werden.

Im weiteren Verlauf bekommen diese Ausgänge ihrer eigentlichen Funktion zugewiesen.

Bremswarn braucht 1s um angezeigt und 2s gelöscht zu werden
Rücklichtwarnung braucht 2s um angezeigt und gelöscht zu werden
Wischwarn braucht 20s um angezeigt und gelöscht zu werden