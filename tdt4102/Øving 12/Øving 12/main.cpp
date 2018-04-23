//#define NDEBUG
#include <iostream>
#include <string>
#include "Sudoku.h"
#include "SudokuIO.h"
#include "SudokuSolver.h"



int main() 
{
	Sudoku game(IO::readFile("sudokuTest.txt"));
	IO::printBoard(game);
	//bool fileWriteSuccess = IO::writeFile(game, "sudokuTestWrite2x2.txt");
	
	/*
	#ifndef NDEBUG 
	//std::cout << "fileWriteSuccess: " << fileWriteSuccess << std::endl;
	std::cout << "Debug marker" << std::endl;
	//system("pause"); 
	#endif
	*/



	SudokuSolver solver(game);
	
	solver.intersectionAtPosition(0, 2);

	
	system("pause");
	return 0;
}