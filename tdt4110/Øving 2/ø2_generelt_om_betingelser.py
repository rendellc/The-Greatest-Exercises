
def del_a():
    a=int(input("Hva er a? "))
    b=int(input("Hva er b? "))
    
    if a*b > a+b:
        print("a+b =",a+b, "er minst.")
    elif a*b < a+b:
        print("a*b =",a*b, "er minst.")
    else:
        print("a+b = a*b = ",a*b)

def del_b():
    a=3*4
    b=int(input("Hva er 3 ganger 4? "))

    if a == b:
        print("12 ditt er riktig!")
    elif a != b:
        print(b,"er dessverre feil.")

del_a()
del_b()
