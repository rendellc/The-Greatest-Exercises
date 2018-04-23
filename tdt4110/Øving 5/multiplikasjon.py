def a_mult(tol):
    n = 1
    prod = 1            #null iterasjoner
    delta_prod = 1      #endring i produktet, n=1
    while delta_prod > tol:
        prod = prod*(1+1/n**2)
        delta_prod = prod*(1+1/n**2) - prod
        n += 1
    print("For aa ha en tolerense pa", tol, "trengs", n, "iterasjoner, og da blir produktet", prod)
    
a_mult(0.1)