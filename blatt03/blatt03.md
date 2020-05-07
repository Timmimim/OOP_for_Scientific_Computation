# Übungsblatt 03 - 07. Mai 2020
Bearbeitung bis zum **14. Mai**.

Auf diesem Übungsblatt wollen wir ein kleines lineare Algebra
Framework erstellen, dass wir in den folgenden Übungsblättern weiter verwenden können.

## Aufgabe 1
Erstellen Sie eine Klasse `Vector` die den Raum $`\mathbb{R}^n`$
repräsentiert, wobei $`n\in\mathbb{N}`$ dynamisch festgelegt wird. Die
Klasse soll folgende Methoden implementieren:
- Konstruktor `Vector(unsigned int length)` initialisiert einen Vektor der Länge `length`
- Zugriff auf Koeffizienten mittels `double& operator()(unsigned int i)`
- Zugriff auf die Länge des Vektors mittels `unsigned int size() const`
- Was auch immer Sie sinnvoll finden

Eine Vorlage für die Klasse finden Sie in `vector.h`.

:bulb: `unsigned int` bedeutet das der Typ nur positive Zahlen
annehmen kann. `unsigned` ≙ nicht-Vorzeichen-behaftet

:bulb: `const`
am Ende der Funktionsdeklaration, bedeutet, dass diese Funktion auf
auch Objekten aufgerufen werden kann, die mit `const` markiert sind.

## Aufgabe 2
Erstellen Sie eine Klasse `Matrix` die den Raum $`\mathbb{R}^{n\times
m}`$ repräsentiert. $`n\in\mathbb{N}`$ und $`m\in\mathbb{N}`$ sollen ebenfalls dynamisch festgelegt sein.
Die Klasse soll folgende Methoden implementieren:
- Konstruktor `Matrix(unsigned int rows, unsigned int cols)` initialisiert eine Matrix
  mit `rows`Zeilen und `cols` Spalten
- Zugriff auf Koeffizienten mittels `double& operator()(unsigned int i, unsigned int j)`
- Zugriff auf Länge und Breite der Matrix mittels `unsigned int rows() const` und `unsigned int cols() const`
- Matrix-Vektor Multiplikation `void mv(const Vector& x, Vector& y) const`
- Was auch immer Sie sinnvoll finden

Eine Vorlage für die Klasse finden Sie in `matrix.h`.

:bulb: Der Speicher der Matrix kann sowohl mittels
`std::vector<std::vector<double>>` als auch mit einem einfachen
`std::vector<double>` implementiert werden. Wie unterscheiden sich die
Ansätze in der Praxis?

## Aufgabe 3
Implementieren Sie eine Klasse `LUDecomposition` welche eine
LU-Zerlegung einer Matrix implementiert und speichert.
Die Matrix soll folgende Methoden implementieren:
- `decompose(const Matrix& m)` berechnet die LU-Zerlegung von `m`
- `decompose(Matrix&& m)` berechnet die LU-Zerlegung von `m`, wobei
  der Speicher von `m` wieder verwertet werden soll.
- `solve(const Vector& b, Vector& x)` löst das Gleichungssystem $`Ax=b`$
  durch Vorwärts- und Rückwärtseinsetzten

Eine Vorlage für die Klasse finden Sie in `lu.h`.

## Aufgabe 4
Testen Sie die Klassen indem Sie ein Programm erstellen, das folgendes
Gleichungssystem löst

```math
    \begin{pmatrix}
      2 & -1 & 0\\
      -1 & 2 & -1\\
      0 & -1 & 2
    \end{pmatrix}
    \begin{pmatrix}
    x_1\\
    x_2\\
    x_3
    \end{pmatrix}
    =
    \begin{pmatrix}
    1\\
    1\\
    1
    \end{pmatrix}.
```

Überprüfen Sie das Ergebnis auf Richtigkeit in dem Sie das Residuum $`r = b -Ax`$ berechnen.
