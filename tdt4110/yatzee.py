__author__ = 'Kristoffer'
# -*- coding: utf-8 -*-
import random

# Returnerer et kast
def startKast():
    mitt_kast = []
    for i in range(5):
        mitt_kast.append(random.randint(1,6))
    return mitt_kast

#Sjekker en hånd for antall av et bestemt tall
def sjekk(hand, tall):
    antall = 0
    for i in hand:
        if i==tall:
            antall += 1
    return  antall

#Lagre highscore
################################
#         Oppgave 2.3          #
#¤##############################
#Lag en funksjon som lagrer navnet til spilleren og poengene han/hun fikk etter endt spill. Lag en fil kalt «highscore.txt»
# file = open(highscore.txt,"a") - for å opne en fil og legge til nytt innhold
#def saveScore(score):


#Sjekker en hånd for antall like og returnerer poeng
def like(hand,antall):
    if sjekk(hand,6)>=antall:
        return 6*antall
    if sjekk(hand,5)>=antall:
        return 5*antall
    if sjekk(hand,4)>=antall:
        return 4*antall
    if sjekk(hand,3)>=antall:
        return 3*antall
    if sjekk(hand,2)>=antall:
        return 2*antall
    if sjekk(hand,1)>=antall:
        return 1*antall
    return 0

# triller en terning i en bestemt posisjon på ny
def nyTerning(liste,posisjon):
    utListe = liste
    utListe[posisjon] = random.randint(1,6)
    return utListe

# Sjekker om spilleren får bonus eller ikke
def bonus(poeng):
    if poeng >= 42:
        print("Du har",poeng,"og får 50 bonuspoeng!")
        return 50
    print("Du har",poeng,"det er ikke nok til å få bonus :(")
    return 0

# henter en liste over hvilke terninger som skal triller på ny (indeksen) (1-indeksert)
################################
#         Oppgave 2.2          #
################################
# Gjør denne funksjonen foolproof, slik at programmet ikkje krasjer med feil input
#Prøve a ta int() av en bokstav (ValueError) (try/except)
#Prøve å hente en index som ikke finnes (IndexError) (if/else)
def nytt_kast_indexer():
    text = input("Hvilke terninger vil du kaste på ny? (separer med komma uten mellomrom (1-indexert) \n")
    if not text:
        return []
    if text == "alle":
        return [0,1,2,3,4]
    # start her:
    #try:
    indekser = text.split(",")
    utListe = []
    for i in indekser:
        utListe.append(int(i)-1) #NB: endrer tilbake til 0-index
    #except ValueError:
    return utListe

# alle terningene som ligger på indeksene trilles på ny
def nytt_kast(innListe,indekser):
    utListe = innListe
    for i in indekser:
        utListe = nyTerning(utListe,i)
    return utListe

# kaster terningene tre ganger og spør om rerolls mellom hver gang
def kast():
    mitt_kast = startKast()
    print("Du kastet:")
    print(mitt_kast)

    #verdi versjon
    #verdier = nytt_kast_value_indexer(mitt_kast)
    verdier = nytt_kast_indexer()
    mitt_kast = nytt_kast(mitt_kast,verdier)
    print("Ditt andre kast ble:")
    print(mitt_kast)

    #verdi versjon
    #verdier = nytt_kast_value_indexer(mitt_kast)
    verdier = nytt_kast_indexer()
    mitt_kast = nytt_kast(mitt_kast,verdier)
    print("Ditt tredje kast ble:")
    print(mitt_kast)
    return mitt_kast

# brukes for i øverste del av yatzy spillet
def faseEn(kast,verdi):
    poeng = 0
    antall = sjekk(kast,verdi)
    poeng += verdi * antall
    print("Du fikk",poeng,"poeng får å ha",antall,"av",verdi)
    return poeng

# gir poeng for to par
def toPar(hand):
    etPar = like(hand,2)
    if etPar > 0:
        verdi = etPar/2
        hand.pop(hand.index(verdi))
        hand.pop(hand.index(verdi))
        andrePar = like(hand,2)
        if etPar and andrePar and (etPar is not andrePar):
            return etPar+andrePar
    return 0

################################
#         Oppgave 2.4          #
#¤##############################
"""
Lag funksjonen house som har inn-parameteren dice som er en liste med fem elementer med
verdier mellom 1 og 6. Funksjonen skal returnere summen av alle terningene hvis verdiene i dice
har både 3 like og ett par (f.eks. 4,4,4,2,2 eller 1,1,6,6,6), hvis ikke skal verdien 0 returneres.
Funksjonen skal også returnere verdien 0 hvis alle elementene i dice er like.
"""
# Kan f.ek. sjekke for tre like (vha. funksjonen like(kast,antall)), fjerne de terningene fra kastet,
# så sjekke for to like
# Evt. sortere og sjekke om 1-2 og 3-4-5 har samme verdi, eller om 1-2-3 og 4-5 har samme verdi
#def hus(hand):




################################
#         Oppgave 2.5          #
#¤##############################
"""
Lag funksjonen straight som har inn-parameteren dice som er en liste med fem elementer med
verdier mellom 1 og 6. Funksjonen skal undersøke om listen representerer en liten eller stor straight.
Følgende skal returneres:
For en liten straight (liste som inneholder tallene 1,2,3,4,5) skal funksjonen returnere tallet 15. For en
stor straight (liste som inneholder tallene 2,3,4,5,6) skal funksjonen returnere tallet 20. For en liste
som er verken liten eller stor straight skal funksjonen returnere tallet 0
"""
# Kan f.ek. sortere kastet og sjekke at differansen mellom alle nabo-terninget er 1

# gir poeng for straight
#def straight(kast):

#def litenStraight(kast):
#def storStraight(kast):


################################
#         Oppgave 2.6          #
################################
# finn liten eller stor straight vha. dictionary
def straight(kast,størrelse):
    dict = {}
    dict["liten"] = [1,2,3,4,5]
    dict["stor"] = [2,3,4,5,6]




# printer en matrix nedover i stedet for bortover
def printMatrix(matrix):
    for array in matrix:
        print(array)

# main funksjonen der selve spillet kjøres
def main():
    poeng = 0
    # kommenter ut dette for raskere testing

    for i in range(1,7):
        print("\nDu vil nå har flest mulig av",i)
        mitt_kast = kast()
        poeng += faseEn(mitt_kast,i)
    poeng += bonus(poeng)

    print("Du vil ha ett par:")
    mitt_kast = kast()
    tempPoeng = like(mitt_kast,2)
    poeng += tempPoeng
    print("Du fikk",tempPoeng,"poeng for ett par")

    print("Du vil ha to par:")
    mitt_kast = kast()
    #tempPoeng = toPar(mitt_kast)
    tempPoeng = toPar(mitt_kast)
    poeng += tempPoeng
    print("Du fikk",tempPoeng,"poeng for to par")

    print("Du vil ha tre like:")
    mitt_kast = kast()
    tempPoeng = like(mitt_kast,3)
    poeng += tempPoeng
    print("Du fikk",tempPoeng,"poeng for tre like")

    print("Du vil ha fire like:")
    mitt_kast = kast()
    tempPoeng = like(mitt_kast,4)
    poeng += tempPoeng
    print("Du fikk",tempPoeng,"poeng for fire like")

    # slutt kommentar her for raskere testing

    """ Oppgave 2.4
    print("Du vil ha et hus (3+2 like):")
    mitt_kast = kast()
    #tempPoeng = toPar(mitt_kast)
    tempPoeng = hus(mitt_kast)
    poeng += tempPoeng
    print("Du fikk",tempPoeng,"poeng for hus")
    """

    """ Oppgave 2.5/2.6
    print("Du vil ha liten straight:")
    #mitt_kast = kast()
    tempPoeng = straight([2,5,4,3,1],"liten")
    poeng += tempPoeng
    print("Du fikk",tempPoeng,"poeng for liten straight")

    print("Du vil ha stor straight:")
    #mitt_kast = kast()
    tempPoeng = straight([2,5,4,3,6],"stor")
    poeng += tempPoeng
    print("Du fikk",tempPoeng,"poeng for stor straight")
    """

    """ Oppgave 2.3
    saveScore(poeng)
    """
main()