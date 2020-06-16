# Übungsblatt 06 - 16. Juni 2020
Bearbeitung bis zum **25. Juni**

## Aufgabe 1 (Temporäre Variablen)
In `cg.h` ist eine Implementierung des CG Verfahrens gegeben, die stark an die mathematische Notation angelegt ist.
Ebenfalls vorgegeben sind (leicht erweiterte) Implementierungen der `Matrix` und `Vector` Klasse. Allerdings ist
diese Implementierung ineffizient bezüglich des Umgangs mit temporären Vectoren.
1. Schreiben Sie ein Testprogramm, das die Korrektheit der Klassen `CGSolver`, `Matrix` und `Vector` überprüft. 
2. Identifizieren Sie die Ursache dieser Ineffizienz. (Hinweis: achten Sie auf die Funktiondeklarationen.) Zusätzlich
   sollen Sie diese Ineffizienz quantifizieren, d.h. wie oft werden temporäre Variablen erstellt, kopiert oder
   verschoben innerhalb einer Iteration des CG Verfahrens.
3. Ändern Sie nur die Funktiondeklarationen in `vector.h` um das Programm zu verbessern. Achten Sie darauf, dass die
   Implementierung weiterhin korrekt ist. Warum sind damit noch nicht alle Ineffizienzen behoben?
4. Fügen Sie Überladungen bereits vorhandener Funktionen in `vector.h` hinzu, die die Erstellung von temporären Variablen
   reduzieren.

Hinweis: Ihre Abgabe braucht nur eine Implementierung enthalten, die 3. und 4. zusammenfasst, es müssen keine separaten
Datein zur Lösung von 3. und 4. angelegt werden.

Lösungen:
2. *TODO*
3. *TODO*

## Aufgabe 2 (SFNINAE)
Erweitern Sie ihre `Polynom` Klasse um eine Funktion für den `+=` Operator, die nur dann kompiliert wenn das Polynom
auf der rechten Seite den gleichen Grad oder niedriger hat. Nutzen Sie dafür `enable_if` im Rückgabewert, um die Funktion
aus dem Overload-Set zuentfernen, wenn der Grad des anderen Polynoms größer ist.

## Aufgabe 3 (Template Spezialization)
In `specialization.cc` ist eine templatisierte Funktion `determinante` definiert, die für eine Matrix, gegeben als ein
`std::array<std::array<double, N>, N>` Object, die Determinante berechnet. Im allgemeinen Fall lässt sich diese über eine
LU Zerlegung berechnen. Spezialisieren Sie diese Funktion für 1D, 2D, und 3D.

Optional: Wie lässt sich die Funktion spezialisieren, wenn statt `double` ebenfalls ein Template-Parameter benutzt wird? 
