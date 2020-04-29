# Übungszettel 2 - 30. April 2020
Bearbeitung bis zum 7. Mai.

## Aufgabe 1 (Implicit SIR Model)



## Aufgabe 2 (C++ Ausdrücke)
Sie haben in der Vorlesung über *Number conversion* und *initialization* gesprochen.
Geben Sie den Wert der Variablen nach der Initialisierung an und erklären Sie wie dieser zustande kommt.

1. `double x = 42.0f:`
2. `float x = 1e-50;`
3. `double x = 1/2;`
4. `double x = 1.0/2;`
5. `int x = -3ul + 4;`

## Aufgabe 3 (Automatic Differentiation)

In dieser Aufgabe soll mithilfe von operator overloading ein
*Automatic differentiation type* entwickelt werden.
Das ist ein Datentyp, der die Auswertung einer Funktion $`f(x)`$ und deren Ableitung $`f^\prime(x)`$ speichert.
Die arithmetischen Operatoren sind so überladen, dass auf der
Auswertung der Ableitung die jeweilige Ableitungsregel ausgeführt wird.
Zum Beispiel:
```math
    (f(x), f^\prime (x)) * (g(x), g^\prime (x)) = (f(x)g(x), (f(x)g^\prime (x) + f^\prime(x)g(x))
```

1. Sie finden im Ordner `autodiff` eine Datei `ad.hh`. Machen Sie sich mit dem Inhalt vertraut.
2. Implementieren Sie die fehlenden arithmetischen Operatoren.
3. In der Datei `newton.cc` finden Sie ein Testprogramm. Testen Sie damit die Funktion von `SimpleAd`.
4. Vervollständigen Sie die Funktion `newton`, sodass sie das
   Newton-Verfahren zur Ermittlung von Nullstellen implementiert:

```math
    x^{i+1} = x^i - \frac{f(x^i)}{f^\prime (x^i)}
```
5. Testen Sie das Newton-Verfahren in dem Sie den zweiten Teil der `main` Funktion einkommentieren.

Mehr Informationen zum automatischen Differenzieren finden Sie z.B. [hier](https://de.wikipedia.org/wiki/Automatisches_Differenzieren).
