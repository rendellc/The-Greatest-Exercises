
from sys import stdin

def main():

	# Read input.
	char_list = {}
	char_pos = 0
	for line in stdin:
		for char in line:
			char_pos += 1
			if char in char_list.keys():
				char_list[char].append(char_pos)
			else:
				char_list[char] = [char_pos]

	with open('test_case.txt', 'w') as file:
		for char in char_list.keys():
			file.write(char + ':')
			
			temp = str(char_list[char])
			#print(temp)
			temp = temp.replace(' ', '')
			temp = temp.replace('[', '')
			temp = temp.replace(']', '')
			#print(temp)
			file.write(temp + '\n')

if __name__ == "__main__":
	main()