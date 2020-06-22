# Übungsblatt 07 - 16. Juni 2020
Bearbeitung bis zum **25. Juni**

## Aufgabe 1 (Temporäre Variablen)
In `cg.h` ist eine Implementierung des CG Verfahrens gegeben, die stark an die mathematische Notation angelegt ist.
Ebenfalls vorgegeben sind (leicht erweiterte) Implementierungen der `Matrix` und `Vector` Klasse. Allerdings ist
diese Implementierung ineffizient bezüglich des Umgangs mit temporären Vectoren.
1. Schreiben Sie ein Testprogramm, das die Korrektheit der Klassen `CGSolver`, `Matrix` und `Vector` überprüft. 
   Dazu können Sie das selbe Testproblem nehmen wie in Blatt 3.
2. Identifizieren Sie die Ursache dieser Ineffizienz. (Hinweis: achten Sie auf die Funktiondeklarationen.) Zusätzlich
   sollen Sie diese Ineffizienz quantifizieren, d.h. wie oft werden temporäre Variablen erstellt, kopiert oder
   verschoben innerhalb einer Iteration des CG Verfahrens.
3. Ändern Sie nur die Funktiondeklarationen in `vector.h` um das Programm zu verbessern. Achten Sie darauf, dass die
   Implementierung weiterhin korrekt ist. Warum sind damit noch nicht alle Ineffizienzen behoben?
4. Fügen Sie Überladungen bereits vorhandener Funktionen in `vector.h` hinzu, die die Erstellung von temporären Variablen
   reduzieren.

Hinweis: Ihre Abgabe soll nur eine Implementierung enthalten, die 3. und 4. zusammenfasst, es müssen keine separaten
Datein zur Lösung von 3. und 4. angelegt werden.

Lösungen:	

	(Bem.: Übermütig, wie ich bin, habe ich in 2 direkt weitere Ineffizienzen neben den Temp-Vektor-Behandlungen
	 betrachtet; diese greife ich aber in 3. wieder auf.)
	
- 2: Keine Copy- und Move-Assignment-Konstruktoren (wobei kein `move` von `std::vector` oder `std::array` möglich), sowie vor allem keine Überladungen der verschiedenen `operatorX` für _rvalue references_, und in `Vector` nahezu kein Arbeiten auf Referenzen, stattdessen Call-by-Value. Daher werden bei jedem Methodenaufruf zunächst für die Parameter neue Objekte aus den bestehenden konstruiert, und ebenso neue Objekte zurückgegeben. 

	Daher werden bereits bei der Initialisieren von `V r = y - A * x` zunächst für `A*x` (Operator-Präzedenz) ein neuer temporärer Vektor konstruiert. Der `Vector::operator-()` ist aber nicht für Referenzen oder rval-refs implementiert, und konstruiert aus `y` und dem o.g. temp-Vektor jeweils neue Vektoren für die Parameter. Als Resultat wird ein neuer temporärer Vektor konstuiert und zurückgegeben. Damit ruft der Ausdruck 4 Standard-Konstruktoren für 2 Rechnungen auf, was sehr redundant ist. Auch die `operator=` sind nicht für rval-refs überladen, i.e. noch ein Default-Konstruktor. 
	
	Dies geschieht zwar für r zunächst nur einmal, setzt sich in der `for-loop` aber mit wesentlich mehr Wirkung fort. Jeder Aufruf der `Vector::dot()` -Methode erzeugt je einen redundanten Konstruktor-Aufruf, da der Parameter _CBV_ statt _Ref_ ist, ebenso verhält es sich mit dem `operator*(double,Vector)`. Für jeden `operator+(Vector,Vector)` und `operator-(Vector,Vector)` werden zwei Konstruktoren für die Parameter, sowie ein Konstruktor für den neuen Result-Vector aufgerufen, es bräuchte aber nur letzteren bei Verwendung von `const Vector&` Referenzen. Zwei Konstruktor-Aufrufe sind somit redundant pro Operator. 
	
	Weiterhin wird die potentiell teure Matrix-Vector-Multiplication via `operator*` mehrfach ausgeführt, anstatt die Multiplikation einmalig und via `Matrix::mv()` Methode auszuführen. Erstere Methode erstellt einen neuen Vektor, und führt dann selbst `mv()` mit diesem als Zielvektor aus. Direkte Verwendung von `mv()` würde, wenn der Zielvektor außerhalb der Schleife erstellt wird, insgesamt 2 Std.-Konstruktoren pro Schleifendurchlauf sparen, da das Resultat dauerhaft zur Verfügung stünde.
	
	Die Neuzuweisung von `x = x + alpha*p` könnte mittels `operator+=` zwei Konstruktoren einsparen.
	
	Vektor `r` wird nach der Erstellung des temp.-Vektors `r_new` lediglich noch einmal verwendet, inform des Skalarprodukts mit sich selbst in Zeile 27. Anstatt `r_new` als temporären Vektor zu verwenden, könnte man `double old_r_dot = r.dot(r)` berechnen, und dann `r -= alpha * (A*p)` berechnen. Für Vector die Zuweisungen `auto r_new = ...` und `r = ...`, würde je ein Konstruktor gespart. Außerdem wird `r.dot(r)` zweimal verwendet, man könnte als mit einer einmaligen Durchführung und einer lokalen Variable eine Operation sparen.
	
	Zuletzt kommt hinzu, dass der Vector `V x` zunächst mit einer festen Größe initialisiert wird, und dann nochmal allen Werten der `double 0.` zugewiesen wird. Dies ist in unserer Anwendung redundant, da `Vector` intern mit `std::vector` funktioniert, und bei der Initialisierung eines Vektors mit Länge != 0 alle Werte standardmäßig auf `0.` (bei `std::vector<double>`) gesetzt werden.
	
	Damit komme ich nach kurzem Zählen auf 4 redundante Kontruktoren für die Verwendungen der `.dot()` Methode, 3\*2 für die +/- Operatoren, 2 für die beiden Verwendung von `double*Vector`, 2 für die Erstellungen/Zuweisungen von `r_new` und `r`, sowie zwei für `x = x + ...` anstelle von `x += ...`, und zwei Matrix-Vektor-Multiplikationen auf Umwegen mit jeweils neu konstruiertem temporären Vektor anstelle einer lokalen Variable und einmaliger Ausführung pro Schleife.
	
	Damit komme ich PRO SCHLEIFENDURCHLAUF auf 6+2+4 = 12 redundanten Konstruktoren, resultierend allein aus der `Vector`-Klasse, sowie zudem 2 redundanten Berechnungen von Skalarprodukten, und 2+2+2 = 6 redundante Konstuktoren aus den ineffizienten Zuweisungen und einer redundanten Matrix-Vektor-Mult. in der Implementierung von `cg.h`. 
	
	
- 3: Wie bereits erwähnt, bin ich bereits in 2. über das Ziel hinaus geschossen. Nach Änderungen im Code für die `Vector` Klasse sind zwar einige Redundanzen und Ineffizienzen behoben, aber es bleiben nach wie vor die redundanten Aufrufe aus der Implementierung von `cg.h` bestehen, nämlich 2 redundante Berechnungen von Skalarprodukten, und 2+2 = 4 redundante Konstuktoren aus den ineffizienten Zuweisungen, sowie zwei Konstruktoren pro Iteration für die Matrix-Vektor-Multiplikation auf Umwegen.

	Zudem ist mir im zweiten Lesen aufgefallen, dass `x = 0.` bewirkt, dass in der folgenden Zuweisung `V r = y - A*x` die Matrix-Vektor-Multiplikation einen 0-Vektor ergibt, i.e. `V r = y - 0 = y`, und folglich `V p = y`. Die Multiplikation kann man sich somit sparen.

	Diese Ineffizienzen lassen sich beheben durch:

	- Ersetzen von `x = x + ...` durch `x += ...`;
	- Ersetzen von `r_new = r - ...` durch `r -= ...` und eliminieren von `r_new`;
	- Folglich keine Neuzuweisung von `r` zum Ende der Schleife, bereits geschehen;
	- Einführen einer lokalen Variable `double old_p_dot = r.dot(r)`;
	- Einführen einer `Vector mv_res` außerhalb der Schleife, um `A.mv(p, mv_res)` nutzen zu können;
	- Nutzen von `mv_res` anstelle von redundanter Multiplikation.

## Aufgabe 2 (SFNINAE)
Erweitern Sie ihre `Polynom` Klasse um eine Funktion für den `+=` Operator, die nur dann kompiliert wenn das Polynom
auf der rechten Seite den gleichen Grad oder niedriger hat. Nutzen Sie dafür `std::enable_if` im Rückgabewert (siehe Vorlesungsskript Section 9.3), um die Funktion
aus dem Overload-Set zu entfernen, wenn der Grad des anderen Polynoms größer ist.

## Aufgabe 3 (Template Spezialization)
In `specialization.cc` ist eine templatisierte Funktion `determinante` definiert, die für eine Matrix, gegeben als ein
`std::array<std::array<double, N>, N>` Object, die Determinante berechnet. Im allgemeinen Fall lässt sich diese über eine
LU Zerlegung berechnen. Spezialisieren Sie diese Funktion für 1D, 2D, und 3D.

Optional: Wenn statt `double` ebenfalls ein Template-Parameter benutzt
werden soll, funktioniert der obige Ansatz nicht, da Sie Funktionen
nicht **partiell** spezialisieren können. Wie lässt sich das Problem
umgehen, so dass Sie denn die Funktion spezialisieren für 1D, 2D, 3D
ausspezialisieren können?
