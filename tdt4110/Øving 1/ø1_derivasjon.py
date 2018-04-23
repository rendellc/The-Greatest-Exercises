#program for å derivere demonstrert med sinus-funksjonen

import math

#definerer den deriverte av sinus
def derivasjon(x,h):
    f1 = math.sin(x)
    f2 = math.sin(x+h)
    derivert=(f2-f1)/h
    print("Den deriverte er:",format(derivert,".4f"))
#gir x og h verdier
def main():
    h=float(input("h: "))
    x=float(input("x: "))
    derivasjon(x,h)

main()
