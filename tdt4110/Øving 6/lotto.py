import random

def trekk(number, antall):
	trekk_liste = number
	trekk = []
	for i in range(antall):
		trekk.append(trekk_liste.pop(random.randint(0,len(trekk_liste)-1)))
	return trekk, trekk_liste

def compList(trekk,myGuess):
	antall_like = 0
	for x in myGuess:
		if x in trekk:
			antall_like += 1
	return antall_like

def make_list_string(list1):
	string1 = ''
	for x in list1:
		string1 += str(x)
	return string1

def lotto_simulator(myGuess):
	number = [x for x in range(1,35)]
	premie = {'70': 2749455, '61':102110, '60':3385, '50':95, '41': 45}  #første siffer = hovedtrekk, andre=tillegg 
	
	#trekker tall
	hoved_trekk, trekk_liste = trekk(number, 7)
	tillegg_trekk, trekk_liste = trekk(trekk_liste, 3)
	
	#finner antall like i hovedtrekk og tilleggstrekk, og gjør det om til en string
	resultat = [compList(hoved_trekk, myGuess), compList(tillegg_trekk, myGuess)]
	resultat_string = make_list_string(resultat)
	
	#finner gevinsten
	if resultat_string in premie:
		gevinst = premie[resultat_string]
	else:
		gevinst = 0

	return gevinst


#antall forsøk på å vinne første premie
fortsett = True
n = 0
while fortsett:
	if lotto_simulator([11,13,15,17,21,31,2]) == 2749455: fortsett = False
	n += 1

print(n)

'''
#en million ganger
investering = 0   #akkumuleringsvariabel
gevinst = 0   #akkumuleringsvariabel
for i in range(1000000):
	investering += 5
	gevinst += lotto_simulator([11,13,15,17,21,31,2])

netto = gevinst - investering
print(gevinst)
print(netto)
'''
