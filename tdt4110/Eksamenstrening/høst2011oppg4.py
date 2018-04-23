import random

def check_highscore(point, scores):
	for place in scores:
		if point > scores[place][1]:
			return place
	return -1

def print_highscores(scores):
	for place in scores:
		name, points = scores[place][0], scores[place][1]
		print(str(place).rjust(2), str(name).ljust(20), str(points).rjust(5))

def add_highscore(points, name, scores):

	for place in scores:
		if points > scores[place]: # må sette inn score i place
			for shift_place in range(9, place-1, -1): # skifter listen et hakk nedover
				scores[shift_place] = scores[shift_place+1]
			scores[place] = [name, points]
			return scores
	return scores

def most_highscores(scores):
	players = {} #dict med spiller og antall higscores
	for place in scores:	#lager dict med spillere
		if scores[place][1] in players.keys():
			players[scores[place][1]] += 1
		else:
			players[scores[place][1]] = 1

	highest_number = -float('inf')
	for player in players:
		if players[player] > highest_number:
			highest_number = players[player]
			player_highest = player

	return player # players-listen er sortert slik at først plass blir returnert her hvis ingen andre har flere

def new_highscorelist():
	players = ['Albus', 'Fleur', 'Frank', 'Harry', 'Hermine',\
			 'Minerva', 'Ron', 'Severus', 'Sirius', 'Vernon']
	scores = {}

	for place in range(1, 11):
		player = players.pop(random.randint(0, len(players)-1))
		scores[place] = [player, 110-place*10]
	return scores

print(new_highscorelist())