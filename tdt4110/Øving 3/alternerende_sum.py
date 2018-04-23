import math

def a_alt_sum():
    n = int(input("Hvor mange ledd skal legges sammen? "))
    summen = 0      #n = 0
    for k in range(1,n+1):
        summen = summen + pow(-1,k+1)*k**2
    print(summen)



def b_alt_sum():
    n = int(input("Hva skal summen være mindre enn? "))
    summen = 0
    k = 1
    cont = True
    while cont:
        if summen + pow(-1,k+1)*k**2 < n:
            summen = summen + pow(-1,k+1)*k**2
            k += 1
        else:
            cont = False
    print("Antall ledd ble:", k-1, "\nSummen ble:",summen)

b_alt_sum()
print("\n")
a_alt_sum()
