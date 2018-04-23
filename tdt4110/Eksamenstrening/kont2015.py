'''
Oppgave 1: flervalg
1) d	r
2) d	r
3) a	r
4) c	r
5) c	r
6) 
7) d	g
8) c	r
9) a	r
10) a	r
11) a	r
12) a	r
13) b	r
14) a	r
15) c	r
16) b	r
17) b	r
18) d	r
19) b	r
20) b	r

sum: 18r-1g=18-0.5=17.5
17.5/20
'''

'''
Oppgave 2
a) [25.0, 20.0, 20.0, 13.33, 15.0]
b) Alle elementer i lister blir til gjennomsnittet
av seg selv og sine naboer. 

c) False
d) Sjekker om to etterfølgende elementer svarer til to etterfølgende
tall (hvis vi antar heltall). 

e) 2
f) Den finner tallet x i listen A og returner produktet av 
koordinatet (null-indeksert)

'''

# Oppgave 1
# a)
import random

SKILTBOKSTAV = ('A','B','C','D','E','F','G','H','J','K','L','N','P','R','S','T','U','V','X','Y','Z','?')

def throw(n):
	return [random.randint(1,6) for i in range(n)]

# b)
def chance(dice):
	summen = 0
	for nr in dice:
		summen += nr
	return summen
# c)
def house(dice):
	dice.sort()
	if dice[0]==dice[1] and dice[1]==dice[2]: #tre første er like
		if dice[3]==dice[4] and dice[2]!=dice[3]:
			return chance(dice)
	elif dice[0]==dice[1] and dice[1]!=dice[2]:
		if dice[2]==dice[3] and dice[3]==dice[4]:
			return chance(dice)
	return 0

# d)
def straight(dice):
	dice.sort()
	if dice == [1,2,3,4,5]:
		return 15
	elif dice == [2,3,4,5,6]:
		return 20
	return 0

# Oppgave 4
# a)
def les_inn_bilinfo():
	merke = input('Hvilket bilmerke var det? ')
	modell = input('Hvilken modell? ')
	farge = input('Hvilken farge? ')
	return [merke, modell, farge]

# b)
def sjekk_bil(vitne, faktisk):
	for i in range(0,3):
		if vitne[i] == faktisk[i]:
			pass
		elif vitne[i] == '?':
			pass
		else:
			return False
	return True

# c)
def les_gyldig_vitneskilt():
	print('Skiltet består av 7 tegn (bruk ? hvis du er usikker)')
	
	cont=True
	while cont:
		cont=False
		lest = input('Skriv inn bilskiltet du så: ')
		if len(lest) != 7:
			print('Det skal være nøyaktig syv tegn') 
			cont=True
		if (lest[0] not in SKILTBOKSTAV) or (lest[1] not in SKILTBOKSTAV):
			print('To første tegn må være lovil skiltbokstav eller ?')
			cont=True
		for tall in lest[2::]:
			if (tall != '?') and (tall not in ['0','1','2','3','4','5','6','7','8','9']):
				print('5 siste tegn må være tall eller ?')
				cont=True
				break

		return lest

# d)
def match(vitne, faktisk):
	for i in range(len(vitne)):
		if (vitne[i]!=faktisk[i]) and (vitne[i]!='?'):
			return False
	return True

# e)
def match_liste(vitne, liste):
	matches = []
	for faktisk in liste:
		if match(vitne, faktisk):
			matches += faktisk
	return matches

# f)
def main():
	try:
		f = open('biler.txt', 'r')
		print('Fil lest')
		bil_dict = {}
		for line in f:
			info = line.split(' ')
			bil_dict[info[0]] = (info[1::])
		f.close()
	except:
		print('Filen mangler')
		return None

	cont='J'
	while cont=='J': #hovedløkke
		vitne_info = les_inn_bilinfo()
		vitne_skilt = les_gyldig_vitneskilt()

		# sjekker for alternativer
		skilt_liste = [] # mulige skilt
		for skilt in bil_dict.keys():
			if match(vitne_skilt, skilt):
				skilt_liste.append(skilt)
		no_match = True
		for skilt in skilt_liste:
			faktisk_info = bil_dict[skilt][:3:] #alle innføringer unntatt eieren
			if sjekk_bil(vitne_info, faktisk_info):
				print(skilt, 'Eier:', bil_dict[skilt][~0])
				no_match = False
		if no_match: print('Ingen matcher funnet')	
		
		cont = input('Vil du sjekke flere kjøretøyer? (J/N) ')

main()



