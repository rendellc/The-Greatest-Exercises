#en klasse for hver brikke
#klassen har posisjon og lovlige trekk
	# lovlige trekk = posisjoner den kan flytte seg til fra sin nåverende posisjon
		# liste med funksjoner av posisjonen som inneholder alle mulige posisjon
			# bonder beveger seg annerledes når de kan angripe
		# må ta hensyn til grensene på brettet
		# tar ikke hensyn til andre brikker
		# 
	# en boolsk variabel som sier om den kan angripe kongen
	# 

# brettet
	# 1-indeksert fra øverst til venstre, radene burde være bokstaver
		# selve logikken bør være 0-indeksert fordi det er enklere
	# hvit starter nederst, sort øverst
		# hvit beveger seg i negativ retning, mens sort går i positiv

EMPTY = None

class AllPieces: #klasse som alle brikker arver fra
	
	
	def check_boundries(self, row, col): # posisjoion = (row, col)
		# tar inn posisjon og returnerer den igjen hvis den er på brettet
		if row in [0,1,2,3,4,5,6,7] and col in [0,1,2,3,4,5,6,7]:
			return True
		else:
			return False

	def check_occupied_cell(self, position):
		# tar inn position returner True hvis det er en annen brikke der, returnerer False ellers
		if position == None: 
			return False
		for piece in game.white_pieces:
			if piece.position == position:
				return True
		for piece in black_pieces:
			if piece.position == position:
				return True

		return False

	def legal_move_check_list_friendly_pieces(self):
		# sjekker om posisjoner i legal_move_list er okkupert av egne brikker
		if self.color == 'BLACK':
			for piece in game.black_pieces:
				if piece.position in self.legal_move_list:
					self.legal_move_list.remove(piece.position)
		elif self.color == 'WHITE':
			for piece in game.white_pieces:
				if piece.position in self.legal_move_list:
					self.legal_move_list.remove(piece.position)

	def legal_move_check_list_enemy_pieces(self):
		# sjekker om posisjoner i legal_move_list er okkupert av fiendens brikker
		if self.color == 'BLACK':
			for piece in game.white_pieces:
				if piece.position in self.legal_move_list:
					self.legal_move_list.remove(piece.position)
		elif self.color == 'WHITE':
			for piece in game.black_pieces:
				if piece.position in self.legal_move_list:
					self.legal_move_list.remove(piece.position)

	def legal_move_check_attack_enemy_king(self):
		# sjekker om fiendens konge er i legal_move_list
		if self.color == 'BLACK':
			if game.white_king.position in self.legal_move_list:
				self.attackEnemyKing = True
			else:
				self.attackEnemyKing = False
		elif self.color == 'WHITE':
			if game.black_king.position in self.legal_move_list:
				self.attackEnemyKing = True
			else:
				self.attackEnemyKing = False 

	def legal_move_check_attack_my_king(self):
		# fjerner de trekkene som setter egen konge i sjakk
		if self.color == 'BLACK':
			move_index = 0
			while move_index < len(self.legal_move_list):
				self.position = self.legal_move_list[move_index]
				
				#AllPieces.update_all_enemy_legal_moves(self) # oppdaterer fiendens trekk

				for piece in game.white_pieces:
					if game.black_king.position in piece.legal_move_list:
						self.legal_move_list.pop(move_index)
						move_index -= 1 #sånn at den ikke hopper over noen
						break
				move_index += 1
		elif self.color == 'WHITE':
			move_index = 0
			while move_index < len(self.legal_move_list):
				self.position = self.legal_move_list[move_index]
				
				#AllPieces.update_all_enemy_legal_moves(self) # oppdaterer fiendens trekk

				for piece in game.black_pieces:
					if game.white_king.position in piece.legal_move_list:
						self.legal_move_list.pop(move_index)
						move_index -= 1 #sånn at den ikke hopper over noen
						break
				move_index += 1

	def legal_move_remove_copies(self):
		# fjerner kopier
		self.legal_move_list = list(set(self.legal_move_list))

		# fjerner 'None' fra legal_move_list
		i = 0 #counter
		while None in self.legal_move_list:
			if self.legal_move_list[i] == None:
				self.legal_move_list.pop(i)
				i -= i
			i += 1

	def legal_move_check_borders(self):
		for move in self.legal_move_list:
			if not self.check_boundries(move[0], move[1]):
				self.legal_move_list.remove(move)

	def update_all_enemy_legal_moves(self):
		if self.color == 'BLACK':
			for piece in game.white_pieces:
				piece.legal_moves()
		elif self.color == 'WHITE':
			for piece in game.black_pieces:
				piece.legal_moves()

	def validate_legal_move_list(self):
		self.legal_move_remove_copies()
		self.legal_move_check_borders()
		self.legal_move_check_attack_my_king()
		self.legal_move_check_list_friendly_pieces()

class Pawn(AllPieces):

	def __init__(self, color, startPosition):
		self.moveNumber = 0 # teller antall moves
		self.alive = True
		self.color = color.upper()
		self.position = startPosition
		self.attackEnemyKing = False
		self.legal_moves()


	def legal_moves(self):
		# tar inn posistion = (row, col) og lager en liste av alle posisjonene man kan flytte til
		# tar i første omgang ikke hensyn til banens grenser, eller andre brikker
		# må legge inn en ekstra test som sjekker at fienden ikke kan angripe kongen
		self.legal_move_list = []

		row = self.position[0]
		col = self.position[1]

		if self.color == 'BLACK':
			# vanlig trekk
			self.legal_move_list.append((row+1, col))

			# første trekk
			if self.moveNumber <= 0:
				self.legal_move_list.append((row+2, col))

			# fiender diagonalt
			for piece in game.white_pieces:
				if piece.position == (row+1, col+1):
					self.legal_move_list.append((row+1, col+1))
				if piece.position == (row+1, col-1):
					self.legal_move_list.append((row+1, col-1))
		
		elif self.color == 'WHITE':
			# vanlig trekk
			self.legal_move_list.append((row-1, col))

			# første trekk
			if self.moveNumber <= 0:
				self.legal_move_list.append((row-2, col))

			# fiender diagonalt
			for piece in game.black_pieces:
				if piece.position == (row-1, col+1):
					self.legal_move_list.append((row+1, col+1))
				if piece.position == (row-1, col-1):
					self.legal_move_list.append((row+1, col-1))

		AllPieces.validate_legal_move_list(self)


class Rook(AllPieces):

	def __init__(self, color, startPosition):
		self.moveNumber = 0
		self.alive = True
		self.color = color.upper()
		self.position = startPosition
		self.attackEnemyKing = False
		self.sjakk = False
		self.sjakkMatt = False
		self.legal_moves()

	def legal_moves(self):
		self.legal_move_list = []

		continueDown = True
		continueUp = True
		continueRight = True
		continueLeft = True

		row = self.position[0]
		col = self.position[1]

		for n in range(9):
			if not AllPieces.check_occupied_cell((row+n, col)) and continueDown:
				self.legal_move_list.append((row+n, col))
			else:
				continueDown = False

			if not AllPieces.check_occupied_cell((row-n, col)) and continueUp:
				self.legal_move_list.append((row+n, col))
			else:
				continueDown = False

			if not AllPieces.check_occupied_cell((row, col+n)) and continueRight:
				self.legal_move_list.append((row, col+n))
			else:
				continueRight = False

			if not AllPieces.check_occupied_cell((row, col-n)) and continueLeft:
				self.legal_move_list.append((row, col-n))
			else:
				continueLeft = False

			if not continueDown and not continueUp and not continueRight and not continueLeft:
				break

		AllPieces.validate_legal_move_list()

class Bishop(AllPieces):

	def __init__(self, color, startPosition):
		self.moveNumber = 0
		self.alive = True
		self.color = color.upper()
		self.position = startPosition
		self.attackEnemyKing = False
		self.sjakk = False
		self.sjakkMatt = False
		self.legal_moves()

	def legal_moves(self):
		self.legal_move_list = []

		continueDownRight = True
		continueUpLeft = True
		continueDownLeft = True
		continueUpRight = True

		row = self.position[0]
		col = self.position[1]

		for n in range(9):
			if not AllPieces.check_occupied_cell((row+n, col+n)) and continueDownRight:
				self.legal_move_list.append((row+n, col+n))
			else:
				continueDownRight = False

			if not AllPieces.check_occupied_cell((row+n, col-n)) and continueDownLeft:
				self.legal_move_list.append((row+n, col-n))
			else:
				continueDownLeft = False

			if not AllPieces.check_occupied_cell((row-n, col+n)) and continueUpRight:
				self.legal_move_list.append((row-n, col+n))
			else:
				continueUpRight = False
			if not AllPieces.check_occupied_cell((row-n, col-n)) and continueUpLeft:
				self.legal_move_list.append((row-n, col-n))
			else:
				continueUpLeft = False
			
			if not continueDownRight and not continueUpLeft and not continue3 and not continue4:
				break

		AllPieces.validate_legal_move_list()

class Knight(AllPieces):

	def __init__(self, color, startPosition):
		self.moveNumber = 0
		self.alive = True
		self.color = color.upper()
		self.position = startPosition
		self.attackEnemyKing = False
		self.sjakk = False
		self.sjakkMatt = False
		self.legal_moves()

	def legal_moves(self):
		self.legal_move_list = []

		row = self.position[0]
		col = self.position[1]

		for bigmove in [-2,2]:
			for smallmove in [-1,1]:
				self.legal_move_list.append((row+bigmove, col+smallmove))
				self.legal_move_list.append((row+smallmove, col+bigmove))

		AllPieces.validate_legal_move_list()

class Queen(AllPieces):

	def __init__(self, color, startPosition):
		self.moveNumber = 0
		self.alive = True
		self.color = color.upper()
		self.position = startPosition
		self.attackEnemyKing = False
		self.sjakk = False
		self.sjakkMatt = False
		self.legal_moves()

	def legal_moves(self):
		self.legal_move_list = []

		continueDown, continueUp, continueRight, continueLeft = True, True, True, True
		continueDownRight, continueUpLeft, continueUpRight, continueDownLeft = True, True, True, True

		row = self.position[0]
		col = self.position[1]

		for n in range(9):
			if not AllPieces.check_occupied_cell((row+n, col)) and continueDown:
				self.legal_move_list.append((row+n, col))
			else:
				continueDown = False
			if not AllPieces.check_occupied_cell((row-n, col)) and continueUp:
				self.legal_move_list.append((row-n, col))
			else:
				continueUp = False
			if not AllPieces.check_occupied_cell((row, col+n)) and continueRight:
				self.legal_move_list.append((row, col+n))
			else:
				continueRight = False
			if not AllPieces.check_occupied_cell((row, col-n)) and continueLeft:
				self.legal_move_list.append((row, col-n))
			else:
				continueLeft = False
			if not AllPieces.check_occupied_cell((row+n, col+n)) and continueDownRight:
				self.legal_move_list.append((row+n, col+n))
			else:
				continueDownRight = False
			if not AllPieces.check_occupied_cell((row-n, col-n)) and continueUpLeft:
				self.legal_move_list.append((row-n, col-n))
			else:
				continueUpLeft = False
			if not AllPieces.check_occupied_cell((row-n, col+n)) and continueUpRight:
				self.legal_move_list.append((row-n, col+n))
			else:
				continueUpRight = False
			if not AllPieces.check_occupied_cell((row+n, col-n)) and continueDownLeft:
				self.legal_move_list.append((row+n, col-n))
			else:
				continueDownLeft = False

			if not continueDown and not continueUp and not continueRight and not continueLeft and not continueDownRight and not continueUpLeft and not continueDownLeft and not continue8:
				break

		AllPieces.validate_legal_move_list()

class King(AllPieces):

	def __init__(self, color, startPosition):
		self.moveNumber = 0
		self.alive = True
		self.color = color.upper()
		self.position = startPosition
		self.attackEnemyKing = False
		self.sjakk = False
		self.sjakkMatt = False
		self.legal_moves()

	def legal_moves(self):
		self.legal_move_list = []

		row = self.position[0]
		col = self.position[1]

		for verticalMove in [-1,0,1]:
			for horisontalMove in [-1,0,1]:
				if verticalMove != 0 and horisontalMove != 0:
					self.legal_move_list.append((row+verticalMove, col+horisontalMove))

		AllPieces.validate_legal_move_list()

class Game:

	def __init__(self):
		self.create_and_populate_board()

	def create_and_populate_board(self):

		self.white_pawn1 = Pawn('white', (6,0))
		self.white_pawn2 = Pawn('white', (6,1))
		self.white_pawn3 = Pawn('white', (6,2))
		self.white_pawn4 = Pawn('white', (6,3))
		self.white_pawn5 = Pawn('white', (6,4))
		self.white_pawn6 = Pawn('white', (6,5))
		self.white_pawn7 = Pawn('white', (6,6))
		self.white_pawn8 = Pawn('white', (6,7))
		self.white_rook1 = Knight('white', (7,0))
		self.white_rook2 = Knight('white', (7,7))
		self.white_knight1 = Knight('white', (7,1))
		self.white_knight2 = Knight('white', (7,6))
		self.white_bishop1 = Bishop('white', (7,2))
		self.white_bishop2 = Bishop('white', (7,5))
		self.white_queen = Queen('white', (7,4))
		self.white_king = King('white', (7,3))

		self.black_pawn1 = Pawn('black', (1,0))
		self.black_pawn2 = Pawn('black', (1,1))
		self.black_pawn3 = Pawn('black', (1,2))
		self.black_pawn4 = Pawn('black', (1,3))
		self.black_pawn5 = Pawn('black', (1,4))
		self.black_pawn6 = Pawn('black', (1,5))
		self.black_pawn7 = Pawn('black', (1,6))
		self.black_pawn8 = Pawn('black', (1,7))
		self.black_rook1 = Knight('black', (0,0))
		self.black_rook2 = Knight('black', (0,7))
		self.black_knight1 = Knight('black', (0,1))
		self.black_knight2 = Knight('black', (0,6))
		self.black_bishop1 = Bishop('black', (0,2))
		self.black_bishop2 = Bishop('black', (0,5))
		self.black_queen = Queen('black', (0,4))
		self.black_king = King('black', (0,3))

		self.white_pieces = [self.white_pawn1, self.white_pawn2, self.white_pawn3, self.white_pawn4, self.white_pawn5, self.white_pawn6, \
							 self.white_pawn7, self.white_pawn8, self.white_rook1, self.white_rook2, self.white_knight1, self.white_knight2, \
					 			self.white_bishop1, self.white_bishop2, self.white_queen, self.white_king]

		self.black_pieces = [self.black_pawn1, self.black_pawn2, self.black_pawn3, self.black_pawn4, self.black_pawn5, self.black_pawn6, \
							self.black_pawn7, self.black_pawn8, self.black_rook1, self.black_rook2, self.black_knight1, self.black_knight2, \
							 self.black_bishop1, self.black_bishop2, self.black_queen, self.black_king]

		self.chess_board =  [[EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY],
							[EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY],
							[EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY],
							[EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY],
							[EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY],
							[EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY],
							[EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY],
							[EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY]]

		for piece in self.white_pieces: 
			row = piece.position[0]
			col = piece.position[1]
			self.chess_board[row][col] = piece
		for piece in self.black_pieces: 
			row = piece.position[0]
			col = piece.position[1]
			self.chess_board[row][col] = piece

game = Game()

def move_piece():
	row0 = 6
	col0 = 1

	piece = game.chess_board[row0][col0]

	piece.legal_moves()
	print(piece.legal_move_list)

move_piece()