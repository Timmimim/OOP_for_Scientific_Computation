# Übungszettel 2 - 30. April 2020
Bearbeitung bis zum 7. Mai.

## Aufgabe 1 (Fließkommazahlen)
1. Was ist der Unterschied zwischen `float` und `double`?
2. Angenommen die Laufzeit des folgenden Codes beträgt eine Sekunde:
```c++
int main()
{
  double x = 1.0e8;
  while (x > 0)
  {
    --x;
  }
}
```
Wie würde sich die Laufzeit verändern, wenn wir `double` durch `float` ersetzen?

3. Betrachten Sie den folgenden Code:
```c++
#include <cassert>
int main()
{
  using T = float; // a type-alias
  T a = 0.15 + 0.15;
  T b = 0.1 + 0.2;
  assert(a == b);
  assert(a >= b);
}
```
`assert` ist ein Macro, das überprüft ob der Ausdruck zu `false` ausgewertet wird. 
- Was ist die Ausgabe des Programms?
- Was ist die Ausgabe des Programms, wenn wir `float` durch `double` ersetzen? Warum?

### Resources
- https://en.wikipedia.org/wiki/Floating-point_arithmetic
- https://en.wikipedia.org/wiki/IEEE_754


## Aufgabe 2 (Kontrollstrukturen)
Machen Sie sich mit den C++ Kontrollstrukturen vertraut, das sind: `if`, `else`, `for`, `do`, `while`, `switch`, `case`.

1. Ersetzen Sie im folgenden Code die `while`-Schleife durch eine `for`-Schleife:
```c++
int log10 = 0;
double num = 12345.0;
while (num >= 10.0) {
  num /= 10.0;
  ++log10;
}
```

2. Was ist der Fehler in den folgenden Codes?

  i.
```c++
  for (int j = 0, j < 10, ++j)
    std::cout << j;
```
  ii.
```c++
int n, sum = 0;
do
{ std::cin >> n; sum += n; }
while (n > 0)
```
  iii.
```c++
int n = 2, m;
while (n < 10)
  m *= n, ++n;
```
  iv.
```c++
unsigned long n = 0;
int cnt = 1;
do
  n += cnt;
  cnt++;
while (n < 100);
```

3. Schreiben Sie ein Programm, das die ersten $`n`$ Quadrate der positiven ganzen Zahlen berechnet.
```math
1^2 + 2^2 + 3^2 + 4^2 + ... + n^2
```
Der Parameter $`n`$ soll durch den Benutzer eingegeben werden.
Benutzen Sie die Streams `std::cin >> ...` und
`std::cout << ...` aus `<iostream>` für die Ein- und Ausgabe.

### Resources
- [if-then-else](https://en.cppreference.com/w/cpp/language/if), [switch-case](https://en.cppreference.com/w/cpp/language/switch),
  [for-loop](https://en.cppreference.com/w/cpp/language/for), [while-loop](https://en.cppreference.com/w/cpp/language/while),
  [do-while-loop](https://en.cppreference.com/w/cpp/language/do)
- [std::cout](https://en.cppreference.com/w/cpp/io/cout), [std::cin](https://en.cppreference.com/w/cpp/io/cin)


## Aufgabe 3 (C++ Ausdrücke)
Sie haben in der Vorlesung über *Number conversion* und *initialization* gesprochen.
Geben Sie den Wert der Variablen nach der Initialisierung an und erklären Sie wie dieser zustande kommt.

1. `double x = 42.0f:`
2. `float x = 1e-50;`
3. `double x = 1/2;`
4. `double x = 1.0/2;`
5. `int x = -3ul + 4;`

## Aufgabe 4 (Automatic Differentiation)

In dieser Aufgabe soll mithilfe von *operator overloading* ein
*Automatic differentiation type* entwickelt und in einem
Newton-Verfahren angewandt werden.
Das ist ein Datentyp, der die Auswertung einer Funktion $`f(x)`$ und
deren Ableitung $`f^\prime(x)`$ speichert.
Die arithmetischen Operatoren sind so überladen, dass auf der
Auswertung $`f(x)`$ die aritmetische Operation und auf der Ableitung
die jeweilige Ableitugnsregel ausgeführt wird.
Zum Beispiel:
```math
    (f(x), f^\prime (x)) * (g(x), g^\prime (x)) = (f(x)g(x), (f(x)g^\prime (x) + f^\prime(x)g(x))
```

1. Sie finden im Ordner `autodiff` eine Datei `ad.hh`. Machen Sie sich
   mit dem Inhalt vertraut.
2. Implementieren Sie die fehlenden arithmetischen Operatoren.
3. In der Datei `newton.cc` finden Sie ein Testprogramm. Testen Sie
   damit die Funktion von `SimpleAd`.
4. Vervollständigen Sie die Funktion `newton`, sodass sie das
   Newton-Verfahren zur Ermittlung von Nullstellen implementiert:

```math
    x^{i+1} = x^i - \frac{f(x^i)}{f^\prime (x^i)}
```
5. Testen Sie das Newton-Verfahren in dem Sie den zweiten Teil der
   `main` Funktion einkommentieren.

Mehr Informationen zum automatischen Differenzieren finden Sie
z.B. [hier](https://de.wikipedia.org/wiki/Automatisches_Differenzieren).
