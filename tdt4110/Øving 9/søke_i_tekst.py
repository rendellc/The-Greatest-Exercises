def les_tekst(filename):
	tekst = [] 
	with open(filename, 'r') as fil:
		for line in fil:
			tekst.append(line)
	return tekst

def fjern_spesialt_tegn(tekst_list):
	new_tekst = []
	for line in tekst_list:
		new_line = ''
		for ch in line:
			ch = ch.lower() #gjør ch til lowercase
			if ord(ch)>=97 and ord(ch)<=122: #sjekker bokstaver a-z
				new_line += ch
			elif ord(ch)==32: #mellomrom
				new_line += ch
			elif ord(ch)>=48 and ord(ch)<=57: #tall 0-9
				new_line += ch
			else:
				pass
		new_tekst.append(new_line)
	return new_tekst

def forekomster(tekst_list):
	word_dict = {}
	for line in tekst_list:
		line = line.split() #deler hver linje inn i ord og gjør hver linje til en egen liste
		for word in line:
			if word in word_dict.keys():
				word_dict[word] += 1
			else:
				word_dict[word] = 1
	return word_dict

def main():
	filename = 'BIBLE.txt' #input("Hva heter filen?" )
	#fil = open(filename, 'r')

	tekst = les_tekst(filename)
	tekst = fjern_spesialt_tegn(tekst)
	word_dict = forekomster(tekst)

	resultat = []
	for word in word_dict.keys():
		print(format(word, '15'),': ', word_dict[word], sep='')

	#fil.close()


main()

