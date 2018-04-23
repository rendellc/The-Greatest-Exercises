############# Kryptering og dekryptering #############
def sirkel_alfabet(nr): #tar inn et tall og returnerer det tilhørende bokstaven fra et sirkulert ascii-alfabet
	nr -= 97
	nr %= 26
	nr += 97
	return chr(nr)

def ceasar_krypt(string, hakk):
	kryptert = ''
	for ch in string:
		if ch == ' ':
			kryptert += ' '
		elif ch == '\n':
			kryptert += '\n'
		else:
			nytt_tall = ord(ch)+hakk
			kryptert += sirkel_alfabet(nytt_tall)
	return kryptert

def ceasar_dekrypt(string, hakk):
	return ceasar_krypt(string, -hakk)

def c_test():
	kryptert = ceasar_krypt(input("Skriv inn en streng med små bokstaver (a-z) og mellomrom: "), 13)
	print("Kryptert:", kryptert)
	print("Dekryptert:", ceasar_dekrypt(kryptert, 13))



######## Filbehandling #############
def open_dekrypt_file(textfil_navn):
	hakk = 3 
	with open(textfil_navn,'r') as my_file:
		content = my_file.read()
	return ceasar_dekrypt(content, hakk)

def write_krypt_file(textfil_navn, content):
	hakk = 3
	with open(textfil_navn, 'w') as my_file:
		my_file.write(ceasar_krypt(content, hakk))

def delete_last_line(textfil_navn):
	with open(textfil_navn, 'r') as f:
		lines = f.readlines()
	with open(textfil_navn, 'w') as f:
		for i in range(len(lines)-1):
			f.write(lines[i])


###################################
def main():
	textfil_navn = 'textfil.txt' #input('Skriv inn navnet på textfilen ("example.txt"): ')
	dekryptert = open_dekrypt_file(textfil_navn)
	print(dekryptert)
	
	print('STOPP for å stoppe. SLETT for å slette siste linje.')
	while True:
		linje = input('Neste linje (skriv STOPP for å stoppe): ')
		if linje == 'STOPP':
			break	
		elif linje == 'SLETT':
			write_krypt_file(textfil_navn, dekryptert)
			delete_last_line(textfil_navn)
			dekryptert = open_dekrypt_file(textfil_navn)
			print(dekryptert)
		else:
			dekryptert += linje + '\n'
	
	write_krypt_file(textfil_navn, dekryptert)

main()