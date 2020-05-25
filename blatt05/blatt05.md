# Übungsblatt 04 - 25. Mai 2020
Bearbeitung bis zum **08. Juni**.

## Aufgabe 1 (Function templates)

Schreiben Sie ein Funktionstemplate
`two_norm` das von einem beliebigen iterierbarem Container die
2-Norm berechnet.

*Hinweis*: Über die Elemente in einem solchen Container lässt sich
z.B. so iterieren:
```
for(auto element: container){
...
}
```

## Aufgabe 2 (Class templates)
Schreiben Sie in Klassentemplate `Polynom` die ein Polynom `n`-ten
Grades implementiert. Als
template-Parameter sollen der Polynomgrad `n` sowie der numerische Typ
angegeben werden können. Außerdem soll sich die Klasse durch mit
einem `std::array` initialisieren lassen und einen über den `operator()`
auswerten lassen.


## Aufgabe 3 (statischer vs. dynamischer Polymorphismus)
Implementieren Sie noch einmal ein Programm, das das SIR Modell mit dem
explizitem Euler-Verfahren löst. Verwenden Sie dabei nur statischen
Polymorphismus und std::array (bzw. einen darauf basierende Vektorklasse).

Verwenden Sie die `chrono` Bibliothek um die Laufzeit des Programms zu
bestimmen. Das können Sie z.B. so
```
#include <chrono>
...
auto start = std::chrono::steady_clock::now();
...
auto end = std::chrono::steady_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;
std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
```

Messen Sie auch die Laufzeit Ihrer Implementierung vom letzten
Übungsblatt und vergleichen Sie diese mit der statischen Implementierung.
