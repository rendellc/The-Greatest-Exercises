#program som returnerer overflatearealet
#til en tetraede med høyde h

#funksjon for overflateareal
def area(h,a):
    
    area=(3**0.5)*a**2
    print(area)

def volum(h,a):
    volum=(2**0.5)*(a**3)/12
    print(volum)

def main():
    h=float(input("h: "))
    a=3*h/(6**0.5)
    area(h,a)
    volum(h,a)
    
main()

    
