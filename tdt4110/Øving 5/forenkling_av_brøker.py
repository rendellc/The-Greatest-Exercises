def gcd(a,b):
    while b != 0:
        gammel_b = b
        b = a%b
        a = gammel_b
    return a

def reduce_fraction(x,y):
    if x > 0 and y > 0:
        return x/gcd(x,y), y/gcd(x,y)
    else:
        print("Trenger positive tall")
    
def main(a,b):
    teller = int(reduce_fraction(a,b)[0])
    nevner = int(reduce_fraction(a,b)[1])
    print("For a = ",a ,"; og b = ", b ,"; er a/b lik: ", teller,"/",nevner, sep="") 

main(5,10)
main(4,2)
main(648718,3632)

#input("Trykk enter for å avslutte")
