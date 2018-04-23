def first_hundred_numbers(filename):
	fil = open(filename, 'w')
	for nr in range(1,101):
		fil.write(str(nr) + '\n')
	fil.close()

first_hundred_numbers('første_hundre_tall.txt')

def read_and_check(filename):
	correct_list = [n for n in range(1,101)]
	print(correct_list)
	fil = open(filename,'r')
	fil_liste = []
	for line in fil:
		fil_liste.append(int(line[:~0]))
	print(fil_liste)
	if fil_liste == correct_list:
		return True
	else:
		return False
	print(fil_liste)

print(read_and_check('første_hundre_tall.txt'))

def read_or_write():
	filename = input('Hva heter filen? ')
	write = input('Vil du skrive til filen? (ja/nei) ')

	if write == 'ja':
		#try:
		with open(filename, 'w+') as fil:
			print('\n'*5)
			for line in fil:
				print(line)
			print('Skriv "stopp" for å stoppe')
			while True:
				skriv_inn = input()
				if skriv_inn == 'stopp':
					break
				else:	
					fil.write(skriv_inn)
		#except:
		#	pass
	else:
		with open(filename, 'r') as fil:
			for line in fil:
				print(line, end='')

read_or_write()

input()