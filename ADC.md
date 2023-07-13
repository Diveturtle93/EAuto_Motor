# **ADC Zuweisung**

Es sind zehn Kanäle für die ADC Auswertung vorgesehen. Jedem Kanal ist eine entsprechende
Priorisierung und ein dafür vorgesehenes Timing zugewiesen. Die Priorisierung ist von eins
bis zehn (wichtig bis unwichtig) aufgelistet. System relevante Signale bekommen eine hohe
Priorität, Signale die eher dem Komfort dienen eine niedrige Priorität. Zusätzlich ist
die Pinbelegung und die Aufgabe mit aufgeführt.

Der AD-Wandler kann nur mit einer maximalen Frequenz von 2.4 MHz Konversationen durchführen.
Bei einer APB2-Frequenz von 108 MHz muss noch ein Vorteiler gewählt werden, um den
AD-Wandler wieder mit einem zulässigen Clock zu betreiben. Gewählt wird hier der Teiler
vier. Mit diesem läuft der AD-Wandler nun mit einer Frequenz von 27 MHz.

Alle Ergbnisse werden als 12bit ausgegeben.

## Liste der AD-Kanäle

| Kanal | Pin | Funktion | Timing | Priorisierung |
|:----- |:---:|:-------- | ------:|:-------------:|
| Channel 3 | PA3 | KL15 | 5000ms | 6 |
| Channel 4 | PA4 | Kühlwasser | 5000ms | 3 |
| Channel 5 | PA5 | Klima-Flap | 1000ms | 4 |
| Channel 6 | PA6 | Gaspedal | 100ms | 2 |
| Channel 7 | PA7 | PCB Temperatur | 5000ms | 7 |
| Channel 8 | PB0 | Return | 1000ms | 9 |
| Channel 9 | PB1 | Info | 1000ms | 10 |
| Channel 14 | PC4 | Bremsdruck | 100ms | 1 |
| Channel 15 | PC5 | Bremsdrucktemperatur | 5000ms | 5 |
| Channel 18 | Temperatur Sensor | STM32 Temperatur | 1000ms | 8 |

## Priorisierung der AD-Kanäle

Die Priorisierung dient dazu die Wichtigkeit eins Signales festzulegen. Diese müssen im
Programm entsprechend deutlich häufiger eingelesen und ausgewertet werden. Zudem können
Signale mit eine niedrigen Priorisierung auch wärend des Programmablaufes vernachlässigt
werden, sollte dies den Programmablauf stören.

## Zeitliches Timing der einzelnen Konversationen

Das zeitliche Timing gibt an wie oft ein Signal ausgewertet werden muss. Dabei ist wichtig
eine dynamische Veränderung des Signales mit zu berücksichtigen. So sind schnell veränderbare
Signale deutlich häufiger ausgewertet als langsame Temperaturanstiege.

## Pinbeschreibung

Im nachfolgenden werden die Aufgaben der Pins beschrieben. Zwei Pins sind dabei besonders
wichtig. Dies sind die Pins PA6 und PC4. Sie sind für die Auswertung des Gaspedals und
für den Bremsdruck zuständig.

Des Weiteren werden insgesamt vier Temperaturen eingelesen. Zwei sind dabei auf der Platine
(STM32 und PCB). Die anderen beiden Temperaturen kommen von externen Sensoren.

Zudem werden die Klima-Flap-Stellung und die Spannung der KL15 im Motorsteuergerät
eingelesen und ausgewertet.

Als letztes sind noch zwei analoge Eingänge für ein Tasterelement vorhanden. Hierbei wird
über unterschiedliche Spannungen eine Tastendruck erkannt.

## Sampletime Cycles

Eine zusätzliche Einstellung wird noch an den Sampletime Cycles vorgenommen. Dies ist eine
Zeitverzögerung, die für ein genaueres Ergebnis sorgen soll. Dabei wird der halte Konensator
um die entsprechenden Clock-Cycles geladen. Danach werden nochmal zwölf Clock-Cycles
für eine Konversation des AD-Wertes benötigt.

## ADC-Werte

Nachfolgend werden im weiten Verlauf die ADC-Werte dokumentiert, welche standardmäßig an
den ADC-Eingängen anliegen. Zusätzlich werden noch für die Auswertung wichtige ADC-Werte
mit berücksichtigt. Auch diese sollen mit aufgefürt werden.

| Kanal | Funktion | Default-Wert @ 5V | Mit Sensor |
|:----- |:-------- | -----------------:| ----------:|
| Channel 3 | KL15 | < 10 | 3000 |
| Channel 4 | Kühlwasser | 3470 | ... |
| Channel 5 | Klima-Flap | < 10 | ... |
| Channel 6 | Gaspedal | < 10 | 253 |
| Channel 7 | PCB Temperatur | 2050 | 1980 |
| Channel 8 | Return | 2930 | 3060 |
| Channel 9 | Info | 2930 | 3060 |
| Channel 14 | Bremsdruck | 4095 | 2930 |
| Channel 15 | Bremsdrucktemperatur | 4095 | 2050 |
| Channel 18 | STM32 Temperatur | 965 | 945 |

Diese Werte sind nur durch eine einzige ADC-Messung ermittelt worden. Sie schwanken bedingt
durch Messungenauigkeiten mit einer Genauigkeit von +/- 20 um den ermittelten Wert.
Bei einer Auflösung von 12 Bit und einer Spannung von 5V am Sensor sind 20 ADC-Punkte
ca. 0,025V. Somit schwankt der Wert um ca. 0,05V. Dies sind ca. 0,03V am ADC-Eingang. Dabei
wurde der 12V Anschluss offen gelassen. Die Platine wurde direkt mit 5V versorgt.
Bei den Messungen für Kühlwasser, Klima-Flap, Gaspedal Bremsdruck und Bremsdrucktemperatur
war jeweils kein Sensor angeschlossen. Diese werden im Verlauf ergänzt.

---

Nachfolgend noch weitere Messungen mit der Platine bei unterschiedlichen Versorgungs-
spannungen.

| Kanal | Funktion | Wert @ 9V | Werte @ 12V (036906051)| Werte @ 12V (038906051) |
|:----- |:-------- | ---------:| ----------------------:| -----------------------:|
| Channel 3 | KL15 | 2235 | 2990 |3003 |
| Channel 4 | Kühlwasser | 3525 | 3530 | 3460 |
| Channel 5 | Klima-Flap | < 10 | < 10 | <10 |
| Channel 6 | Gaspedal | 253 | 253 | 253 |
| Channel 7 | PCB Temperatur | 1900 | 1915 | 1980 |
| Channel 8 | Return | 3060 | 3065 | 3060 |
| Channel 9 | Info | 3060 | 3065 | 3060 |
| Channel 14 | Bremsdruck | 3125 | 3135 | 1470 |
| Channel 15 | Bremsdrucktemperatur | 2275 | 2270 | 2280 |
| Channel 18 | STM32 Temperatur | 950 | 945 | 945 |

---

Der Drucksensor gibt an seinen beiden Maximalwerten ADC-Werte mit 679 und 3080 aus.
Das entspricht ca. 0,45 bar und 2 bar. Diese Werte müssen entsprechend noch validiert
werden. Ggf. ist auch eine Anpassung im Schaltplan notwendig.

Nach einer erneuten Messung mit einem ausgebauten Sensor sind die Werte für den Druck, wie
erwartet. Des Sensor gibt bei Umgebungsdruck (ca. 1 Bar) entsprechend eine Wert von um die
96 kPa zurück. Dies entspricht einem Druck von 0,96 Bar. Ebenfalls ist aufgefallen, dass
der erster gemessene Sensor, eine andere Teilenummer hat. Die Recherche ergab, der Sensor
hat einen geringeren maximal Druck. Dafür aber eine bessere Auflösung über den Wertebereich.
Der Wertebereich liegt für den Sensor 036906051 bei 15 kPa bis 120 kPa (0,25V bis 4,75V)