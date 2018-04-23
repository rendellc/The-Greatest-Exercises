import math
debug = True


def f(x):
    return (x-12)*math.exp(5*x)-8*(x+2)**2
    
def g(x):
    return -x-2*x**2-5*x**3+6*x**4

def f_derivert(x,h):
    f_derivert = (f(x+0.5*h)-f(x-0.5*h))/h
    return f_derivert

def g_derivert(x,h):
    return (g(x+0.5*h)-g(x-0.5*h))/h

def newton():
    tol = 0.0001  #minst 1568 på f(12)
    h = 0.0001
    n = 0 #iterasjoner
    '''
    #metoden på f
    x_k = 12
    while math.fabs(f(x_k)) > tol:
        x_k1 = x_k - f(x_k)/f_derivert(x_k,h)
        x_k = x_k1
        
        if debug == True:
            n += 1
            print(n, )
    print("f har nullpunkt ved", x_k)
    
    '''
    #metoden på g
    x_k = 1
    while math.fabs(g(x_k)) > tol:
        x_k1 = x_k - g(x_k)/g_derivert(x_k,h)
        x_k = x_k1
    print("g har nullpunkt ved", format(x_k, '.5f')

newton()

