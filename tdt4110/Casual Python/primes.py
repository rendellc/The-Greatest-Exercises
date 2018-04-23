def primeGen(n, primeList):
	maxPrime = max(primeList)
	if n>maxPrime:
		for n in range(maxPrime, n):
			isPrime = True
			for prime in primeList:
				if n%prime == 0: 
					isPrime = False
					break
			if isPrime: primeList.append(n)
	return primeList

primeList = [2,3]

primeList = primeGen(10000, primeList)

def primeRatio(primeList):
	for i in range(len(primeList)):
		print(sum(primeList[:i:])/primeList[i])

primeRatio(primeList)