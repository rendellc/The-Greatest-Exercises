
def a_sum():
    N = 5       #antall ledd
    summen = 0  #summen av 0 ledd
    for i in range(1,N):
        x_i = 1/i**2            #i-ende leddet
        summen = summen + x_i   #summen med det i-ende leddet
    print(summen)

def b_sum():
    tol = 0.00000000000000001     #feiltoleranse
    x_i = 1         #nullte leddet
    i = 1           #ledd-teller
    summen = 1      #summen av 1 ledd    
    while x_i - 1/(i+1)**2 > tol:
        x_i = 1/(i+1)**2
        summen = summen + x_i
        i += 1
    print("Summen er ",summen," og antall ledd er ", i)

a_sum()

b_sum()
