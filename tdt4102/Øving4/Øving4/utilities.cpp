#include <cstdlib>
#include <iostream>
#include <random>

int randomWithLimits(int lowerLimit, int upperLimit)
{
	using namespace std;
	int randomNumber = std::rand(); //generer et tilfeldig tall

									// tilpasser tallet til grensene
	upperLimit += 1; //inkluderer øvre grense
	randomNumber = randomNumber % (upperLimit - lowerLimit);
	randomNumber = randomNumber + lowerLimit;

	return randomNumber;
}

int modernRandomWithLimits(int lowerLimit, int upperLimit)
{
	using namespace std;
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<int> uniform(lowerLimit, upperLimit);

	int randomNumber = uniform(generator);

	return randomNumber;

}

void swapNumbers(int* num1, int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

void printArray(int table[], int SIZE)
{
	using namespace std;

	for (int i = 0; i < SIZE; i++) {
		cout << table[i] << endl;
	}
}

void randomizeArray(int table[], int SIZE)
{
	for (int i = 0; i < SIZE; i++) {
		table[i] = modernRandomWithLimits(0, 100);
	}
}


void insertionSortArray(int table[], int SIZE)
{
	int j = 0;
	int element = 0;
	for (int i = 1; i < SIZE; i++) {
		element = table[i];
		j = i;
		while (j > 0 && table[j - 1]>element) {
			table[j] = table[j - 1];
			j--;
		}
		table[j] = element;
	}
}

int medianOfArray(int table[], int SIZE)
{
	if (SIZE % 2 == 0) {
		// snittet av to elementer
		int middleIndex = SIZE / 2;
		int element1 = table[middleIndex - 1];
		int element2 = table[middleIndex];
		return (element1 + element2) / 2;
	} 
	else {
		// ett enkelt element
		int middleIndex = SIZE / 2;
		return table[middleIndex];		
	}
}


void randomizeCString(char table[], int numberOfGrades, char minBound, char maxBound)
{
	using namespace std;

	int randomCharCode = 0;
	char randomChar = '\0';
	
	for (int i = 0; i < numberOfGrades; i++) {
		int min = static_cast<int>(minBound);
		int max = static_cast<int>(maxBound);
		randomCharCode = modernRandomWithLimits(min, max);
		randomChar = static_cast<char>(randomCharCode);
		table[i] = randomChar;
	}
	table[numberOfGrades] = '\0';
}

bool boundCheck(char input, char minBound, char maxBound)
{
	input = toupper(input);
	minBound = toupper(minBound);
	maxBound = toupper(maxBound);

	if (input >= minBound && input <= maxBound)
		return true;
	else
		return false;
}

void readInputToCString(char table[], int numberOfGrades, char minBound, char maxBound)
{
	using namespace std;

	char input = 0;
	
	for (int i = 0; i < numberOfGrades; i++) {
		cin >> input;
		if (boundCheck(input, minBound, maxBound)) {
			table[i] = toupper(input);
		}
		else {
			cout << input << " is not between " << minBound << " and " << maxBound << endl;
			i--;
		}
	}
	table[numberOfGrades] = 0;
}

int countOccurencesOfCharacter(char table[], int SIZE, char character)
{
	int counter = 0;
	for (int i = 0; i < SIZE; i++) {
		if (table[i] == character)
			counter++;
	}
	return counter;
}