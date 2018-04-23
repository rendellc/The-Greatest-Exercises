def fibonacci():
    f_k2 = 0
    f_k1 = 1
    sum_fib = 0
    n = int(input("Hvor mange fibonacci-tall ønsker du? "))
    if n > 0:
        print("Fibonacci-tall:", 0, "Summen til nå er", 0)
    for i in range(n):
        f_k = f_k1 + f_k2   #regner ut neste
        f_k2 = f_k1
        f_k1 = f_k
        sum_fib = sum_fib + f_k
        print("Fibonacci-tall:", f_k, "Summen til nå er", sum_fib)

def fibonacci_liste():
    n = int(input("Hvor mange fibonacci-tall ønsker du? "))
    print("Fibonacci-tall \tSummen   ")
    print("----------------------------")
    f_k2 = 0
    f_k1 = 1
    sum_fib = 0
    for i in range(n):
        f_k = f_k1 + f_k2   #regner ut neste
        f_k2 = f_k1
        f_k1 = f_k
        sum_fib = sum_fib + f_k
        print(f_k,"\t\t",sum_fib)

#fibonacci()
fibonacci_liste()
