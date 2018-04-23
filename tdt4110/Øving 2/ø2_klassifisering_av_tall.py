#klassifiserer x med funksjonene
def wholeNumber(x):
    if x % 1 != 0:
        return 0
    else:
        return 1

def evenNumber(x):
    if x % 2 != 0:
        return 0
    else:
        return 1
    
def posNumber(x):
    if x > 0:
        return 1
    else:
        return 0

#sammenlign x med y
def compareNr(x,y):
    if not x < y:
        if not x > y:
            return True
        else:
            return False
    else:
        return False

def main():
    x = float(input("Oppgi tall: "))

    #klassifiser første tall
    if wholeNumber(x) == 1:
        print("Dette er et heltall.")
    if evenNumber(x) == 1:
        print("Dette er et partall.")
    if posNumber(x) == 1:
        print("Dette er et positivt tall.")
    
    y = float(input("Oppgi et til tall: "))

    print("Tallene er like:",compareNr(x,y))
    

main()

        
    
