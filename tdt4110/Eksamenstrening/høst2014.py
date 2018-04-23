# Eksamen ITGK 2014 besvarelse

# ***** Oppgave 1 *****
'''
1. d	R
2. b	R
3. b	R
4. d	R
5. a	R
6. b	R
7. c	R
8. c	R
9. c	R
10. d	R
11. b	R
12. d	R
13. a	R
14. b	R
15. a	R
16. a	R
17. a	R
18. d	R
19. c	R
20. a	R
21. b	R
22. a	R
23. a	R
24. a	R
25. a	R

25/25
'''

# ***** Oppgave 2 *****
# a)
def inputPerson():
	navn = input('Name: ')
	ID = input('ID: ')
	vekt = int(input('Weight: '))
	size = int(input('Size: '))
	return [navn, ID, vekt, size]

# b)
def readDbFile(filename):
	db = []
	with open(filename, 'r') as f:
		for line in f:
			line = line.split(';')
			entry = [line[0], line[1], int(line[2]), int(line[3])]
			db.append(entry)
	return db

# c)
def printMembersList(db):
	COL1 = 15
	COL2 = 9
	COL3 = 5
	COL4 = 4
	print('Navn'.ljust(COL1), 'ID-NR'.ljust(COL2), 'VEKT kg.'.rjust(COL3+4), 'SKJERMSTORLEIK'.rjust(COL4))
	for line in db:
		print(line[0].ljust(COL1), line[1].ljust(COL2), str(line[2]).rjust(COL3)+' kg', str(line[3]).rjust(COL4)+'kvadratfot')

# d)
def addPerson(filename):
	person = inputPerson()
	db = readDbFile(filename)
	db.append(person)
	with open(filename, 'a') as f:
		f.write(person[0]+';'+person[1]+';'+person[2]+';'+person[3]+'\n')
	return db

# e)
def feet2seconds(feet):
	if feet<=3000:
		return 0
	elif feet <= 4000:
		return (feet-3000)/100
	else:
		return 10 + (feet-4000)/200

# 22/25

# ***** Oppgave 3 *****
# a)
def weatherStats(weatherData):
	max_entry = (-float('inf'), None)
	min_entry = (float('inf'), None)
	rain = 0
	for i in range(len(weatherData)):
		if weatherData[i][0]>max_entry[0]:
			max_entry = (weatherData[i][0], i+1)
		if weatherData[i][1]<min_entry[1]:
			min_entry = (weatherData[i][1], i+1)
		rain += weatherData[i][2]

	print('There are', len(weatherData), 'in the period.')
	print('The highest temperature was', max_entry[0], 'C on day number', max_entry[1])
	print('The lowest temperature was', min_entry[0], 'C on day number', min_entry[1])
	print('There was a total of', rain, 'mm rain in the period. ')

# b) ** litt feil i rangen og litt utydelig kodet
def coldestThreeDays(weatherData): 
	coldest = (float('inf'), None)
	for i in range(len(weatherData)-3):
		period = weatherData[i:i+3][1]
		avg = sum(period)/3
		if coldest[0] >= avg:
			coldest = (avg, i+1)
	return coldest[1]

# c)
def addNewDay(extraData, weatherData): 
	extraData.split(', ')
	#finner høyeste temp
	maxTemp = int(extraData[0].strip('max='))
	minTemp = int(extraData[1].strip('min='))
	rain	= int(extraData[2].strip('mm'))
	weatherData.append([maxTemp, minTemp, rain])
	return weatherData

# 25/30

# ****** Oppgave 4 ******
'''
a) 	14
	Funksjonen ganger sammen tall på motsatt side av listen og summerer alle produktene. 
b) 	[1,0,1,0]
	[0,1,0,1]
	[1,0,1,0]
	[0,1,0,1]
	Lager et sjakkrutemønster med 0 og 1 som er W*W stort
c) 'ROSENBORG'
	Funksjonen setter sammen hver tredje indeks (fra 0-te) til én sammenhengende streng. 
d)	Feil 1 skjer i linje 14 hvor det burde stå; return parentheses_list==[]
	Feil 2 skjer fordi koden ikke sjekker rekkefølge på paranteser, kun forekomster. For
	eksempel etter en ( må det komme en ny åpende parantes eller en ), slik at parantesen lukkes
	før noen nye åpnes. Hvis koden oppdager en lukkende parantes må den sjekke at den svarer til 
	forrige åpnende parantes. Feilen kan rettes i linje 10 ved å heller skrive
		if char != parentheses_list[~0]: 
	og i linje 13 hvor den må fjerne siste element i listen
		parentheses_list.pop()

18/20
'''