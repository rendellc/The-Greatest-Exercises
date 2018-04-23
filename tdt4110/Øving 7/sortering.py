import random

def bubbleSort(liste):
	n = 0
	while n <= len(liste):
		for i in range(len(liste)-1):
			if liste[i]>liste[i+1]:
				a = liste[i]
				b = liste[i+1]
				liste[i+1] = a
				liste[i] = b
				
				n = 0 #sier at et bytte har skjedd
			else:
				n += 1
	return liste

def selectionSort(liste):
	ny_liste = []
	lengde = len(liste)
	for i in range(lengde):
		ny_liste.append(max(liste))
		liste.remove(max(liste))
	return ny_liste

test_liste = [random.randint(-50,50) for i in range(10000)]

print(selectionSort(test_liste)) #3.7 sekunder for 10 000 elementer, går gjennom listen kun én gang
#print(bubbleSort(test_liste)) #24.8 sekunder for 10 000 elementer, må iterere mange flere ganger gjennom listen
