#include "SudokuSolver.h"
#include "Sudoku.h"
#include <algorithm> // std::set_intersection
#include <iterator>  // std::inserter
#include "testing_utils.h"

#ifndef NDEBUG
#define INTERSECT_DEBUG
#endif // !NDEBUG

SudokuSolver::SudokuSolver(const Sudoku& game)
	: N(game.N) 
	, board(game.board)
	, availableRow(new set_type[N*N])
	, availableCol(new set_type[N*N])
	, availableBox(new set_type[N*N])
{
	for (size_t i = 1; i <= N*N; ++i) {
		valueRangeSet.insert(static_cast<int>(i));
	}
	// initialize available sets
	for (size_t i = 0; i < N*N; ++i) {
		availableRow[i] = valueRangeSet;
		availableCol[i] = valueRangeSet;
		availableBox[i] = valueRangeSet;
	}
	updateAllAvailable();
}

SudokuSolver::~SudokuSolver() {
	delete[] availableBox;
	delete[] availableCol;
	delete[] availableRow;
}


size_t SudokuSolver::calculateBoxIndex(size_t boxNumber) const {
	size_t boxRow = boxNumber / (N*N); // rounds down to correct row
	size_t boxColumn = boxNumber % (N*N);
	
	/*__0___1___2__
	0:	0	3	6
	1:	27	30	33
	2:	54	57	60
	*/
	size_t index = boxRow*N*N*N + boxColumn*N;
	assert(index < N*N*N*N);
	return index;
}

void SudokuSolver::updateAvailablePosWithMode(size_t row, size_t col, search_mode mode) const {
	switch (mode)
	{
	case SudokuSolver::ROW: 
	{
		set_type* temp = &availableRow[row];
		// iterate over row
		for (size_t iCol = 0; iCol < N*N; ++iCol) {
			// check if element is in row
			auto iter = temp->find(board.get(row, iCol).number);

			// remove if found
			if (iter != temp->end()) {
				temp->erase(iter);
			}
		}

		break;
	}
	case SudokuSolver::COLUMN:
	{
		set_type* temp = &availableCol[col];
		// iterate over column
		for (size_t iRow = 0; iRow < N*N; ++iRow) {
			// check if element is in row
			auto iter = temp->find(board.get(iRow, col).number);

			// remove if found
			if (iter != temp->end()) {
				temp->erase(iter);
			}
		}
		break;
	}
	case SudokuSolver::BOX: 
	{
		// calculate indexes to be used during iteration
		const size_t boxNumber = calculateBoxNumber(row, col);
		const size_t boxRowIndex = boxNumber / (N*N);
		const size_t boxColumnIndex = boxNumber % (N*N);

		set_type* temp = &availableBox[boxNumber];

		// iterate over box
		// starts at upper left side, goes left to right, up to down
		for (size_t row = boxRowIndex; row < boxRowIndex + N; ++row) {
			for (size_t col = boxColumnIndex; col < boxColumnIndex + N; ++col) {
				auto iter = temp->find(board.get(row, col).number);

				// remove if found
				if (iter != temp->end()) {
					temp->erase(iter);
				}
			}
		}
		break;
	}
	default:
		std::cerr << "Invalid search mode: " << mode << std::endl;
		break;
	}
}


void SudokuSolver::updateAvailableAtPosition(size_t row, size_t col) {
	// update row
	for (size_t row = 0; row < N*N; ++row) {
		updateAvailablePosWithMode(row, 0, ROW);
	}

	// update column
	for (size_t col = 0; col < N*N; ++col) {
		updateAvailablePosWithMode(0, col, ROW);
	}

	// update boxes
	for (size_t iRow = 0; iRow < N; ++iRow) {
		for (size_t iCol = 0; iCol < N; ++iCol) {
			updateAvailablePosWithMode(iRow*N, iCol*N, BOX);
		}
	}
}


void SudokuSolver::updateAllAvailable() {
	// update all positions
	// very wasteful
	for (size_t row = 0; row < N*N; ++row) {
		for (size_t col = 0; col < N*N; ++col) {
			updateAvailableAtPosition(row, col);
		}
	}
}


void SudokuSolver::tripleSetIntersection(const set_type& set1, const set_type& set2, const set_type& set3, set_type& resultSet) const {
	set_type temp;
	
	std::set_intersection(set1.begin(), set1.end()
		, set2.begin(), set2.end()
		, std::inserter(temp, temp.begin())
		);

	#ifdef INTERSECT_DEBUG
	std::cout << "\ntripleSetIntersection print (1):\n";
	test::printSet(temp);
	#endif

	std::set_intersection(temp.begin(), temp.end()
		, set3.begin(), set3.end()
		, std::inserter(resultSet, resultSet.begin())
		);

	#ifdef INTERSECT_DEBUG
	std::cout << "\ntripleSetIntersection print (2):\n";
	test::printSet(temp);
	#endif
}


size_t SudokuSolver::calculateBoxNumber(size_t row, size_t col) const {
	/*
	 col/N == 0			col/N == 1			col/N == 2
	(0,0) (0,1) (0,2) | (0,3) (0,4) (0,5) | (0,6) (0,7) (0,8)
	(1,0) (1,1) (1,2) | (1,3) (1,4) (1,5) | (1,6) (1,7) (1,8)
	*/

	assert(N != 0);
	size_t boxCol = col / N;
	size_t boxRow = row / N;

	return boxRow * N + boxCol;
}

SudokuSolver::set_type SudokuSolver::intersectionAtPosition(size_t row, size_t col) const {
	size_t box = calculateBoxNumber(row, col);
	
	set_type rowSet = availableRow[row];
	set_type colSet = availableCol[col];
	set_type boxSet = availableBox[box];
	set_type resultSet;

	tripleSetIntersection(rowSet, colSet, boxSet, resultSet);

	#ifdef INTERSECT_DEBUG
	std::cout << "(row, col) = (" << row << ", " << col << ")\n";
	std::cout << "\nrowSet:\n"; test::printSet(rowSet);
	std::cout << "\ncolSet:\n"; test::printSet(colSet);
	std::cout << "\nboxSet:\n"; test::printSet(boxSet);
	std::cout << "\nresultSet:\n"; test::printSet(resultSet);
	#endif

	return resultSet;
}

