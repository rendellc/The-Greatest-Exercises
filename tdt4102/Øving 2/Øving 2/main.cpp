#include <iostream>
#include <clocale>
#include "Header.h"



int main()
{
	setlocale(LC_ALL, "nb-NO");

	menySystem();

	//inputAndPrintInteger();

	//int number = inputInteger();
	//std::cout << "Du skrev: " << number << std::endl;

	//inputIntegersAndPrintSum();

	/*
	for (int i = 10; i < 20; i++) {
		if (isOdd(i)) {
			std::cout << i << " er et oddetall" << std::endl;
		}
		else {
			std::cout << i << " er et partall" << std::endl;
		}
	}
	*/

	return 0;
}
