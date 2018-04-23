#pragma once
#include "Sudoku.h"
#include <string>

class Sudoku; 
// should not be necessary

namespace IO
{
	namespace setting {
		const size_t spacing = 1; // spaces between columns
		const char spaceSeperator = ' ';
		const char rowSeperator = ' ';
		const char colSeperator = ' ';
		const char rowColSeperatorIntersection = ' ';
		const char fileRowSeperator = '\t';
	}
	void printBoard(const Sudoku& game);
	bool writeFile(const Sudoku& game, std::string filename);
	Sudoku readFile(std::string filename);
}