birthdays = {
"22 nov": ["Lars", "Mathias"],
"10 des": " Elle ",
"30 okt": ["Veronica", "Rune"],
"12 jan": "Silje",
"31 okt": "Willy",
"8 jul": ["Brage", "Øystein"],
"1 mar": "Nina"
}

def add_birthday_to_date(date,name):
	global birthdays
	try:
		birthdays[date].append(name)
	except KeyError:
		birthdays[date] = name
	except NameError:
		birthdays[date] = list(birthdays[date]).append(name)

add_birthday_to_date('30 okt', 'Gunnar')
add_birthday_to_date('9 feb', 'Lillian')
add_birthday_to_date('4 apr', 'Nicolai')
add_birthday_to_date('1 oct', 'Rendell')
print(birthdays)

input()