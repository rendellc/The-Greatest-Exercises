def delelig(a,b):
    if a % b == 0:
        return True
    else:
        return False

def isprime(a):
    primtall = True
    for b in range(2,a):
        if delelig(a,b) == True:
             primtall = False
             break
    return primtall

def isprime_ver2(a):
    primtall = True
    i = 3
    if a % 2 == 0:
        primtall = False
    else:
        while i <= round(a**0.5+0.5):
            if delelig(a,i) == True:
                primtall = False
                break
            i += 2

    if a == 2: primtall = True
    
    return primtall

for x in range(1,100000):
    if isprime_ver2(x) == True:
        print(x, "er primtall")

#input('trykk "Enter" for å avslutte')