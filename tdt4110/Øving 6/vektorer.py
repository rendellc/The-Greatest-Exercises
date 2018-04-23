def lag_vektor(x,y,z):
    return [x,y,z]

def print_vektor(vec):
    print('Vektor =', vec)

def skalar_mult(vec, c):
    ny_vec = []
    for i in vec: ny_vec.append(i*c)
    return ny_vec

def vektor_lengde(vec):  #skalar_mult() må bli kjørt først
    summen = 0  #akkumuleringsvariabel
    for i in vec: summen += i**2
    return summen**0.5

def dotprodukt(vec1, vec2):
    produkt = vec1[0]*vec2[0]+vec1[1]*vec2[1]+vec1[2]*vec2[2]
    
def main():
    vec1 = lag_vektor(2,3,4)
    print_vektor(vec1)
    
    skalar = 3 #int(input(Skriv inn en skalar: ))
    vec2 = skalar_mult(vec1,skalar)
    print_vektor(vec2)
    
    lengde_vec1 = vektor_lengde(vec1)
    lengde_vec2 = vektor_lengde(vec2)
    
    print('Lengde før skalering:',lengde_vec1)
    print('Lengde etter skalering:', lengde_vec2)
    print('Forholdet mellom vektorene:', lengde_vec2/lengde_vec1)

    dot_vektor = dotprodukt(vec1,vec2)
    print('Indreprokuktet ble: ',dot_vektor)

main()

input()