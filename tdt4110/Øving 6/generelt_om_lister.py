#a)
li = [1,2,3,4,5,6]
print(li)

#b)
ny_li = []
for x in li:
	if x % 2 != 0:
		ny_li.append(-x)
	else:
		ny_li.append(x)
li = ny_li
print(li)

#c)
li.sort()
print(li)