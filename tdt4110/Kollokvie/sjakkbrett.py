def is_partall(n):
	if n%2 == 0:
		return True
	else:
		return False

def sjakkbrett(coordinate): #coordinate = [x,y]
	x = coordinate[0]
	y = coordinate[1]

	if is_partall(x) and is_partall(y):
		return 'Svart'
	elif not is_partall(x) and not is_partall(y):
		return 'Svart'
	else:
		return 'Hvit'

for x in range(1,9):
	for y in range(1,9):
		print('Rute', x,',',y,'er:', sjakkbrett([x,y]))