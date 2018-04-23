def V_sluttsum(A,r,k):
	year_list = []
	for i in range(k+1):
		year_list.append(A*(1+r/4)**(4*i))
	#return year_list[-1]
	for year in range(len(year_list)):
		print(year, '\t', format(year_list[year], '5.0f'))

def A_startsum(V,r,k):
	A = 0
	while A*(1+r/4)**(4*k) < V:
		A += 1000 #øker startsum
	return A

#print(V_sluttsum(1000, 0.06, 20))
print(A_startsum(5000, 0.05, 20))