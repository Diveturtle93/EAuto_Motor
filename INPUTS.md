# **Input Zuweisung**

Es stehen für die Programmierung unterschiedlichste Eingänge am Mikrocontroller zur
Verfügung. Diese sind alle über eine entsprechende Logiklevel Schaltung nach aussen
geführt.

---

Es stehen für die Auswertung zwei unterschiedlicher Schaltungen zur Verfügung.
Bei der ersten Schaltung muss der Schalter ein 12V Signal an den Eingang anlegen.
Dieses wird dann verarbeitet und an den Mikrocontroller invertiert mit einem 3.3V Pegel
weitergegeben. Ist der Schalter nicht gedrückt, so liegt am Mikrocontroller 3.3V an. Wird
der Schalter gedrückt, so fällt das Signal am Mikrocontroller auf 0V ab. Die zweite Art
von Schaltung ist genau umgekehrt. Hier muss der Schalter das Signal mit Masse versorgen.
Dieses Signal wird ebenfalls über einen Pegelwandler insgesamt ein 3.3V Signal umgewandelt.
Hier bekommt der Mikrocontroller ein 3.3V Signal, sobald der Schalter gedrückt wird.
Ist der Schalter nicht gedrückt, so liegen am Eingang des Mikrocontrollers 0V an.

---

Alle Eingänge sind Kurzschluss fest und für Spannungen von 0V bis 12V ausgelegt. Darüber
hinaus sind die Eingänge sicher gegen Verpolung und Überspannungen bis 24V.


## Liste der Eingänge

Nachfolgend ist eine Auflistung aller Eingangspins vom Mikrocontroller.

| Funktionsgruppe | Pin | Funktion | Relevanz | Getestet |
|:--------------- |:---:|:-------- |:-------- | --------:|
| Shutdown Circuit | PA0 | Crash | System | No |
| Shutdown Circuit | PA1 | Emergency Run | System | No |
| STM32 | PA2 | Wakeup | Komfort | No |
| Navibedienelement | PA9 | Out A | Komfort | Ja |
| Navibedienelement | PA10 | Out B | Komfort | Ja |
| Board Computer | PA11 | Up In | Komfort | No |
| Shutdown Circuit | PB10 | BTB Sense | System | No |
| Fahrzeug | PB15 | Anlasser | System | No |
| SD-Card | PC6 | SD Switch | Komfort | No |
| Navibedienelement | PC7 | Enter | Komfort | Ja |
| STM32 | PC13 | Button 1 | Komfort | No |
| ASR | PD4 | ASR 2 | Komfort | No |
| Fahrzeug | PD8 | KL15 | System | No |
| Bamocar | PD10 | Bamo In 2 | Komfort | No |
| Bamocar | PD12 | Bamo In 1 | Komfort | No |
| ASR | PE3 | Eco | Komfort | No |
| Board Computer | PE4 | Down In | Komfort | No |
| Fahrzeug | PE5 | Durchfluss | Komfort | No |
| STM32 | PE6 | Button 2 | Komfort | No |
| Pedale | PE8 | Kickdown | System | No |
| Pedale | PE9 | Leerlauf | System | No |
| Pedale | PE10 | Kuplung NO | System | No |
| Pedale | PE11 | Bremse NC | System | No |
| Pedale | PE12 | Bremse NO | System | No |
| Shutdown Circuit | PE13 | AKKU Sense | System | No |
| Shutdown Circuit | PE14 | SDC0 Sense | System | No |
| ASR | PF1 | ECON | Komfort | No |
| Fahrzeug | PF11 | Recuperation | Komfort | No |
| DCDC | PG0 | Instruction | System | No |
| DCDC | PG1 | Fault | System | No |
| ASR | PG4 | ASR 1 | Komfort | No |
| Tempomat | PG5 | GRA 4 | Komfort | No |
| Tempomat | PG6 | GRA 3 | Komfort | No |
| Tempomat | PG7 | GRA 2 | Komfort | No |
| Tempomat | PG8 | GRA 1 | Komfort | No |
| Board Computer | PG12 | Reset In | Komfort | No |


## System relevante Eingänge

Alle System relevanten Eingänge haben etwas mit der Auswertung der Daten zum Fahren mit
dem Fahrzeug zu tun. Diese Eingänge werden deshalb öfter geprüft als Komforteingänge.
Zudem geben die System relevanten Eingänge aufschluss auf Komponentenzustände die zum
Fahren benötigt werden. Sie werden ebenfalls über den CAN-Bus als Nachricht versendet,
um die Zustände für Debug-Zwecke mitloggen zu können.


## Besondere Eingänge

Bei mehreren Eingängen gibt es noch zusätzliche Eigenschaften, weshalb diese nicht als
reine Logik IO betrachtet werden können. Dies liegt daran, dass sie entsprechend wichtig
sind oder noch eine andere Aufgabe haben, als nur einen Logikpegel einzulesen.


## Komfort Eingänge

Alle Komfort Eingänge sind zusätzlich vorhanden und dienen nur der Steuerung von Periferie,
die nicht zum Fahren wichtig ist, aber mit im Fahrzeug verbaut werden soll. Diese Komponenten
werden erstmal nicht mit ihren eigentlichen Funktionen belegt und werden aktuell nur für
Debug-Zwecke verwendet.

Im weiteren Verlauf bekommen diese Eingänge ihrer eigentlichen Funktion zugewiesen.

## Standart Werte

Für sämtliche Eingänge liegen standart Werte für die Auswertung vor. Diese liegen auch am
Mikrocontroller an wenn kein Stecker am Motorsteuergerät gesteckt ist. Darüber hinaus
wird noch in der nachfolgenden Tabelle mit aufgeführt, welche Werte am Mikrocontroller
eingelesen werden können, wenn das Motorsteuergerät im Fahrzeug verbaut ist. Diese beiden
Werte können sich gegebenenfalls von einander unterscheiden.

| Funktionsgruppe | Pin | Funktion | Standart Wert | Wert KFZ KL15 aus| Wert KFZ KL15 an |
|:--------------- |:---:|:-------- | -------------:| ----------------:| ----------------:|
| Shutdown Circuit | PA0 | Crash | 1 | 1 | 1 |
| Shutdown Circuit | PA1 | Emergency Run | 1 | 1 | 1 |
| STM32 | PA2 | Wakeup | 1 | 1 | 1 |
| Navibedienelement | PA9 | Out A | 1 | 1 | 1 |
| Navibedienelement | PA10 | Out B | 1 | 1 | 1 |
| Board Computer | PA11 | Up In | 1 | 1 | 1 |
| Shutdown Circuit | PB10 | BTB Sense | 1 | 1 | 1 |
| Fahrzeug | PB15 | Anlasser | 1 | 1 | 1 |
| SD-Card | PC6 | SD Switch | 1 | 1 | 1 |
| Navibedienelement | PC7 | Enter | 1 | 1 | 1 |
| STM32 | PC13 | Button 1 | 1 | 1 | 1 |
| ASR | PD4 | ASR 2 | 1 | 1 | 1 |
| Fahrzeug | PD8 | KL15 | 1 | 1 | 1 |
| Bamocar | PD10 | Bamo In 2 | 1 | 1 | 1 |
| Bamocar | PD12 | Bamo In 1 | 1 | 1 | 1 |
| ASR | PE3 | Eco | 1 | 1 | 1 |
| Board Computer | PE4 | Down In | 1 | 1 | 1 |
| Fahrzeug | PE5 | Durchfluss | 1 | 1 | 1 |
| STM32 | PE6 | Button 2 | 1 | 1 | 1 |
| Pedale | PE8 | Kickdown | 1 | 1 | 1 |
| Pedale | PE9 | Leerlauf | 1 | 1 | 1 |
| Pedale | PE10 | Kuplung NO | 1 | 1 | 1 |
| Pedale | PE11 | Bremse NC | 1 | 1 | 1 |
| Pedale | PE12 | Bremse NO | 1 | 1 | 1 |
| Shutdown Circuit | PE13 | AKKU Sense | 1 | 1 | 1 |
| Shutdown Circuit | PE14 | SDC0 Sense | 1 | 1 | 1 |
| ASR | PF1 | ECON | 1 | 1 | 1 |
| Fahrzeug | PF11 | Recuperation | 1 | 1 | 1 |
| DCDC | PG0 | Instruction | 1 | 1 | 1 |
| DCDC | PG1 | Fault | 1 | 1 | 1 |
| ASR | PG4 | ASR 1 | 1 | 1 | 1 |
| Tempomat | PG5 | GRA 4 | 1 | 1 | 1 |
| Tempomat | PG6 | GRA 3 | 1 | 1 | 1 |
| Tempomat | PG7 | GRA 2 | 1 | 1 | 1 |
| Tempomat | PG8 | GRA 1 | 1 | 1 | 1 |
| Board Computer | PG12 | Reset In | 1 | 1 | 1 |