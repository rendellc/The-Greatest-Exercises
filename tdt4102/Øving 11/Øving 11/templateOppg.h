#pragma once
#include <random>
#include <ctime>
#include <string>
#include <algorithm>
#include <iostream>

namespace diy {

	template<typename T>
	void swap(T& left, T& right) {
		T temp = left;
		left = right;
		right = temp;
	}

	template<typename T>
	void shuffle(T* table, size_t length) {
		std::srand(std::time(NULL));
		for (size_t i = 0; i < length; ++i) {
			size_t randomIndex = (std::rand() % length);
			swap<T>(table[i], table[randomIndex]);
		}
	}

}; // end namespace diy

void shuffleTest() {
	int a[] = { 1,2,3,4,5,6,7,8,9 };
	for (const auto& iter : a) { std::cout << iter << '\n'; }
	diy::shuffle(a, 9);
	std::cout << std::endl;
	for (const auto& iter : a) { std::cout << iter << '\n'; }
	std::cout << std::endl;

	double b[] = { 1.2,2.2,3.4,4.1,-1.5,10.3,134.1,12.2,9.0 };

	/*
	std::string c[] = { "one", "two", "three", "four" };
	shuffle(c, 4);
	for (const auto& iter : c) { std::cout << iter << '\n'; }
	std::cout << std::endl;
	for (const auto& iter : c) { std::cout << iter << '\n'; }
	std::cout << std::endl;
	*/
}


