# **Kombiinstrument FIS**

Die Kommunikation mit dem FIS am Kombiinstrument läuft über den Infotainment-CAN im Fahrzeug. Dieser ist nicht
standardmäßig vorgesehen und wird deshlab nachgerüstet. Auf diesem sind Daten die auch auf den Komfort-CAN
vorhanden sind, als auch die Nachrichten für die Ansteuerung des FIS.

Das FIS kann in drei Teile unterteilt werden. Oben, Mitte, Unten. Im oberen Teil befinden sich zwei Zeilen,
die einzeln angesprochen werden können. Darunter ist der mittlere Bereich für die allgemeinen Infos.
Dieser ist mit zwei Strichen abgetrennt. Unterhalb befindet sich der dritte Bereich. Dieser hat ebenfalls zwei
Zeilen. Zudem kann auch der gesamte oder nur der mittlere und untere Bereich angesprochen werden. Die hängt
von der Konfiguration und des beanspruchten Displayplatzes ab.

---

Der oberste Bereich kann zudem auch einzeln über zwei Nachrichten angesprochen werden. Dies wird standardmäßig
vom Radio gemacht. Dabei ist dann eine ID für die obere Zeile (0x261) und eine ID für die untere Zeile (0x263) da.
Zusätzlich muss dann noch die Nachricht mit der ID 0x661 auf dem CAN-Bus gesendet werden. Ansonsten werden
diese beiden IDs nicht akzeptiert.

Für die Nachricht mit der ID 0x661 sind dann folgende Daten zu senden:

0x81 0x01 0x12 0xA0 0x00 0x00 0x00 0x00

Die beiden Zeilen bleiben solange angezeigt, bis sich der Inhalt ändert oder die Nachricht 0x661, für ca. 5s, 
nicht mehr auf dem CAN-Bus present ist.

---

Des Weiteren gibt es noch die beiden Nachrichten mit den IDs 0x265 und 0x267. Diese werden nur akzeptiert,
wenn im Kombiinstrument die Konfiguration Telefon auf dem CAN-Bus aktiviert ist. Um dann die Daten in den
obersten beiden Zeilen anzuzeigen, wird dann noch die Nachricht mit der ID 0x665 benötigt.

Der Inhalt ist:

0x77 0x25 0x00 0xAA 0xAC 0xAA 0x2A

Wenn diese Nachricht gesendet wird, werden die beiden Nachrichten 0x261 und 0x263 überschrieben und erst wieder
angezeigt, wenn die Nachricht 0x665 nicht mehr gesendet wird. Der Inhalt 0x77 bedeutet aktiv anzeigen. Mit dem
Inhalt 0x61 wird die Nachricht inaktiv und nicht auf dem Display ausgegeben. Sie wird aber von Kombiinstrument
akzeptiert und abgespeichert.

---

Der mittlere FIS Bereich verwendet die Nachrichten mit den IDs 0x6C0 und 0x6C1. Damit tauscht man Informationen
und Konfigurationen aus. Das Protokoll erwartet eine Bestätigung beider Teilnehmer und bricht die Kommunikation
bei einem Timeout ab. Dann muss von vorne begonnen werden.

Zu Beginn ist eine Initialisierung notwendig, bevor Daten auf dem Display angezeigt und geschrieben werden können.
Wenn alle Daten gesendet wurden, bleibt die Anzeige für ca. 10s stehen, bis das Display wieder auf die
standardmäßige Anzeige zurückkehrt.


Quellen (12.07.2024):
https://github.com/quiggy/AudiCanControl
https://github.com/John949949/DIS-Display
https://www.ttforum.co.uk/threads/instrument-cluster-circuit-board.1938787/
https://www.ttforum.co.uk/threads/displaying-boost-on-the-dis.1954729/
