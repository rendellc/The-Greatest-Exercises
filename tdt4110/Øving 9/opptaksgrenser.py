poenggrense_fil = open('poenggrenser_2011.csv','r')

def antall_alle():
	poenggrense_fil.seek(0) #sørger for å starte på første rad i filen
	antall = 0 #teller
	for line in poenggrense_fil:
		if 'Alle' in line:
			antall += 1
	print(antall) #printer ikke ut i printen under, bug?
	return antall

print('Tok inn alle søkere:', antall_alle())

def average_poenggrense():
	poenggrense_fil.seek(0) #sørger for å starte på første rad i filen
	poeng = 0 #poengteller
	antall = 0
	for line in poenggrense_fil:
		if 'Alle' not in line:
			tall = line
			i1 = tall.find(',')
			i2 = tall.find('\n')
			poeng += float(line[(i1+1):i2])
			antall += 1
	return poeng/antall #gjennomsnittet

print('Gjennomsnittlig opptaksgrense:', average_poenggrense())

def lavest_poenggrense():
	poenggrense_fil.seek(0) #sørger for å starte på første rad i filen
	lavest_sjekk = float('inf')
	for line in poenggrense_fil:
		if 'Alle' not in line:
			tall = line
			i1 = tall.find(',')
			i2 = tall.find('\n')
			poeng = float(line[(i1+1):i2])
			if poeng < lavest_sjekk:
				lavest_sjekk = poeng
				lavest_studie = line[:i1]
	return lavest_studie, lavest_sjekk

print(lavest_poenggrense())

poenggrense_fil.close()