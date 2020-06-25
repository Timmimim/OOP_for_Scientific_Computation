# Übungsblatt 08 - 25. Juni 2020
Bearbeitung bis zum **02.Juni**

## Aufgabe 1 (Binäre Operatoren)
Implementieren Sie `expression templates` zur der binären Operationen `+,-` angewandt auf den Typen `Vector`. Zusätzlich
sollen diese `expression templates` in den Typ `Vector` konvertierbar sein, d.h. der `Vector` Typ benötigt einen 
neuen Konstruktor der ihre `expression templates` akzeptiert. Ihre Implementierung soll damit in der Lage sein folgende 
Ausdrücke berechnen zu können (ohne den Einsatz von Temporaries):
```c++
Vector a, b, c;
auto t1 = a + b + c;
auto t2 = a - a;
```
Eine genauere Einführung zum Thema `expression templates` entnehmen Sie Vorlesungsskript. Da der hier verwendete
`Vector` Typ dynamische größe besitzt, müssen Ihre `expression templates` eine Funktion bereitstellen, die die Größe 
(oder auch Dimension) des Ausdrucks darstellt.

## Aufgabe 2 (Skalare Multiplikation)
Erweitern Sie Ihre `expression templates` um skalare Multiplikation und Division, also `scalar * vector` und 
`vector [*/] scalar` zu unterstützen. Sie können annehmen, dass Ausdrücke immer korrekt geklammert sind, d.h. Sie
müssen sich keine Gedanken um die korrekte Reihenfolge der Operatoren machen. Ihre Implementierung soll damit in der
Lage sein folgende Ausdrücke berechnen zu können:
```c++
Vector d, e, f;
double alpha;
auto t3 = alpha * (d + e) + f;
auto t4 = (d + e) / 2.;
```
 Beschränken Sie sich auf den Fall, dass die Skalare vom Typ `double` sind. Erstellen Sie zusätzliche Klassen, die
 Operationen der Art `op(scalar, vector)` und `op(vector, scalar)` darstellen. Achten Sie darauf, dass Sie die 
 Funktion zur Bestimmung der Größe anpassen.

## Aufgabe 3 (Skalarprodukt)
Erweitern Sie Ihre `expression templates` um das Skalarprodukt zu unterstützen, also die Operation `*(vector, vector)`.
Ihre Implementierung soll damit in der Lage sein folgende Ausdrücke berechnen zu können:
```c++
Vector g, h, i;
double t5 = g * h;
Vector t6 = (g * h) * i;
```
Erstellen Sie dazu erneut eine neue Klasse, die die Operation `*(vector, vector)` implementiert. Um die Berechnung 
des Skalarprodukts auszulösen kann ein Konvertierungs-Operator nach `double` benutzt werden die Syntax dazu lautet
```c++
class A{
    operator double() /*const (possible)*/ { /* implementation */}
};
```
siehe auch [hier](https://en.cppreference.com/w/cpp/language/cast_operator). Damit wäre die Klasse `A` implizit nach 
`double` konvertierbar, also folgende Ausdrücke wären erlaubt
```c++
void f(double);

A a{};
f(a);
```

## Aufgabe 4 (Matrix-Vector-Produkt)
Erweitern Sie Ihre `expression templates` um Matrix-Vektor-Multiplikation zu unterstützen. Ihre Implementierung soll
damit in der Lage sein folgenden Ausdruck berechnen zu können:
```c++
Vector j, k, l;
Matrix M;
auto t5 = j + M * (k - l);
```
Erstellen Sie dazu erneut eine neue Klasse, die die Operation `op(matrix, vector)` implementiert. Beachten Sie, das
keine Operationen der Art `op(matrix, matrix)` gefordert sind.

## *Optional*: Aufgabe 5 (Template-Programming)
Implementieren Sie Ihre Operatoren, ohne eine neue Klasse für Skalare-Multiplikation zu erstellen. Dies 
benötigt einen gewissen Aufwand an Template-Programmierung. Sie könnten dazu wie folgt vorgehen: erstellen Sie einen
templatisierten Typ der eine `constexpr bool` Variable enthält (oder direkt eine templatisierte Variable, siehe
[hier](https://en.cppreference.com/w/cpp/language/variable_template)) die ausdrückt, ob ein Typ sich wie ein Skalar, 
ein Vector oder eine Matrix verhält. Die default Instanziierung sollte in allen Fällen `false` sein und durch 
Spezialisierung sollte für entsprechende Typen der Wert auf `true` gesetzt werden. Mit Hilfe von `enable_if` und
SFINAE können Sie dann in Ihrer Klasse für binäre Operatoren verschiedene Varianten der selben Funktionen implementieren,
wobei nur eine aktiv ist, abhängig von den Typen der beiden Operanden. Außerdem mussen Sie die Generator-Funktionen mit
SFINAE so überladen, das immer nur eine Version aktiv ist und alle anderen aus dem Overload-Set entfernt werden.
