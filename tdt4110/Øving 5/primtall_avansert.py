
def get_prime_file():
	textfile = open("primtallsliste.txt", "r")
	
	prime_list = []
	for line in textfile:
		prime_list.append(int(line))

	textfile.close()
	return prime_list

def write_to_prime_file(prime_list):
	textfile = open("primtallsliste.txt", "w")

	for tall in prime_list:
		textfile.write(str(tall) + "\n")

def isprime(tall, prime_list):
        for n in prime_list:
                if  tall % n == 0:
                        return False
        return True

def calculate_prime(i, prime_list):
	last_known_prime = prime_list[-1]
	for k in range(last_known_prime+1,i): #3 default
		if isprime(k, prime_list):
			prime_list.append(k)
	return prime_list 

def prime_factor(tall,prime_list):
	prime_factors = []  			#liste som faktorene legges til
	if tall in prime_list:
		prime_factors = [tall]
	else:
		for prime in prime_list:
			if tall % prime == 0:
				power = 1			#tester potenser av primtall
				while tall%(prime**power) == 0:
					prime_factors.append(prime)
					power += 1
	return prime_factors

def main1(primes_up_to):
	prime_list = get_prime_file()

	#regner ut og legger til primtall til i filen
	calculate_prime(primes_up_to, prime_list)
	write_to_prime_file(prime_list)

	#primtallsfaktoriserer tall
	print(prime_factor(4, prime_list))

main1(800000)