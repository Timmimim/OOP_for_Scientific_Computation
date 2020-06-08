# Übungsblatt 06 - 08. Juni 2020
Bearbeitung bis zum **15. Juni**

## Aufgabe 1 (Iteratoren)

Sie haben in der Vorlesung Iteratoren kennengelernt. Wir wollen nun
dieses Konzept in dem von Ihnen entwickelten Matrix-Vector Framework
verwenden. Im Repository finden Sie eine Datei
`matrix_iterator.hh`. Sie enthält Klassen die es erlauben über die
Koeffizienten der `Matrix` vom Übungsblatt 3 mithilfe von Iteratoren
zu iterieren.
Machen Sie sich mit dem Inhalt der Datei vertraut, betrachten Sie auch
das Programm `iterator_example.cpp`.
Gleichungsysteme die beim der Diskretisierung von partiellen
Differentialgleichungen vorkommen, sind oft sehr groß es sind aber nur
wenige Einträge nicht-null. Diese Matritzen werden *dünn-besetzt*, bzw. *sparse* genannt.
Für den effizienten Umgang mit solchen Matrizen gibt es spezielle
Formate, wie z.B. das
[CSR-Format](https://en.wikipedia.org/wiki/Sparse_matrix#Compressed_sparse_row_(CSR,_CRS_or_Yale_format)).
Die Datei `csrmatrix.hh` enthält eine einfache Implementierung einer `CSRMatrix`.

1. Um den Umgang mit Iteratoren zu Üben wollen wir ein allgemeines
Matrix-Vector Produkt implementieren. Vervollständingen sie den
`operator*` in der Datei `mv.hh`. Verwenden Sie dabei die Iteratoren aus `matrix_iterator.hh`.

2. Implementieren Sie Iterator und Range Klassen um das
iterieren über eine `CSRMatrix` zu ermöglichen. Dabei soll nur über
nicht-null Einträge iteriert werden. Orientieren Sie sich dabei an den
bereitgestellten Klassen für `Matrix`.

## Aufgabe 2 (Gauss-Seidel)
Ein iteratives Lösungsverfahren für lineare Gleichungssysteme ist das
Gauss-Seidel Verfahren. Dieses nähert sich der Lösung an, indem es
folgende Iterationsvorschritt anwendet:
```math
    x_i^{(k+1)} = \frac{1}{a_{ii}} \left(b_i - \sum_{j=0}^{i-1} a_{ij}x_j^{(k+1)} - \sum_{j=i+1}^{n} a_{ij}x_j^{(k)}\right)
```

- Erstellen Sie eine Klasse `GaussSeidel`, die das Verfahren
  implementiert. Die Klasse soll ein template Argument für den
  verwendeten Matrixtypen erhalten. Verwenden Sie dabei die Iteratoren aus Aufgabe 1.
- Testen Sie das Verfahren an dem Gleichungssystem mit $`100`$ unbekannten und der Systemmatrix
```math
A = \begin{pmatrix}
    2 & -1 & 0 & \cdots & 0\\
    -1 & 2 & -1 & \cdots & 0\\
    & \ddots & \ddots & \ddots & \\
    0 & \cdots & -1 & 2 & -1\\
    0& \cdots & 0 & -1 & 2
\end{pmatrix}
```
und einem geeigneten Vektor für die rechte Seite. Das Testprogramm
soll das System sowohl mit der `CSRMatrix` als auch mit `Matrix`
funktionieren. Vergleichen Sie die Laufzeiten der beiden Fälle.
