def countCoins(mynt_list):
	counted = [0,0,0,0] #[tjuere, tiere, femere, enere]
	for i in mynt_list:
		if i == 20:
			counted[0] += 1
		elif i == 10:
			counted[1] += 1
		elif i == 5:
			counted[2] += 1
		elif i == 1:
			counted[3] += 1
	return counted

def numCoins(tall_liste):
	liste = tall_liste
	required_list = []
	for i in liste:
		required = [0,0,0,0]
		while True:
			if i >= 20:
				required[0] += 1
				i -= 20
				continue
			elif i >= 10:
				required[1] += 1
				i -= 10
				continue
			elif i >= 5:
				required[2] += 1
				i -= 5
				continue
			elif i >= 1:
				required[3] += 1
				i -= 1
				continue
			break
		required_list.append(required)
	return required_list  #liste med alle myntene til som kreves for tall_liste


def weightCoins(mynt_list):
	weight_list = [9.9 , 6.8, 7.85, 4.35]
	total_list = []
	for x in mynt_list:
		weight_each_type = dotproduct(weight_list, x)
		total = 0
		for i in range(4):
			total += weight_each_type[i]
		total_list.append(total)
	return total_list


def dotproduct(list1, list2):
    vektor = []
    for i in range(4):
        vektor.append(list1[i]*list2[i])
    return vektor


def main():
	liste = [12,23,34,45,56,67,78,89,90,98,87,65,54,43,21]

	required_list = numCoins(liste)  #liste med mynter som trengs for å nå tallene i 'liste'
	print(required_list)
	print(weightCoins(required_list))


main()

#numCoins([12,23,34,45,56,67,78,89,90,98,87,65,54,43,21]
