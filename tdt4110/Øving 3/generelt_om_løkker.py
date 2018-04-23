def null_til_hundre():
    x = 0
    for i in range(1,101):
        x = x + i
    print(x)

def produkt():
    k = 1
    n = 0
    while k < 1000:
        n += 1
        k *= n
    print("Antall produkter er", n, "og produktet er", k,".")

def spørsmål():
    svar = input("Har dette spørsmålet et svar? ")
    while svar != "Ja" and svar != "ja":
        print("Feil. Prøv igjen.")
        svar = input("Har dette spørsmålet et svar? ")
    print("Riktig")

null_til_hundre()
produkt()
spørsmål()
