debug = True

def mult(x,y):
    if debug:
        print("Verdiene som multipliseres er",x , "og", y)
    if type(x) == int and type(y) == int:
        print(x*y)
    else:
        print("Verdiene er ikke heltall")

#tester forskjellige inputs
mult(14,76)
mult(14,13)
mult(15,1)
mult(121,"nittito")
mult(14.2453,76)
