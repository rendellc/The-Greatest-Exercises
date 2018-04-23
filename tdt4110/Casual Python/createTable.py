def createTable(number, size):
	return [[number for _ in range(size)] for __ in range(size)]

A = createTable(0,3)

def fillTable(table):
	number = 2
	for row in range(len(table)):
		for col in range(len(table[row])):
			table[row][col] = number
			number += 2
	return table

A = fillTable(A)

def printTable(table):
	for row in range(len(table)):
		s = ''
		for col in range(len(table[row])):
			s += str(table[row][col]).rjust(5)
		print(s)

printTable(A)
