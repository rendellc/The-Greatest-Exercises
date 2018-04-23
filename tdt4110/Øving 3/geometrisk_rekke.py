r = 0.9             #grunntallet r i rekkene

def a_georekke():
    n = 100         #antall ledd i rekken              
    i = 0           #tellevariabel
    summen = 0      #summen av 0 ledd
    while i <= n:
        summen = summen + r**i
        i += 1
    print("Den geometriske rekken gir",summen, "etter",n,"iterasjoner.\n")

def b_georekke():
    #definerer variablene
    tol = 0.001     #tolleranse
    i = 0           #teller
    summen = 0
    
    #regner ut summen
    while r**(i-1) > tol:       #differansen vil være størrelsen av det siste leddet
        summen = summen + r**i
        i += 1
    print("Summen ble:",summen, "og antall iterasjoner var ",i-1)
    
    #tester de ulike verdiene r kan være
    if r > -1 and r < 1:        
        limit = 1/(1-r)
        diff = limit - summen
        print("Differansen mellom grenseverdien og summen er\n", diff)
    else:
        print("Differansen er uendelig")

a_georekke()

if r > -1 and r < 1:
    b_georekke()
