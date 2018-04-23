import math

def rekurs_sum(n):
	if  n:
		return n + rekurs_sum(n-1)
	return 0

def smallest_element(liste, i=0, smallest=float('inf')):
	if liste[i] < smallest:
		smallest = liste[i]
	if i==len(liste)-1: # siste element i liste
		return smallest
	return smallest_element(liste, i+1, smallest)

req_depth = 0

def rekurs_sinus(x):
	global req_depth
	req_depth += 1 #nysjerrig på rekursjonsdybde
	print(req_depth)

	epsilon = 10**(-323) #lite tall, må være (mye) mindre enn 1
	if math.fabs(x)<epsilon:
		return x
	else:
		sin_x3 = rekurs_sinus(x/3) # gir forbedring på ~2^n ganger færre rekursjoner
		return 3*sin_x3-4*sin_x3**3
		#return 3*rekurs_sinus(x/3)-4*rekurs_sinus(x/3)**3


print(rekurs_sum(3))
#print(smallest_element([-9,5,21,3,5,4,-40]))
#print(rekurs_sinus(math.pi))

input('done')
