def number_of_lines(filename):
	with open(filename, 'r') as myfile:
		antall = 0
		for line in myfile:
			antall += 1
		return antall

def number_frequency(filename):
	with open(filename, 'r') as myfile:
		resultat = {}
		for line in myfile:
			if line[0] in resultat.keys(): #0-te index er der tallet er
				resultat[line[0]] += 1
			else:
				resultat[line[0]] = 0
	return resultat

print(number_of_lines('numbers.txt'))

tall_dict = number_frequency('numbers.txt')
for key in tall_dict.keys():
	print(key, ': ', tall_dict[key])