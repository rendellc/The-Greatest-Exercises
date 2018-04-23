#include "Sudoku.h"
#include "SudokuIO.h"
#include <fstream>
#include <string>
#include <cassert>

namespace IO 
{
	std::ostream& operator<<(std::ostream& out, const Cell& cell) {
		out << cell.number;
		return out;
	}

	template<typename T>
	void printTimesOfChar(const size_t howMany, const T& character) {
		for (size_t _ = 1; _ <= howMany; ++_) {
			std::cout << character;
		}
	};

	void printBoard(const Sudoku& game) {
		using std::cout; using std::endl;

		decltype(auto) board = game.getBoard();
		decltype(auto) N = game.getSize(); // boardsize is N^2 x N^2 
		
		for (size_t row = 0; row < N*N; ++row) {
			for (size_t col = 0; col < N*N; ++col) {
				cout << board.get(row, col);

				// print spacing
				printTimesOfChar(setting::spacing, setting::spaceSeperator);

				// check for seperation and print
				if (col % N == N - 1) {
					cout << setting::colSeperator;
					printTimesOfChar(setting::spacing, setting::spaceSeperator); // new space on other side of colSeperator
				}
			}
			cout << endl;
			if (row % N == N - 1) {
				// iterate over bigger grids (for 9x9 sudoku these are the 3x3 grid regions
				for (size_t gridCol = 0; gridCol < N; ++gridCol) {
					printTimesOfChar(N, setting::rowSeperator);
					// check for end and print intersection sign if not end
					if (gridCol != N - 1) {
						cout << setting::rowColSeperatorIntersection;
					}
				}
				cout << '\n';
			}
		}
	}

	bool writeFile(const Sudoku& game, std::string filename) {
		decltype(auto) board = game.getBoard();
		decltype(auto) N = game.getSize();
		assert(setting::fileRowSeperator != '\0'); // this will make readFile not work!

		std::ofstream file;
		file.open(filename);
		if (file.fail()) {
			std::cerr << filename << " couldn't be opened" << std::endl;
			return false;
		}

		file << N << '\n'; // first line is board size
		// add board to file
		for (size_t row = 0; row < N*N; ++row) {
			for (size_t col = 0; col < N*N; ++col) {
				file << board.get(row, col) << setting::fileRowSeperator;
			}
			file << std::endl;
		}


		file.close();
		return true;
	}

	Sudoku readFile(std::string filename) {
		std::ifstream file;
		file.open(filename);
		if (file.fail()) {
			std::cerr << "Failed to open " << filename << std::endl;
			return Sudoku(0);
		}

		size_t N;
		file >> N; // first line/character of file is game size
		Sudoku game(N);

		int scannedElement;
		size_t row = 0, col = 0;
		while (file >> scannedElement) {
			game.board.set(row, col, Cell(scannedElement));

			++col;
			col %= N*N;
			if (col == 0) {
				++row;
			}
		}

		file.close();
		assert(row == N*N); // a check to see if file was parsed correctly
		return game; // file was (probably) parsed correctly
	}



} // end namespace IO