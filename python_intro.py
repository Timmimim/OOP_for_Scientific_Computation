#definiere Golden Ratio Funktion 
def f(x):
    return x**2 - x - 1

#f ist die Funktion
#a,b die Intervallgrenzen
#n Anzahl Iterationen
def bisection(f,a,b,n):
    #Vorbedingung prüfen
    if f(a)*f(b) > 0:
        print("Vorbedingung für Bisektionsverfahren nicht erfüllt!")
        return None

    #wähle intervallmitte
    c = (a+b)/2
    
    #simple Fälle (exakte Lösung bzw gewünschte Genauigkeit erreicht)
    if f(c) == 0 or n-1 < 0: return c

    #Berechne Wert für beide Teilintervalle
    if f(a)*f(c) < 0: return bisection(f,a,c,n-1)
    elif f(c)*f(b) < 0: return bisection(f,c,b,n-1)

# eventuell Liste zurückgeben? Falls mehr als eine Nullstelle.

if __name__ == '__main__':
    print("Iteration 10: " + str(bisection(f,1,2,10)))
    print("Iteration 25: " + str(bisection(f,1,2,25)))
    print("Iteration 50: " + str(bisection(f,1,2,50)))
    print("Iteration 100: " + str(bisection(f,1,2,100)))
    print("Fehler: " + str(bisection(f,2,4,10)))