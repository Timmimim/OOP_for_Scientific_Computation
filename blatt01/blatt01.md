# Übungszettel 1 - 2020/04/23

Dieser Übungszettel soll vor allem in den Übungsablauf und die Infrastruktur einführen.
Die Verteilung und Abgabe der Übungsaufgaben wird über das GitLab des ZIVs organisiert.
Zur Kommunikation haben wir im Mattermost ein Team erstellt.
Die Bearbeitung der Übungsaufgaben soll in **Dreiergruppen** erfolgen.

## Aufgabe 0 (Gitlab und Mattermost)

- :pencil: 0.0: Gehen Sie auf https://zivmattermost.uni-muenster.de und loggen Sie
 sich ein.

- :pencil: 0.1: Schreiben Sie eine private Nachricht an Nils-Arne Dreier (n_drei02).
Falls Sie Wünsche für Ihre Gruppenmitglieder haben, teilen Sie diese
bitte dort mit. Anderenfalls werden die Gruppen zufällig eingeteilt.

Wir fügen Sie dann dem Mattermost-Team hinzu.
Sobald sich alle Gruppenmitglieder gemeldet haben, erstellen wir für
Sie ein GitLab Repository in dem Sie Ihre Übungen bearbeiten sollen.

Weitere Informationen zu Mattermost finden Sie hier:
- https://www.uni-muenster.de/IT/services/kommunikation/chat/
- https://docs.mattermost.com/guides/user.html

## Aufgabe 1 (Arbeiten mit Git)
Für die Bearbeitung der Aufgaben müssen Sie mit Git umgehen können.
- :pencil: 1.0: Machen Sie sich mit Git vertraut.
Sie können Git direkt aus Visual Studio Code steuern. Hier gibt es
ein Einführungsvideo:
https://code.visualstudio.com/docs/introvideos/versioncontrol

- :pencil: 1.1: Klonen Sie das für Sie erstellte Repository auf Ihrem Rechner.

- :pencil: 1.2: Erstellen Sie einen Branch, nennen Sie ihn z.B. "B1A1_Gruppenmitglieder"

- :pencil: 1.3: Im Stammverzeichnis finden Sie eine Datei `Team.md`. Tragen Sie dort die
  Namen der Gruppenmitglieder ein.
  
- :pencil: 1.4: Erstellen Sie einen Commit, der die Änderungen
  enthält. Wählen Sie eine aussagekäftige Commit-Message.

- :pencil: 1.5: *Pushen* Sie den Branch auf das GitLab.

- :pencil: 1.6: Erstellen Sie einen *Merge Request* im GitLab, um den Branch nach "master" zu mergen.

In dem Merge Request erhalten Sie Feedback von Ihrem
Übungsgruppenleiter.
Der Übungsgruppenleiter wird diesen Merge Request begutachten,
ggf. kommentieren und mergen.

Weitere Informationen zum Arbeiten mit Git und GitLab bekommen Sie hier:
- https://git-scm.com/docs
- https://docs.gitlab.com/ee/gitlab-basics/

## Exercise 2 (Power-Method) - 2 Bonuspunkte

Schreiben Sie ein Programm in python, das für eine gegebene positiv definite
Matrix $`A\in \mathbb{R}^{n\times n}`$ den größten Eigenwert 
$`\sigma > 0`$ mit zugehörigem Eigenvektor $`r\in \mathbb{R}^n`$ näherungsweise
bestimmt. Verwenden Sie dazu die iterative Potenz-Methode zur Bestimmung
des größten Eigenvektors:

- Sei ein zufälliger Startvektor $`r^{(0)}\in\mathbb{R}^n`$ gegeben,
  welcher nicht im Kern von $`A`$ liegt ($`Ar^{(0)} \neq 0`$).

- Für $`n > 0`$ ist in jedem Iterationsschritt die neue Annäherung
  durch $`r^{(n)}:=\frac{Ar^{(n−1)}}{\|Ar^{(n−1)}\|}`$ gegeben, wobei $`\|v\|^2:=\sum_{i=1}^n v_i^2`$ die
  euklidische Norm von $`v\in \mathbb{R}^n`$ sei.

Eine Approximation des zugehörigen Eigenwertes ist durch den
Rayleigh-Quotienten $`\sigma(A,r) :=\langle r,Ar\rangle\langle r,r\rangle`$
gegeben. Gehen Sie dazu in folgenden Schritten vor: 
- 2.0: :pencil: Schreiben Sie eine Funktion `rayleigh_quotient(A, r)`, welche den
  Rayleigh-Quotienten $`\sigma(A,r)`$ berechnet und zurück gibt.
- 2.1: :pencil: Schreiben Sie eine Funktion `find_initial_value(A)`, welche zu $`A`$
  einen geeigneten Startwert $`r^{(0)}`$ findet und zurück
  gibt. Hinweis: Suchen Sie dazu im `numpy.random` Modul eine geeignete
  Funktion, die einen zufälligen Vektor passender Größe
  erstellt.
- 2.2: :pencil: Schreiben Sie eine Funktion `power_method(A, n)`, welches die
  Approximation des Eigenvektors $`r^{(n)}`$ iterativ bestimmt und in jedem
  Schritt den Rayleigh-Quotienten $`\sigma(A,r^{(n)})`$ ausgibt.
- 2.3: :pencil: Schreiben Sie eine Funktion `test(A, r, sigma)`, welche den
  Approximationsfehler $`Ar−\sigma r`$ ausgibt. Testen Sie ihr Programm
  für die folgenden Matrizen mit $`n= 20`$ Iterationen.

```math
    B = \begin{pmatrix}
        3&0&0\\
        0&1&0\\
        0&0&1
    \end{pmatrix}\quad
    C = \begin{pmatrix}
        4&-1&-1\\
        0.5&2&-1\\
        0&0&1
    \end{pmatrix}
```
