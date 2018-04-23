#pragma once
#include "Array2D.h"
#include "SudokuIO.h"
#include <iostream>

struct Cell {
	int number;

	Cell() : number(0) {}
	Cell(int number) : number(number) {}
	Cell(const Cell& cell) : number(cell.number) {}
};

class Sudoku {
private:
	const size_t N; // size of board, N^2 * N^2
	
	/*  sudoku board is represented as 
		2d array of Cells */
	Array2D<Cell> board; 
public:
	Sudoku(size_t N);

	Sudoku(const Sudoku& rhs);

	const size_t getSize() const;
	const Array2D<Cell> getBoard() const;


	friend class SudokuSolver;
	friend Sudoku IO::readFile(std::string filename);
};