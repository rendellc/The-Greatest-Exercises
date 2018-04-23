def pris(alder):
	pris_tabell = {'Småbarn':'Gratis', 'Barn':20, 'Student':50, 'Voksen':80, 'Honoer':'Gratis'}
	if alder < 5:
		return pris_tabell['Småbarn']
	elif alder <= 20:
		return pris_tabell['Barn']
	elif alder <= 25:
		return pris_tabell['Student']
	elif alder <= 60:
		return pris_tabell['Voksen']
	else:
		return pris_tabell['Honoer']

print('Pris:', pris(int(input('Skriv inn alder: '))))

input('trykk enter')