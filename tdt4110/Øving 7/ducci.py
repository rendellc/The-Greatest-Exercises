import math

def ducci(tallrekke):
	tallrekke_kopi = [0 for i in tallrekke]
	i = 0
	while tallrekke_kopi != tallrekke:
		for i in range(len(tallrekke)):
			tallrekke_kopi[i] = math.fabs(tallrekke[i]-tallrekke[(i+1)%len(tallrekke)])
		tallrekke = tallrekke_kopi
		tallrekke_kopi = [0 for i in tallrekke]
		print(tallrekke)

ducci([1,-3456789,1,1,1,1,1,1])
