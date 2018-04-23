#include <iostream>
#include "Header.h"

// a)
void menySystem()
{
	std::cout << "0) Avslutt" << std::endl;
	std::cout << "1) Summer to tall" << std::endl;
	std::cout << "2) Summer flere tall" << std::endl;
	std::cout << "3) Konverter fra NOK til EURO" << std::endl;
	std::cout << "4) Skriv ut gangetabell" << std::endl;
	std::cout << "5) Løs et annengradspolynom" << std::endl;
	std::cout << "6) Beregn lån-innbetalinger" << std::endl;

	while (true) {
		std::cout << "\n\n";
		
		std::cout << "Hvilken funksjon ønsker du? (0-6)" << std::endl;

		int choice = inputInteger();

		switch (choice) {
		case 0:
			// end program
			return;
		case 1:
			std::cout << "Skriv inn to tall" << std::endl;
			inputIntegersAndPrintSum();
			break;
		case 2:
			inputIntegersUsingLoopAndPrintSum();
			break;
		case 3:
			convertNOKtoEUR0();
			break;
		case 4:
			multiplicationTable();
			break;
		case 5:
			solveQuadraticEquation();
			break;
		case 6:
			calculateLoanPayments();
			break;
		default:
			// wrong input
			std::cout << "Tall må være 0-6" << std::endl;
			break;
		}
	}
}


void multiplicationTable()
{
	int width = 0;
	int height = 0;

	std::cout << "Skriv inn bredden: ";
	width = inputInteger();

	std::cout << "Skriv inn høyden: ";
	height = inputInteger();

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			std::cout << (h + 1)*(w + 1) << "\t";
		}
		std::cout << std::endl;
	}

}