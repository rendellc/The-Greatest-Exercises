def seperate(numbers, threshold):
	smaller = []
	larger = []
	[smaller.append(i) for i in numbers if i < threshold]
	[larger.append(i) for i in numbers if i >= threshold]
	return smaller, larger


def multiplication_table(n):
	return [[k*i for i in range(1, n+1)] for k in range(1, n+1)]

def print_mult_table(table):
	for row in table:
		for nr in row:
			print(nr,'		',end='')
		print('\n', end='')

table = multiplication_table(5)
print(table)
print_mult_table(table)
