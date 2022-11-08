# **Revisionen**

Während der Entwicklung werden unterschiedliche Revisionen der einzelnen Platinen entstehen. Damit die
Software nur einmal erstellt werden muss, und nicht für jede Platine, wird beim Kompilieren eine
Compiler Variable mit übergeben, die dann in der Software bestimmte Funktionen mit definiert bzw.
Funktionen beim kompilieren weg lässt. Das ist wichtig, wenn man die Software mit mehreren Platinen
und unterschiedlichen Platinen Revisionen testen möchte.

## Liste der Platinen Revisionen

| Platine | Revision | Sample Number im Code |
|:------- |:--------:| ---------------------:|
| Motorsteuergerät | 1.0 | 1 |
| Motorsteuergerät | 1.1 | 2 |
| Motorsteuergerät | Keine | 255 |
| Batteriemanagement-System | 1.0 | 1 |
| Batteriemanagement-System | 1.1 | 2 |
| Batteriemanagement-System | Keine | 255 |