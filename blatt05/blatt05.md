# Übungsblatt 05 - 25. Mai 2020
Bearbeitung bis zum **08. Juni**.

## Aufgabe 1 (Class Templates)
Schreiben Sie ein Klassentemplate `Polynom` die ein Polynom `n`-ten
Grades implementiert. Als template-Parameter sollen der Polynomgrad
`n` sowie der numerische Typ angegeben werden können. Außerdem soll
sich die Klasse durch mit
einem `std::array` initialisieren lassen und einen über den `operator()`
auswerten lassen.
Implementieren Sie außerdem den `operator *= (const K& alpha)`, wobei `K`
der numerische Type ist, das ein Polynom mit dem Faktor `alpha` skaliert.

## Aufgabe 2 (Function Templates)
- Schreiben Sie ein freies Funktionstemplates `differntiate` welches
  als Parameter ein `Polynom` $`n`$-ten Grades als Parameter erhält, die
  Ableitung berechnet und diese als Polynom $`n-1`$-Grades zurück gibt.

- Schreiben Sie freie `operator`en für die mathematischen Operatoren
  für Addition, Subtraktion und Multiplikation für Polynome vom Grad `n` und `m`.
  Überlegen Sie sich insbesondere was ein geeigneter Rückgabetyp ist.

## Aufgabe 3 (Lagrange Interpolation)
- Schreiben Sie eine Funktion `LagrangeBasis` die zu gegebenen
  Stützstellen, gegeben in einem `std::array<double, K>` die
  zugehörige Lagrange-Basis berechnet.

- Erstellen Sie ein geeignetes Testprogramm um die Lagrange-Basis zu testen.

*Hinweis*: Eine Beschreibung der Lagrange-Polynome finden Sie z.B. auf
[Wikipedia](https://de.wikipedia.org/wiki/Lagrange-Polynom).
