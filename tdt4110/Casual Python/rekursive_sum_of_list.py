depth = 0

def rekursive_sum(list1):
	
	if len(list1) == 1:
		return list1[0]
	else:
		return list1[0] + rekursive_sum(list1[1:])

print(rekursive_sum([2,3,4,4,4,4,4,4,4]))


def rekursive_square(x):
	global depth
	depth += 1
	if x <= 2:
		return 1.00001
	else:
		return rekursive_square(x-1)*rekursive_square(x-1)

print(rekursive_square(9))
print('Rekursjonsdybde: ', depth)
print(1*2*3+2*3*4*5*6)