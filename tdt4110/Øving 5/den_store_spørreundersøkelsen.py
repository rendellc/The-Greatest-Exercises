fortsett = True

#startverdier
antall_kvinner = 0
antall_menn = 0
antall_fag = 0
antall_ITGK = 0
antall_timer_lekser = 0

def avslutt_undersøkelse(arg):
    if str(arg) == "hade":
        global fortsett
        fortsett = False

def oppdater_global(kjonn, alder, fag, variabelmedlem_ITGK, timer_lekser):
    global antall_kvinner
    global antall_menn
    global antall_fag
    global antall_ITGK
    global antall_timer_lekser

    if kjonn == "m":
        antall_menn += 1
    elif kjonn == "f":
        antall_kvinner += 1

    if fag == "ja":
        antall_fag += 1
        antall_timer_lekser += timer_lekser
    
    if variabelmedlem_ITGK == "ja":
        antall_ITGK += 1
    

def main():
    while fortsett == True:
        kjonn = input("Mann eller kvinne (m/f)? ")
        avslutt_undersøkelse(kjonn)
        if fortsett == False: continue
        
        alder = input("Alder: ")
        avslutt_undersøkelse(alder)
        if fortsett == False: continue
        alder = int(alder)
        if not alder >= 16 and alder <= 25:
            print("Du er utenfor tiltenkt gruppe")
            continue
        
        fag = input("Tar du fag (ja/nei)? ")
        while fag != "ja" and fag != "nei" and fag != "hade":
            print("Ugyldig input")
            fag = input("Tar du fag (ja/nei)? ")
        avslutt_undersøkelse(fag)
        if fortsett == False: continue

        if fag == "ja":
            if alder < 22:
                variabelmedlem_ITGK = input("Tar du ITGK? ")
            else:
                variabelmedlem_ITGK = input("Tar virkelig du ITGK? ")

        if fag == "nei":
            timer_lekser = 0
            variabelmedlem_ITGK = "nei"
        
        avslutt_undersøkelse(variabelmedlem_ITGK)
        if fortsett == False: continue

        if fag == "ja":
            timer_lekser = input("Hvor mange timer bruker du på lekser daglig? ")
            avslutt_undersøkelse(timer_lekser)
            if fortsett == False: continue
            timer_lekser = int(timer_lekser)

        if fag == "nei":
            timer_lekser = 0
            variabelmedlem_ITGK = "nei"

        oppdater_global(kjonn, alder, fag, variabelmedlem_ITGK, timer_lekser)        

    print("\n", antall_menn, "menn og", antall_kvinner, "kvinner deltok.")
    print(antall_fag, "tok fag, og av dem tok", antall_ITGK, "ITGK.")
    print("De brukte i snitt", antall_timer_lekser/(antall_kvinner+antall_menn))
    print("timer daglig på lekser.")

main()


#avsluttende for å vente
input('Trykk "enter" for å gå videre')
