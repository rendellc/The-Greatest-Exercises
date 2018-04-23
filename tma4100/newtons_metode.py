import math

f = lambda x: x**2-2*math.cos(x)
f_derivative = lambda x: 2*x+2*math.sin(x)


def newtons_metode(f, f_derivative, x_0, epsilon=0.0001):
	x_n = x_0
	i = 0
	while math.fabs(f(x_n))>epsilon:
		x_n = x_n - f(x_n)/f_derivative(x_n)
		i += 1
		if i > 1000:
			break
	return x_n, i

print(newtons_metode(f, f_derivative, 2))