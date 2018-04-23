import math

def dy_maple_test_11_6(x,y):
	return 6*math.sin(x)*math.cos(5*y)

def eulers_method(dy, x_0, y_0, x_n, n):
	h = (x_n-x_0)/n
	print(h)
	y_i = y_0
	x = x_0
	for i in range(n+1):
		#print('x=',x)
		print('y(',x,')= ', y_i, sep='')
		y_i = y_i + h*dy(x,y_i)
		y_i = round(y_i, 10)
		x = round(x_0+i*h, n)

eulers_method(dy_maple_test_11_6, 2, 4, 5, 1000)
