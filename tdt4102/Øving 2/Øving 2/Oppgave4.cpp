#include <iostream>
#include "Header.h"
#include <cmath>


double discriminant(double a, double b, double c)
{
	return b*b - 4 * a*c;
}

void printRealRoots(double a, double b, double c)
{
	double discriminantCalc = discriminant(a, b, c);
	int numberOfSolutions = 0;

	if (discriminantCalc > 0) {
		numberOfSolutions = 2; //more than one solution
	}
	else if (discriminantCalc == 0) {
		numberOfSolutions = 1; //exactly one solution
	}

	double root1 = 0, root2 = 0;

	switch (numberOfSolutions)
	{
		case 1:
			root1 = -b / (2*a);
			std::cout << "Dette andregrads-polynomet har løsning " << root1 << std::endl;
			break;
		case 2:
			root1 = (-b + sqrt(discriminantCalc) / (2 * a));
			root2 = (-b - sqrt(discriminantCalc) / (2 * a));
			std::cout << "Dette andregrads-polynomet har løsning " << root1 << " og " << root2 << std::endl;
			break;
		default:
			std::cout << "Dette andregrads-polynomet har ingen reelle løsninger" << std::endl;
			break;
	}
}

void solveQuadraticEquation()
{
	std::cout << "Skriv inn annengradskoefisienten (a): ";
	double a = inputDouble();
	std::cout << "Skriv inn førstegradskoefisienten (b): ";
	double b = inputDouble();
	std::cout << "Skriv inn konstantleddet (c): ";
	double c = inputDouble();
	std::cout << std::endl;

	printRealRoots(a, b, c);
}
