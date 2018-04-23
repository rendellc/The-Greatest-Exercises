import random

def random_list(length, a, b):
	return [random.randint(a,b) for i in range(length)]

def comp_two_lists(list1, list2):
	like = 0
	like_tall = []
	for i in list1:
		if i in list2:
			if i not in like_tall: #for å unngå kopier
				like += 1
			like_tall.append(i)
	return like, like_tall

def comp_lists(list_of_lists):
	while len(list_of_lists)>=2:
		like, like_tall = comp_two_lists(list_of_lists[0], list_of_lists[1])
		list_of_lists.pop(0)
		list_of_lists[0] = like_tall
	return like

def partall_rekke(list1):
	rekke_liste = []
	lengde_rekke = 0 #teller sammenhengende rekke
	list1.append(1) #koden er feil, så legger til et oddetall til slutt sånn at det funker #jalla
	
	for i in range(len(list1)): 
		if list1[i] % 2 == 0:
			lengde_rekke += 1
		if i>0:
			if not list1[i-1] % 2 == 0 and list1[i]%2==0: #betyr at vi er på starten av en ny partallsrekke
				start_pos = i
		if i < len(list1) and list1[i] % 2 == 0:
			if not list1[i+1] % 2 == 0: #sjekker om neste tall er partall
				rekke_liste.append((start_pos,lengde_rekke))
				lengde_rekke = 0
	
	lengste_rekke = 0
	for rekker in rekke_liste:
		if rekker[1]>lengste_rekke:
			lengste_rekke = rekker[1]
			start_pos = rekker[0]
	try:
		return start_pos,lengste_rekke
	except:
		return 'Ingen partall i rekke'


print(partall_rekke([1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9876543]))

'''
list_of_lists = [random_list(10,0,5) for k in range(50)] #30 tilfeldige lister mellom 0 og 50 som er 50 lange]
print(list_of_lists)
print(comp_lists(list_of_lists))
'''