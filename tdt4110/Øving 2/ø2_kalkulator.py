#definerer operasjonsfunksjonene
def pluss():
    print("Svar: ", t1+t2)
def minus():
    print("Svar: ", t1-t2)
def gange():
    print("Svar: ", t1*t2)
def dele():
    if t2 == 0:
        print("Ugyldig tall. Kan ikke dele på 0")
    else:
        print("Svar: ", t1/t2)

def main():
    if operasjon == "pluss":
        pluss()
    elif operasjon == "minus":
        minus()
    elif operasjon == "gange":
        gange()
    elif operasjon == "dele":
        dele()
    else:
        print("Ugyldig operasjonvalg.")

#får input fra brukeren
t1 = float(input("Skriv inn første tall: "))
operasjon = input('Valgene er "pluss", "minus", "gange" og "dele" \nHvilken matematisk operasjon vil du bruke? ')
t2 = float(input("Skriv inn andre tall: "))

main()
