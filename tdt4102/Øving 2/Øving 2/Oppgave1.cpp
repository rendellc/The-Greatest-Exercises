#include <iostream>
#include "Header.h"

// a)
void inputAndPrintInteger()
{
	int tall = 0;
	
	std::cout << "Skriv inn et heltall: ";
	std::cin >> tall;
	std::cout << "Du skrev: " << tall << std::endl;
}

// b)
int inputInteger() 
{
	int tall = 0;

	//std::cout << "Skriv inn et heltall: ";
	std::cin >> tall;
	
	return tall;
}

// c)
void inputIntegersAndPrintSum()
{
	// Bruker inputInteger() for å hente tall fra brukeren
	// siden den returner en verdi som kan lagres i en variabel
	int num1 = inputInteger();
	int num2 = inputInteger();

	std::cout << "Summen av tallene: " << num1 + num2 << std::endl;
}

// e)
bool isOdd(int num)
{
	if (num % 2 == 0) {
		return false;
	}
	else {
		return true;
	}
}

// f)
void printHumanReadableTime(int totalSeconds)
{
	// calculate hours, minutes, seconds
	int hours = totalSeconds / 3600;
	int minutes = (totalSeconds - hours * 3600) / 60;
	int seconds = totalSeconds - (hours * 3600) - (minutes * 60);  

	// format and display
	if (hours != 1) {
		std::cout << hours << " timer, ";
	}
	else {
		std::cout << "1 time, "; 
	}

	if (minutes != 1) {
		std::cout << minutes << " minutter, ";
	}

	else {
		std::cout << "1 minutt, ";
	}

	if (seconds != 1) {
		std::cout << seconds << " sekunder" << std::endl;
	}
	else {
		std::cout << "1 sekund" << std::endl;
	}
}