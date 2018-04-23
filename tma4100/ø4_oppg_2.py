import math

a_1 = 1

def a(n):
	a_i = a_1
	for i in range(n):
		a_i = (1+2*a_i)**0.5
	return a_i

print(a(10),2**0.5+1, )
