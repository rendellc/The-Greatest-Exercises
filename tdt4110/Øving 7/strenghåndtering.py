def er_like(string1, string2):
	if len(string1) != len(string2):
		return False
	else:
		for i in range(len(string1)):
			if string1[i] != string2[i]: return False
	return True

def reverser_streng(string1):
	rev_streng = ''
	for i in range(len(string1)):
		rev_streng += string1[-i-1]
	return rev_streng


def palindrom_test(string1):
	return er_like(string1, reverser_streng(string1))

def streng_i_streng(string1, string2):
	if len(string2) <= len(string1):
		for i in range(len(string1)-len(string2)+1):
			if er_like(string1[i:(i+len(string2))], string2):
				return True, i
	return False

'''
test = 'aabbcccbbaa'
print(er_like(test, 'hei'))
print(er_like(test, 'hade'))
print('\n')
print(reverser_streng(test))
print(palindrom_test(test))
'''

print(streng_i_streng('Jeg likasdf pannekaker', 'r'))