from sys import stdin

Inf = float('inf')

def min_coins_greedy(coins: tuple, value: int) -> int:
    num_coins = 0
    for coin in coins:
    	num_coins += value//coin
    	value -= (value//coin)*coin

    return num_coins


def min_coins_recursive(coins: tuple, value: int) -> int:
	# contains a bug, when coins=(1000,512,1) and value=2024
	if not value:
		return 0
	if not coins:
		return Inf

	# have to calculate
	num_current = value//coins[0] # NOTE(): its not always correct to take maximum number of coins[0]
	value_remaining = value - num_current*coins[0]
	include_current = num_current + min_coins_recursive(coins[1:], value_remaining)
	dont_include_current = min_coins_recursive(coins[1:], value)
	optimal = min(include_current, dont_include_current)

	return optimal

memo = {}

def min_coins_clever(coins, value):
	Min = [value+1]*(value+1)
	Min[0] = 0

	for Sum in range (1,value+1):
		for coin in coins:
			if(coin <= Sum and Min[Sum-coin]+1 < Min[Sum]):
				Min[Sum] = Min[Sum-coin]+1
	return(Min[value])


def min_coins_dynamic(coins: tuple, value: int) -> int:
	global memo
	if not value:
		return 0
	if not coins:
		return Inf

	if (len(coins),value) in memo.keys():
		return memo[(len(coins),value)]

	# have to calculate
	# taking maximum number of coins[0] => logic error
	include_current = Inf
	if value >= coins[0]:
		include_current = 1 + min_coins_dynamic(coins, value-coins[0])
	
	dont_include_current = min_coins_dynamic(coins[1:], value)
	
	optimal = min(include_current, dont_include_current)
	
	memo[(len(coins),value)] = optimal

	return optimal

def min_coins_dynamic_with_bug(coins: tuple, value: int) -> int:
	global memo
	if not value:
		return 0
	if not coins:
		return Inf

	if (len(coins),value) in memo.keys():
		return memo[(len(coins),value)]

	# have to calculate
	# taking maximum number of coins[0] => logic error
	num_current = value//coins[0] # NOTE(): its not always correct to take maximum number of coins[0]
	value_remaining = value - num_current*coins[0]
	include_current = num_current + min_coins_dynamic_with_bug(coins[1:], value_remaining)
	dont_include_current = min_coins_dynamic_with_bug(coins[1:], value)
	
	optimal = min(include_current, dont_include_current)
	
	memo[(len(coins),value)] = optimal

	return optimal

'''
def can_use_greedy(coins: tuple) -> bool:
	n = len(coins)

	for i in range(n):
		for k in range(i+1,n):
			if (coins[i] < (k-i+1)*coins[k]):
				return False

	return True
'''
def can_use_greedy(coins: tuple) -> bool:
	prev = Inf
	for coin in coins:
		if coin*2 > prev:
			return False
		prev = coin

	return True
'''
'''
def main():
	coins = []
	for c in stdin.readline().split():
	    coins.append(int(c))
	coins.sort()
	coins.reverse()
	coins = tuple(coins)

	method = stdin.readline().strip()

	if method == "graadig" or (method == "velg" and can_use_greedy(coins)):
	    for line in stdin:
	    	#print(int(line), min_coins_greedy(coins, int(line)))
	        print(min_coins_greedy(tuple(coins), int(line)))
	else:
	    for line in stdin:
	        print(min_coins_clever(tuple(coins), int(line)))


def test():
	coins = (1000, 512, 1)
	values = [2024]
	print(coins)	
	print("Can use greedy? ", "Yes"*can_use_greedy(coins) + "No"*(not can_use_greedy(coins)))

	#for value in values:
	#	print("best greedy:",min_coins_greedy(coins, value))

	for value in values:
		print(value)
		print("\tGrådig: ", min_coins_greedy(coins,value))

		print("\tDynamic: ", min_coins_clever(coins,value))

		print("\tRecursive: ", min_coins_recursive(coins, value))
	

#test()
main()
#print(memo)