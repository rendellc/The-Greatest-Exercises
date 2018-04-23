import math

def integrasjon(func, a, b, N):
	h = (b-a)/N
	areal = 0 #akkumuleringsvariabel
	for i in range(N+1):
		areal += func(i*h+h/2+a)*h
	return areal

def trapesmetoden(func, a, b, N):
	h = (b-a)/N
	areal = 0 #akkumuleringsvariabel
	for i in range(N+1):
		areal += 0.5*h*(func(h*i+a)+func(h*(i-1)+a))
	return areal

def simpsons_metode(func, a, b, N):
	if N % 2 == 0:
		h = (b-a)/N
		areal = func(a) #første ledd i summen
		for i in range(1, N+1):
			if i % 2 == 0:
				areal += 2*func(h*i+a)
			else: 
				areal += 4*func(h*i+a)
		areal = areal*h/3
		return areal
	else:
		print("N må være partall")

#d)
print(integrasjon(math.sin,0,math.pi,100))
print(trapesmetoden(math.sin,0,math.pi,100))
print(simpsons_metode(math.sin,0,math.pi,100))
print("\n")

#e)
def g(x):
	return math.exp(-x**2)

print('1. ordens: ', integrasjon(g, -1, 1, 100))
print('Trapesmetoden: ', trapesmetoden(g, -1, 1, 100))
print('Simpsons metode: ', simpsons_metode(g, -1, 1, 100))
#simpsons metode gir minst avvik
