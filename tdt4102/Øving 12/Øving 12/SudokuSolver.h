#pragma once
#include "Sudoku.h"
#include <set>

class SudokuSolver {
private:
	enum search_mode {ROW, COLUMN, BOX};
	using set_type = std::set<int>;
	using board_type = Array2D<Cell>;
	
	const board_type board;
	const size_t N;

	set_type* availableCol;
	set_type* availableRow;
	set_type* availableBox;
	set_type valueRangeSet;

	// intersection of three sets
	void tripleSetIntersection(const set_type& set1, const set_type& set2, const set_type& set3, set_type& resultSet) const;


	//void updateAvailable(const Sudoku& game);
	set_type intersectionAtPosition(size_t row, size_t col) const;


	/*	return a number between 0 and n^2 representing
		the box at (row,col)	*/
	size_t calculateBoxNumber(size_t row, size_t col) const;

	/*	returns a set containing non-conflicting
		elements in specified section */
	void updateAvailablePosWithMode(size_t row, size_t col, search_mode mode) const;

	/*  returns index of upper left corner of box */
	size_t calculateBoxIndex(size_t boxNumber) const;


	void updateAvailableAtPosition(size_t row, size_t col);

	void updateAllAvailable();




public:
	SudokuSolver(const Sudoku& game);
	~SudokuSolver();
	SudokuSolver() = delete;

	friend int main();
};