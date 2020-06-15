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
