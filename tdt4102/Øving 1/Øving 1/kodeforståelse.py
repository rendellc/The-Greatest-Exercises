def isFibonacciNumber(n):
    a = 0
    b = 1
    while b < n:
        temp = b
        b = a + b
        a = temp
    return b==n
