# Übungszettel 2 - 30. April 2020
Bearbeitung bis zum 7. Mai.

## Aufgabe 1 (Fließkommazahlen)
1. Was ist der Unterschied zwischen `float` und `double`?
  
- Der Typ `double` erlaubt die Handhabung von floating point Werten in doppelter Präzision gegenüber `float`, 
indem die doppelte Anzahl Bits zur Darstellung zur Verfügung stehen. 
Der darstellbare Zahlenbereich steigt mit der Bit-Größe von Mantisse und Exponent (s. `IEEE_754`)

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

- Die Ersetzung würde rein technisch bei der Laufzeit nicht (nennenswert) zu Buche schlagen. Die Speicherunterschiede sind extrem gering, und x64 Systeme und Prozessoren machen kaum einen Unterschied zwischen float und double Berechnungen (s. Mini-Benchmark https://entwickler-ecke.de/topic_Berechnungen+mit+float+oder+double_114463,0.html).

- Allerdings ist der Decrement-Operator `--x` so definiert, dass er den gegebenen Wert auf den jeweils nächsten niedrigeren ganzzahligen Wert (plus Nachkommastellen) erniedrigt. Während dies bei Integer Typen ein simples -1 darstellt, und lineare Veränderungen der Bit-Werte bedeutet, ist dies wegen der komplexen Repräsentation von floating point Typen nicht ganz so simpel. In diesem Fall geht der Wert aufgrund der begrenzten Präzision des `float`-Typen durch Rundung verloren, da `99.999.999f` nicht darstellbar ist und `x` wird nie verändert. Dadurch kann die Schleife nie terminieren, und die Laufzeit erhöht sich auf "unendlich".

- Ein weiterer möglicher 'Pitfall' an dieser Stelle wäre, dass ein Wert, der in `double`-precision präzise darstellbar ist, im Bereich der `float`-precision nicht darzustellen ist (e.g. 1.0e50), und beim impliziten und/oder expliziten Cast in der Folge einen `underflow` oder `overflow` auslöst, bzw auf einen Wert gerundet wird, der eine feste Konstante repräsentiert. Der Datentyp bedingt veränderte Werte, die wiederum das Verhalten des Programms beeinträchtigen. Im o.g. Fall ergäbe sich so 
```c++ 
    float x = 1.0e50f;
    while(x > 0)
    {
        --x;  // bei erster Ausführung x = inf, positive infinity value
        /*
            In der Folge wird x durch den --x Operator nicht mehr 
            veränderlich sein, gegeben durch die Implementierung von inf;
            Dadurch terminiert die Schleife nie, und es ergibt sich 
            eine unendliche Laufzeit (>> 1s). 
    }
```


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
  - **`None`, da beide Assertions zutreffen.**
- Was ist die Ausgabe des Programms, wenn wir `float` durch `double` ersetzen? Warum?
  - Assertions schlagen beide (!!) fehl, Programm mit Fehlermeldung beendet.
  - Die Double-Repräsentationen von `(.1 + .2)` und `(.15 + .15)` unterscheiden sich in den letzten 3 Stellen der _Mantisse_, sodass sich `a < b` ergibt:
    - `.15 + .15` == `0011111111010011001100110011001100110011001100110011001100110011`
    - `0.1 + 0.2` == `0011111111010011001100110011001100110011001100110011001100110100`
  - Die weniger präzise Single-Precision Float Representation ist dagegen entgegen aller Wahrscheinlichkeit in diesem Zusammenhang präziser, da `a == b`:
    - `.15f + .15f` == `00111110100110011001100110011010`
    - `0.1f + 0.2f` == `00111110100110011001100110011010`


### Resources
- https://en.wikipedia.org/wiki/Floating-point_arithmetic
- https://en.wikipedia.org/wiki/IEEE_754
```c++
#include <memory>
#include <iostream>
#include <limits>
#include <iomanip>

#include <cassert>

template <typename T>
std::string getBits(T t) {
    std::string returnString{""};
    char *base{reinterpret_cast<char *>(std::addressof(t))};
    char *tail{base + sizeof(t) - 1};
    do {
        for (int bits = std::numeric_limits<unsigned char>::digits - 1; bits >= 0; bits--) {
            returnString += ( ((*tail) & (1 << bits)) ? '1' : '0');
        }
    } while (--tail >= base);
    return returnString;
}

int main()
{
    using T = double; // or float; a type-alias
    T a = 0.15 + 0.15;
    T b = 0.1 + 0.2;
    //assert(a == b);
    //assert(a >= b);

    std::cout << getBits(a) << std::endl;
    std::cout << getBits(b) << std::endl;
}
```


## Aufgabe 2 (Kontrollstrukturen)
Zu C++ Kontrollstrukturen: `if`, `else`, `for`, `do`, `while`, `switch`, `case`.

1. Ersetzen einer `while`-Schleife durch eine `for`-Schleife:
```c++
int log10 = 0;
double num = 12345.0;
while (num >= 10.0) {
  num /= 10.0;
  ++log10;
}
```
==>
```c++
int log10 = 0;
double num = 12345.0;
for (num; num >= 10.0; num /= 10.0)
  ++log10;
```

2. Was ist der Fehler in den folgenden Codes?

  i.
```c++
  for (int j = 0, j < 10, ++j)
    std::cout << j;
```
 - Kommata anstelle der korrekten Semikola;
 - korrekt wäre `for (int j = 0; j < 10; ++j)`

  ii.
```c++
int n, sum = 0;
do
{ std::cin >> n; sum += n; }
while (n > 0)
```
  - Schließendes Semikolon fehlt (`... while (n > 0);`)
  - Anmerkung:
    - Wertzuweisungen müssen einzeln geschehen, n so nicht explizit initialisiert (Wert aus Bit-Zustand im allozierten Speicher übernommen, kann beliebiger `int` Wert sein)
    - korrekter / besser wäre `int n = 0, sum = 0;`, siehe nächste Aufgabenstellung.


  iii.
```c++
int n = 2, m;
while (n < 10)
  m *= n, ++n;
```
  - `m` wird nicht explizit initialisiert, nimmt zu Beginn beliebigen `int` Wert
  - Im Test erzeugt dies `m = 0`, wenn `m` zuletzt deklariert wird.
  - Wird noch mindestens eine weitere Variable hinter `m` deklariert, wird diese `0`, und `m` nimmt im Test einen willkürlichen Wert im Interval `[32764, 32767]` an
  - Die Multiplikation sorgt in der Folge für einen Overflow im `int` Datentyp:
  ```shell
      # ./test
        n : m
        2 : 32765
        3 : 65530
        4 : 196590
        5 : 786360
        6 : 3931800
        7 : 23590800
        8 : 165135600
        9 : 1321084800
        10 : -995138688
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
  - Werden innerhalb des Schleifenkörpers (zwischen `do` und `while`) mehrere Instruktionen ausgeführt, müssen diese in geschweifte Klammern gefasst werden, um den Scope der Schleife abzustecken.


3. Schreiben Sie ein Programm, das die ersten $`n`$ Quadrate der positiven ganzen Zahlen berechnet.
```math
1^2 + 2^2 + 3^2 + 4^2 + ... + n^2
```
Der Parameter $`n`$ soll durch den Benutzer eingegeben werden.
Benutzen Sie die Streams `std::cin >> ...` und
`std::cout << ...` aus `<iostream>` für die Ein- und Ausgabe.

```c++
#include <iostream>

// return unsigned long to be able to calculate larger squared values
unsigned long sqr(unsigned int n)
{
  return (unsigned long) n * (unsigned long) n;
}

unsigned long squared_integer_sequence_from_0_to(int n)
{
  // n <= 0 -> return 0, as sequence is empty
  // n == 1 -> return result = 1*1 = 1
  if(n <= 0) return 0;
  if(n == 1) return 1;

  // initialise to 1 to skip 1*1 redundancy
  unsigned long res = 1;
  // start sum with 2^2, as 1^2 already known and included
  for (unsigned int i = 2; i <= n; ++i)
  {
    res += sqr(i);
  }
  return res;
}

int main()
{
  std::cout << "Please enter a positive integer number: ";
  int input;
  std::cin >> input;
  unsigned long sum_of_squares = squared_integer_sequence_from_0_to(input);
  std::cout << sum_of_squares << std::endl;
}
```


## Aufgabe 3 (C++ Ausdrücke)
Sie haben in der Vorlesung über *Number conversion* und *initialization* gesprochen.
Geben Sie den Wert der Variablen nach der Initialisierung an und erklären Sie wie dieser zustande kommt.

1. `double v = 42.0f => 42 bzw 42.0`
      - Begründung: FloatingPoint-Promotion, Double ist präziser und 42.0f kann genau repräsentiert werden.
2. `float x = 1e-50 => 0`
      - Begründung: Der angegebene`double`-Wert kann in `float` nicht dargestellt werden, und wird zu `0` gerundet im Rahmen einer FloatingPoint-Demotion.
3. `double x = 1/2 => 0`
      - Begründung: Die Division wird zuerst ausgewertet, und durch die Links-Assoziativität des Operators wird eine Ganzzahl-Division auf `integer` Werten ausgeführt. Das Ergebnis (mathematisch 0.5) wird gerundet auf 0. Erst dann wird der Wert via Type-Casting auf `double` übertragen, der Wert von `0.0` bleibt jedoch gleich.
4. `double x = 1.0/2 => 0.5`
      - Begründung: Entgegen `3.` wird hier die Division auf dem Datentyp `double` durchgeführt, mit implizitem Type-Cast von `int 2` auf `double 2.0`. Die Division ergibt in der Folge den mathematisch korrekten `double`-Wert `0.5`.
5. `int x = -3ul + 4 => 1`
      - Begründung: 
        - `-3ul` resultiert durch einen _Underflow_ im `unsigned long` Datentyp im dritt-höchsten darstellbaren `unsigned long`-Wert `18446744073709551613`.
        - Die Addition passiert implizit auf dem `unsigned long` Datentyp, mit einem impliziten Cast von `4` auf `4ul`.
        - Durch die Addition von 4 wird der `unsigned long` Maximalwert überschritten und es passiert ein _Overflow_, und die Bit-Repräsentation flippt. Das Resultat ist `1ul`, und wird schließlich gecastet auf `int`, wobei der Wert erhalten bleibt.
        - `_______3ul == 0000000000000000000000000000000000000000000000000000000000000011`
        - `______-3ul == 1111111111111111111111111111111111111111111111111111111111111101`
        - `_______4ul == 0000000000000000000000000000000000000000000000000000000000000100`
        - `-3ul + 4ul == 0000000000000000000000000000000000000000000000000000000000000001`

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
