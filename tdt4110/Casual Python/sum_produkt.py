liste = []
for x in range(100):
	for y in range(100):
		if y*x == x+y: liste.append((x,y))

print(liste)
