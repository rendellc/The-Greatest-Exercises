def add_family(navn, forhold, family): #forhold = bror, mor osv. 
	if forhold in family.keys():
		family[forhold].append(navn)
	else:
		family[forhold] = [navn]
	return family

def main():
	family = {}
	navn, forhold = 'ikke stopp', 'ikke stopp'
	while navn != 'stopp' and forhold != 'stopp':
		print('Skriv stopp for å stoppe')
		navn = input('Hva heter familiemedlemmet? ')
		forhold = input('Hva slags tilknyttning har han/hun deg? ')
		if navn != 'stopp' and forhold != 'stopp':
			family = add_family(navn, forhold, family)
	print(family)

main()

input()
