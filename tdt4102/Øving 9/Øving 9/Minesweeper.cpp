#include "Minesweeper.h"
#include <random>
#include <ctime>
#include <algorithm> // std::min, std::max

struct Tile {
	bool open = false;
	bool mine = false;
	bool flag = false;
};

Minesweeper::Minesweeper(int width, int height, int mines)
	: WIDTH(width), HEIGHT(height), MINES(mines), GAMEOVER(false)
{
	createEmptyBoard();
	fillBoard();
}

Minesweeper::~Minesweeper() 
{	
	for (int row = 0; row < HEIGHT; ++row) {
		delete [] board[row];
	}
	delete[] board;
}

bool Minesweeper::isGameOver() const {
    return GAMEOVER;
}

bool Minesweeper::isTileOpen(int row, int col) const {
	return board[row][col].open;
	//return false;
}

bool Minesweeper::isTileMine(int row, int col) const {
	return board[row][col].mine;
	//return false;
}

bool Minesweeper::isTileFlag(int row, int col) const
{
	return board[row][col].flag;
}

void Minesweeper::openTile(int row, int col) {
	board[row][col].open = true;
	GAMEOVER = GAMEOVER || board[row][col].mine; // stays permanently true after one mine has been opened
	
	openAdjecentMines(row, col);
}

// calls openTiles for adjecent Tiles if they have no adjecent mines
void Minesweeper::openAdjecentMines(int row, int col)
{
	using std::max;
	using std::min;
	
	if (numAdjacentMines(row, col) == 0) {
		// open adjecent tiles
		for (int r = max(0, row - 1); r < min(HEIGHT, row + 2); ++r) {
			for (int c = max(0, col - 1); c < min(WIDTH, col + 2); ++c) {
				if (!board[r][c].mine && !board[r][c].open) { // 
					openTile(r, c);
				}
				
			}
		}
	}
}

int Minesweeper::numAdjacentMines(int row, int col) const 
{	
	//int row_min = std::max(0, row - 1);
	//int row_max = std::min(HEIGHT, row + 1);
	using std::max;
	using std::min;

	int counter = 0;
	for (int r = max(0, row - 1); r < min(HEIGHT, row + 2); ++r) {
		for (int c = max(0, col - 1); c < min(WIDTH, col + 2); ++c) {
			// don't need to check for self, because if self is mine, then game is over anyway
			if (board[r][c].mine) {
				++counter;
			}
		}
	}

	return counter;
}

void Minesweeper::createEmptyBoard()
{
	board = new Tile*[HEIGHT];
	for (int i = 0; i < HEIGHT; i++) {
		board[i] = new Tile[WIDTH];
	}
}

void Minesweeper::fillBoard()
{
	// check if there are enough tiles for the mines
	int nrOfTiles = HEIGHT * WIDTH;
	if (nrOfTiles > MINES) {
		srand(time(nullptr));
		int placementCounter = 0;
		while (placementCounter < MINES) {
			// get random indexes
			int randRow = rand() % HEIGHT;
			int randCol = rand() % WIDTH;

			// check collision
			if (board[randRow][randCol].mine) {
				continue; // skip placement of mine
			}

			// place mine
			board[randRow][randCol].mine = true;
			++placementCounter;
		}
	}
	else {
		// #mines >= #tiles, fill entire board with mines
		for (int row = 0; row < HEIGHT; ++row) {
			for (int col = 0; col < WIDTH; ++col) {
				board[row][col].mine = true;
			}
		}
	}
}

void Minesweeper::changeFlag(int row, int col)
{
	board[row][col].flag = !board[row][col].flag; // changes flag
}

int Minesweeper::remainingMines() const
{
	// sjekker returner antall miner som ikke har flagg
	int unflaggedMines = 0;
	for (int row = 0; row < HEIGHT; ++row) {
		for (int col = 0; col < WIDTH; ++col) {
			if (board[row][col].flag && board[row][col].mine) {
				++unflaggedMines;
			}
		}
	}
	return MINES - unflaggedMines;
}
