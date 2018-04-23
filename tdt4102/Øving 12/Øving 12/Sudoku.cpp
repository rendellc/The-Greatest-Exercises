#include "Sudoku.h"
#include "Array2D.h"
#include <String>

Sudoku::Sudoku(size_t N)
	: N(N), board(N*N, N*N)
{
	// init array
	for (size_t row = 0; row < N*N; ++row) {
		for (size_t col = 0; col < N*N; ++col) {
			board.set(row, col, Cell(0));
		}
	}
}

Sudoku::Sudoku(const Sudoku& rhs)
	: N(rhs.N)
	, board(rhs.board)
{}

bool operator< (const Cell& lhs, const Cell& rhs) {
	return lhs.number < rhs.number;
}

const Array2D<Cell> Sudoku::getBoard() const {
	return board;
}

const size_t Sudoku::getSize() const {
	return N;
}