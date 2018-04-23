#include <iostream>
#include "Header.h"

// a)
void inputIntegersUsingLoopAndPrintSum()
{
	int numInput = 0;
	int numSum = 0;

	std::cout << "Skriv inn 0 for � summere og avslutte" << std::endl;
	do {
		std::cin >> numInput;
		numSum += numInput;
	} while (numInput != 0); 
	// bruker en do-while loop fordi man ikke vet antall tall som skal summeres p� forh�nd
	// hvis jeg hadde det med � skrive inn antallet p� forh�nd ville en for-loop v�rt best

	std::cout << "Summen av tallene: " << numSum << std::endl;
}

// c)
double inputDouble()
{
	double num = 0.0;

	// std::cout << "Skriv inn et desimaltall: ";
	std::cin >> num;

	return num;
}

// d)
void convertNOKtoEUR0()
{
	double nokValue = 0.0;
	double euroValue = 0.0;
	double conversionRateNOKtoEURO = 9.64;

	do {
		std::cout << "Skriv inn et positivt bel�p (NOK): ";
		std::cin >> nokValue;
	} while (nokValue < 0);

	// m� bruke inputDouble fordi den returnerer og tar inn et desimaltall
	// 

	euroValue = nokValue / conversionRateNOKtoEURO;

	std::cout.setf(std::ios::fixed);
	std::cout.setf(std::ios::showpoint);
	std::cout.precision(2);
	std::cout << nokValue << " kr tilsvarer " << euroValue << " euro." << std::endl;


}


