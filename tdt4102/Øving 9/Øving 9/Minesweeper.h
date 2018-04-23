#pragma once

struct Tile;

class Minesweeper {
private:
	
	// game board
	Tile **board;
	const int WIDTH;
	const int HEIGHT;
	const int MINES;
	
	bool GAMEOVER;

	// utils
	void createEmptyBoard();
	void fillBoard();
	void openAdjecentMines(int row, int col);
public:
    Minesweeper(int width, int height, int mines);
    ~Minesweeper();

    bool isGameOver() const;
	int remainingMines() const;

    bool isTileOpen(int row, int col) const;
    bool isTileMine(int row, int col) const;
	bool isTileFlag(int row, int col) const;

    void openTile(int row, int col);
	void changeFlag(int row, int col);

    int numAdjacentMines(int row, int col) const;

    // Vi slår av autogenerert kopikonstruktør og tilordningsoperator for å unngå feil
    Minesweeper(const Minesweeper &) = delete;
    Minesweeper &operator=(const Minesweeper &) = delete;
};
