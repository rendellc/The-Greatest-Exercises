#listene som oppgaven tar utgangspunkt i
fornavn = ['johan', 'eli', 'mats', 'lene', 'simon','inger', 'henrik', 'mari', 'per']
etternavn = ['Hag', 'Hag', 'Basmestad', 'Grimlavaag', 'Kleivesund','Fintenes', 'Svalesand', 'Molteby', 'Hegesen']

def a_forlengs():
    for x in range(9):
        print(fornavn[x], etternavn[x])
        

def b_for_bak():
    for x in range(9):
        print(fornavn[x], etternavn[-x-1])

print("Oppgave a")
a_forlengs()
print("\nOppgave b")
b_for_bak()

#simon Kleivesund er likt i begge fordi han er i midten
#og listen inneholder et oddetall elementer.


def c1_stor_forbokstav():
    for x in range(9):
        F_navn = fornavn[x]                     #henter fornavnet
        F_navn = F_navn[0:1].upper() + F_navn[1:len(F_navn)]
        print(F_navn,etternavn[x])

def c2_stor_forbokstav():
    for x in range(9):
        F_navn = fornavn[x]                     #henter fornavnet
        F_navn = F_navn[0:1].upper() + F_navn[1:len(F_navn)]
        print(F_navn,etternavn[-x-1])

print("\nOppgave c1")
c1_stor_forbokstav()

print("\nOppgave c2")
c2_stor_forbokstav()
