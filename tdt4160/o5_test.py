
def printAll():
	print("r0:", r0)
	print("r1:", r1)
	print("r2:", r2)
	print("r3:", r3)

r0 = 2
r1 = 1
r2 = 1
r3 = [False,False,False]
print("r1:", r1)
while not r3[1]:
	#r1 = 1
	r2 = r2*r0 # mul
	
	r0 = r0 - r1 # sub

	# cmp
	r3[0] == r0 < r1
	r3[1] == r0 > r1
	r3[2] == r0 == r1
	printAll()
	input()

print("r2", r2)

input()