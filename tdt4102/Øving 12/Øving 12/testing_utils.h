#pragma once
#include "SudokuSolver.h"

namespace test
{
	using std::set;
	using std::cout;
	using std::endl;


	void printSet(const set<int>& set) {
		for (const auto& iter : set) {
			cout << iter << '\n';
		}
	}


};