def rows_in_file(textfile):
	antall = 0
	with open(textfile, 'r') as fil:
		for line in fil:
			antall += 1
	return antall

def numbers_in_file(textfile):
	tall = {}
	with open(textfile, 'r') as fil:
		for line in fil:
			if line[0] in tall.keys():
				tall[line[0]] += 1
			else:
				tall[line[0]] = 1
	return tall

def print_file(tall_dict):
	tall_list = list(tall_dict.keys())
	tall_list.sort() #sorter liste med tall fra dict-en
	for tall in tall_list:
		print(tall, ': ', tall_dict[tall], sep='')

print_file(numbers_in_file('numbers.txt')) #dictionary med tall og tallforekomster
print(rows_in_file('numbers.txt'))
