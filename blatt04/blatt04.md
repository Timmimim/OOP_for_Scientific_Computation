# Übungsblatt 04 - 14. Mai 2020
Bearbeitung bis zum **21. Mai**.

## Aufgabe 1 (move-construction and -assignment)
Betrachten Sie das Programm `move.cc`.
 - 1.1: Verändern sie die Klasse `A` so, dass bei der Auswertung von
     ```c++
       A d = a + b + c;
     ```
     nur ein default constructor aufgerufen wird.

 - 1.2: Verändern Sie den Ausdruck
     ```c++
     a = a + b + c;
     ```
     durch
   Verwendung von `std::move`, sodass bei der Auswertung nur der
   move constructor aufgerufen wird.

## Aufgabe 2 (SIR Modell mit explizitem und implizitem Euler)

Schreiben Sie ein Programm, dass das SIR-Modell mit Hilfe des
impliziten Euler Verfahrens löst.
Eine Beschreibung der Methode finden Sie auf der [Homepage zur
Vorlesung](https://sso.uni-muenster.de/LearnWeb/learnweb2/mod/resource/view.php?id=1563639&forceview=1).
Gehen Sie dafür in folgenden Schritten vor:

- Überlegen Sie zunächst was das Konzept eines Anfangswertproblems (ODE) umfasst,
  so dass das SIR Modell nur eine Realisation dessen ist und das Programm später
  auch mit anderen Modellen genutzt werden kann.
  
- Schreiben Sie eine abstrakte Basisklasse `ODE`, welche das Konzept beschreibt.
  Die Zeitschrittverfahren sollen später nur Methoden dieser Klasse nutzen.

- Implementieren Sie das SIR-Modell in eine Klasse `SIR`, die von dem Interface `ODE` erbt.
  Benutzen Sie die Parameter $`\beta = 0.4, \gamma = 0.04`$.

- Überlegen Sie sich ein Konzept für einen ODE Löser und schreiben Sie
  eine abstrakte Basisklasse `ODESolver`.

- Implementieren Sie das explizite Euler-Verfahren in eine Klasse `ExplicitEuler`,
  welche von dem Interface `ODESolver` erbt.

- Implementieren Sie das implizite Euler-Verfahren in eine Klasse `ImplicitEuler`,
  welche von dem Interface `ODESolver` erbt.

- Schreiben Sie das `main` Programm, das die beiden Konzept
  zusammenführt und die ODE mit Hilfe des Lösers löst.

Verwenden Sie das Lineare Algebra Framework vom letzten
Übungsblatt. Ggf. macht es Sinn die Klassen um einige Operatoren zu erweitern.



## Aufgabe 3 (Visualisierung)
- 3.1: Setzten Sie sich mit den C++ Funktionen für die Datei-Ausgabe auseinander.
Informationen finden Sie z.B. auf [cppreference.com](https://en.cppreference.com/w/cpp/io/basic_ofstream).

*Tipp*: Sie können für die Klasse `Vector` den Operator
```
    std::ostream operator<<(std::ostream& stream, const Vector& x)
```
implementieren. Dieses können Sie dann sowohl für `std::cout` als auch
für `std::ofstream`s verwenden.

- 3.2: Erweitern Sie Ihr Programm aus Aufgabe 2, sodass die Lösung in
  eine csv-Datei geschrieben wird.

- 3.3: Schreiben Sie ein `python` Programm, dass die csv Datei einlädt
  und die Lösung visualisiert. Für das laden der csv-Datei können sie
  die Funktion `numpy.loadtxt` verwenden. Sie können dabei auf das `python`
  Beispiel zum (expliziten Euler Verfahren)[https://sso.uni-muenster.de/LearnWeb/learnweb2/pluginfile.php/2336433/course/section/528482/euler.py?time=1587851741940]
  aufbauen.
