'''
Oppgave 1
1) a
2) a
3) b
4) a
5) a
6) 
7) c
8) b
9) a
10) b
11) b
12) c
13) a
14) b
15) a
16) d
17) c
18) c
19) a
20)
'''

#Oppgave 2
#a)
def edgeLength(x_1, y_1, x_2, y_2):
	return (((x_1-x_2)**2+(y_1-y_2)**2)**0.5)

#b) 
def circumference(pList):
	length = 0 #akkumuleringsvariabel
	
	if pList % 2 == 0 and len(pList) > 0:
		i = 0 # teller
		while i <= len(pList)-2:
			length  += edgeLength(pList[i], pList[(i+1)], pList[i+2], pList[i+3])
			i += 2
		length += edgeLength(pList[0], pList[1], pList[~0], pLost[~1])
		return length
	else:
		return -1

#c)
def enclosingRectangle(pList):
	x_maks = -float('inf')
	x_min = float('inf')
	y_maks = -float('inf')
	y_min = float('inf')

	for i in range(len(pList)):
		num = pList[i]
		if i%2 == 0:
			if num > y_maks:
				y_maks = num
			if num < y_min:
				y_min = num
		else:
			if num > x_maks:
				x_maks = num
			if num < x_min:
				x_min = num
	return [x_min, x_maks, y_min, y_maks]

#d)
def readPolygonFile(filename):
	with open(filename, 'r') as f:
		pList = []
		for line in f:
			x = line[0]
			y = line[~0]
			pList.append(x)
			pList.append(y)
	return pList


#Oppgave 3

'''
forløp:

n = 4
a = [3,4,6,7]
b = [3,4,7,6]

res = 0
x = 0

a[x] = 3
b[x] = 3
-> res = 1
x = 1
n = 3

a[x] == b[x] = 4
-> res = 2
x = 2
n = 2

a[x] != b[x]
x = 3
n = 1

a[x] != b[x]
x = 4
n = 0

return res (2)
'''

# 2

#b) 
# mystery5 tar inn to lister, a og b, og returner antall like elementer på lik index på de 
# n første indexene

# c) 

# mystery6(3,2) = 2*mystery6(2,2) = 2*2*mystery6(1,2) = 2*2*2*mystery6(0,2) = 2*2*2*1 = 8
# svar = 8

# Oppgave 4

# a)

def check_highscore(points, scores):
	plass = 0 #teller scores over
	
	for name, score in scores:
		if points < score:
			plass += 1
	if plass == 0:
		return -1
	else:
		return plass
	

# b)

def print_highscores(scores):
	print_plass = 1
	while True:
		for name, score in scores:
			plass = check_highscore(score, scores)
			if  plass == print_plass:
				print(str(print_plass).rjust(2), str(name).ljust(20), str(score).rjust(5))
				print_plass += 1
			if plass == -1:
                                pass
