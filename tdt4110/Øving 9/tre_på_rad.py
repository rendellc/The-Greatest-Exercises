def print_board(board):
	print(' 1 2 3')
	print('-------')
	for row in range(len(board)):
		for col in board[row]:
			print('|', col, sep='' ,end='')
		print('|', row+1)
	print('-------')

def check_board(board):
	#sjekker rader
	for rad in board:
		if rad[0]== rad[1] and rad[0]==rad[2]:
			if rad[0] is not ' ':
				return True, rad[0]
	
	#sjekker kolonner
	for i in range(len(board)):
		if board[0][i]==board[1][i] and board[0][i]==board[2][i]:
			if board[0][i] is not ' ':
				return True, board[0][i]

	#sjekker diagonaler
	if board[0][0]==board[1][1] and board[0][0]==board[2][2]:
		if board[0][0] is not ' ':
			return True, board[0][0]
	elif board[2][0]==board[1][1] and board[2][0]==board[0][2]:
		if board[2][0] is not ' ':	
			return True, board[2][0]	
	
	#hvis ingen har vunnet
	#sjekker om det er flere tomme celler i brettet
	for rad in board:
		if ' ' in rad:
			return False, True
	return False, False #seier, fortsett

def input_names():
	spiller1 = input('Spiller 1: ')
	spiller2 = input('Spiller 2: ')
	return spiller1, spiller2

def legal_move(move, board): #move=(x,y) koordinatet til plasseringa, #board=matrise
	x = move[0]
	y = move[1]
	if board[x][y] == ' ':
		return True
	else:
		return False

def input_move():
	while True:
		move = input("Hvor vil du sette inn? (f. eks. '1,2') ")
		move = [int(move[0])-1, int(move[2])-1]
		if move[0] in [0,1,2] and move[1] in [0,1,2]:
			break #gyldig input, 
	return move

	
def tre_paa_rad_main():
	spiller1, spiller2 = input_names()
	spiller1_sign = 'x'
	spiller2_sign = 'o'

	start_board = [[' ',' ',' '],[' ',' ',' '],[' ',' ',' ']]
	board = start_board

	while True:
		print_board(board)

		print(spiller1, 'sin tur')
		move = input_move()
		while not legal_move(move, board):
			move = input_move()
		x = move[0] #minus en pga. nullindeks
		y = move[1]
		board[x][y] = spiller1_sign
		seier, fortsett = check_board(board)
		if seier:
			print_board(board)
			print(spiller1, 'vant!')
			return None #for å avslutte spillet
		elif not fortsett:
			print_board(board)
			print('Ingen vant :(')
			return None #for å avslutte spillet

		print_board(board)

		print(spiller2, 'sin tur')
		move = input_move()
		while not legal_move(move, board):
			move = input_move()

		x = move[0] #minus en pga. nullindeks
		y = move[1]
		board[x][y] = spiller2_sign
		seier, fortsett = check_board(board)
		if seier:
			print_board(board)
			print(spiller2, 'vant!')
			return None #for å avslutte spillet
		elif not fortsett:
			print_board(board)
			print('Ingen vant :(')
			return None #for å avslutte spillet

tre_paa_rad_main()

input() #sånn at ikke konsollen forsvinner