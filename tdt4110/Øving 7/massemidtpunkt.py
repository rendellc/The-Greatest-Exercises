import random

def center_of_mass(stang):
	M = 0
	for m in stang: M += m #total masse
	r_i = 0.5
	summen = 0
	for m_i in stang:
		summen += m_i*r_i
		r_i += 1
	return summen/M

random_stang = [random.randint(1,10) for i in range(15)]
print('Tilfeldig generert:', random_stang)
print(center_of_mass(random_stang))

print(center_of_mass([1]))
print(center_of_mass([1,1]))
print(center_of_mass([1,1,1]))
print(center_of_mass([3,1,3]))
print(center_of_mass([1,2,3,4]))