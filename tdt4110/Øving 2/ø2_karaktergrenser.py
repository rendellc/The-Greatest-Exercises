#program som tar inn karakterpoeng (0-100) og returnerer karakter (A-F)
#får poeng fra bruker

def main():
    poeng=float(input("Poeng: "))

    #Regner karakter og tester etter feil
    if poeng%1 != 0 or poeng <= 0:
        print("Poeng må være positivt heltall.")
    elif poeng <= 40:
        print("F")
    elif poeng <= 52:
        print("E")
    elif poeng <= 64:
        print("D")
    elif poeng <= 76:
        print("C")
    elif poeng <= 88:
        print("B")
    elif poeng <= 100:
        print("A")
    elif poeng > 100:
        print("Poeng utenfor skalaen")

main()
main()
main()

input()
