def del_a():
    x = 2
    y = int(input("Skriv inn et tall "))
    z = x // y
    print(z)

def del_b():
    a = 2
    b = 3
    if (b<a or not b%a):
        b = a+b
    else:
        a = a*b 
    print("a: ",a)
    print("b: ",b)

#del d
def func1(a):
    import random
    x = [0 for i in range(a)]
 
    for i in range(a):
        x[i] = random.randint(0,10)
 
    return x
 
def func2(x):
    return sorted(x)
# Dette er en kommentar
tall = int(input("Skriv inn et tall: "))
k = func1(tall)
y = func2(k)
print(x)
print(y)
