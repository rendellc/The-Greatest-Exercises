
def pascalsTrekant(n):
	trekant = []
	trekant.append([1]) #første rad
	for i in range(n): #går gjennom radene, 
		rad = []
		rad.append(1)
		if i>=1:
			for m in range(len(trekant[i])-1):
				tall = trekant[i][m]+trekant[i][m+1]
				rad.append(tall)
		rad.append(1)
		trekant.append(rad)
	return trekant



def polynom_utdvidelse(n):
	koefisienter = pascalsTrekant(n)[~0] #siste rad i trekanten
	for k in range(len(koefisienter)):
		if k <= n-1:
			print(koefisienter[k],'y^(',n-k,')*x^(',k,')',sep='',end=' + ')
		else:
			print(koefisienter[k],'y^(',k,')*x^(',n-k,')',sep='')

print(pascalsTrekant(4)[~0])
polynom_utdvidelse(4)