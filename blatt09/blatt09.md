# Übungsblatt 09 - 02. Juli 2020
Bearbeitung bis zum **09. Juli**

## Aufgabe 1 (Sparse Marix*Vector Arithmetische Intensität)
Gegeben sei eine Spare-Matrix `A` im CSR Format der Dimension `NxN` mit `nnz` nicht Null Einträgen. Diese Matrix besteht
aus drei Arrays, `values` enthält die nicht-null Einträge, `colIndex` enthält die dazugehörigen Spaltenindizes und 
`rowStart` gibt den ersten Index im `values` Array der aktuellen Zeile an. Die Sparse Matrix*Vector Operation lässt sich
damit wie folgt berechnen:  
```
for i in 0..N
    y[i] = 0.
    for j in rowStart[i]..rowStart[i+1]
        idx = colIndex[j]
        val = values[j]
        y[i] += val * x[idx]
```
Nehmen Sie an, dass alle die Einträge aller Arrays 8 Byte groß sind (entspricht `double` und `std::size_t`). Zeigen Sie, 
dass die arithmetische Intensität `1/12` entspricht unter angemessenen Vereinfachungen.

## Aufgabe 2 (Roofline Model PCG)
Betrachten Sie folgende Beschreibung des PCG Algorithmus:  
```
r_0 := b - A * x_0  
if r_0 is sufficently small, then return x_0     
z_0 := M^-1 * r_0 
p_0 := z_0 
k := 0   
for k:= 0..maxit
    q_k := A * p_k
    alpha := (r_k^T * z_k) / (p_k^T * q_k)   
    x_k+1 := x_k + alpha * p_k  
    r_k+1 := r_k - alpha * q_k 
    if ||r_0||_2 is sufficiently small, then return x_k+1   
    z_k+1 := M^-1 * r_k+1  
    beta := (z_k+1^T * r_k+1) / (z_k^T * r_k)   
    p_k+1 := z_k+1 + beta * p_k 
```
`A` und `M^-1` werden als Sparse Matrizen der Größe `NxN` betrachtet. Nehmen Sie für die Aufgaben an, dass `A` im 
Durchschnitt `n` und `M^-1` im Schnitt `m` nicht-null Eintrage pro Zeile haben. Sie können davon ausgehen, dass `N` so 
groß ist, dass die Matrizen und alle Vektoren immer aus dem Hauptarbeitsspeicher geladen werden. Als Datentypen werden 
die C++ Typ `double` und `std::size_t` verwendet, d.h. für jeden skalaren Eintrag eines Vektors oder einer Matrix werden
8 Byte transferiert. Im weitern werden zwei Prozessoren mit den folgenden Eigenschaften (auf einen Kern bezogen)
betrachtet:

|          | Skylake Server (2017) | PowerPC 450 (2006) |
|:---------|:----------------------|:-------------------|
| Taktrate | 2.2 GHz/s | 850 MHz/s |
| FLOP/cyle | 32 | 1 |
| Bandbreite | 10 GB/s | 3.7 GB/s |
    
1. Bestimmen Sie die arithmetische Intensitat der einzelnen Schritte einer PCG-Iteration. Fassen Sie dabei Operationen
   ähnlicher Art sinnvoll zusammen.
2. Skizzieren Sie ein Roofline Model für beide Prozessoren und tragen Sie die Teilschritte des PCG mit unterschiedlicher
   arithmetischer Intensitat dort ein.
3. Bestimmen Sie die Laufzeit einer Iteration in Abhangigkeit von `N` und `n, m` für beide Systeme.
