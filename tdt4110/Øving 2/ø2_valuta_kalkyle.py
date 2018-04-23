#program som tar inn hvor mye penger som skal veksles,
#om det skjer på en flyplass eller bank
#om det skal skje nå eller senere

#liste over kurser
def nå_kurs():
    if kurs == "euro":
        return 8.7
    elif kurs == "gbp":
        return 11.9
    elif kurs == "rub":
        return 0.14
    
def senere_kurs():
    if kurs == "euro":
        return 9.1
    elif kurs == "gbp":
        return 12.5
    else:
        return 0.15 
    
#få hvor mye penger som skal veksles
nok_penger = float(input("Hvor mange kroner ønsker du å veksle? "))

#velg valuta
print('Du kan veksle til "euro", "gbp" eller "rub".')
kurs = input("Skriv inn valutaen du vil bruke: ")

#velg bank eller flyplass
print("Du kan veksle ved flyplassen eller banken.")
print("Flyplassen tar 10% i vekslingsgebyr, mens banken tar 5%")
sted = input('Vil du veksle på "flyplass" eller "bank"? ')

#velg tidspunkt
tidspunkt = input('Vil du veksle "nå" eller "senere"? ')

#beregn nok_penger i valuta
    #hent kursen (tidspunkt og valuta)
if tidspunkt == "nå":
    #beregn hvor mye penger man får
    if sted == "bank":
        vekslet_penger = (nok_penger/nå_kurs())*0.95
    else:
        vekslet_penger = (nok_penger/nå_kurs())*0.90
elif tidspunkt == "senere":
    if sted == "bank":
        vekslet_penger = (nok_penger/senere_kurs())*0.95
    else:
        vekslet_penger = (nok_penger/senere_kurs())*0.90

print("Hvis du veksler", nok_penger, "NOK vil det gi deg \n",\
      format(vekslet_penger, ".2f"), kurs, "når du veksler på",sted)
