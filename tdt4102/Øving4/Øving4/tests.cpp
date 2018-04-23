#include <iostream>
#include <cmath>
#include "utilities.h"
#include "tests.h"
using namespace std;

void incrementByValueNumTimes(int* startValue, int increment, int numTimes)
{
	for (int i = 0; i < numTimes; i++) {
		*startValue += increment;
	}
}

void testPart1()
{
	// incrementByValueNumTimes
	int v0 = 5;
	int increment = 2;
	int iterations = 10;
	incrementByValueNumTimes(&v0, increment, iterations);
	cout << "v0: " << v0
		<< " increment: " << increment
		<< " iterations: " << iterations << endl;
		//<< " result: " << result << endl;
	
	// swap
	int num1 = 30;
	int num2 = -50;
	cout << "\nBefore:\n";
	cout << "num1: " << num1
		<< "\nnum2: " << num2 << endl;

	swapNumbers(&num1, &num2);
	cout << "After:\n";
	cout << "num1: " << num1
		<< "\nnum2: " << num2 << endl;
}

void testPart2()
{
	const int SIZE = 20;
	
	int percentages[SIZE];

	randomizeArray(percentages, SIZE);
	printArray(percentages, SIZE);

	cout << endl;
	swapNumbers(&percentages[0], &percentages[SIZE-1]);
	printArray(percentages, SIZE);
	cout << "Median: " << medianOfArray(percentages, SIZE) << endl;

	cout << endl;
	insertionSortArray(percentages, SIZE);
	printArray(percentages, SIZE);
	cout << "Median: " << medianOfArray(percentages, SIZE) << endl;
}

void testPart3()
{
	// Innstillinger
	const int GRADES_PER_YEAR = 8;
	const int NR_OF_YEARS = 5;
	const int NR_GRADES = 6; // antall forskjellige karakterer
	const char GRADES[NR_GRADES] = { 'A', 'B', 'C', 'D', 'E', 'F' };

	const int TOTAL_NR_GRADES = GRADES_PER_YEAR * NR_OF_YEARS;


	// *** PROGRAM ***
	char grades[TOTAL_NR_GRADES + 1] = {};

	// lag en tilfeldig liste med karakterer A-E
	// randomizeCString(grades, TOTAL_NR_GRADES, 'A', 'E');

	// bruker skriver inn karakterer
	readInputToCString(grades, TOTAL_NR_GRADES, 'A', 'E');
	
	cout << "grades: " << grades << endl;

	// --- Gjennomsnitt ---
	// telling
	int gradeCount[NR_GRADES] = {};
	for (int i = 0; i < NR_GRADES; i++) {
		gradeCount[i] = countOccurencesOfCharacter(grades, TOTAL_NR_GRADES, GRADES[i]);
	}
	
	// snitt
	int sumOfGrades = gradeCount[0] * 1
					+ gradeCount[1] * 2
					+ gradeCount[2] * 3
					+ gradeCount[3] * 4
					+ gradeCount[4] * 5;

	char average = 'A' + round(static_cast<float>(sumOfGrades) / TOTAL_NR_GRADES) - 1;
	cout << "Average grade: " << average << endl;


	//char inputGrades[GRADES_PER_YEAR + 1] = {};
	//readInputToCString(inputGrades, GRADES_PER_YEAR, 'A', 'F');
	//cout << inputGrades << endl;

	//cout << countOccurencesOfCharacter(grades, GRADES_PER_YEAR + 1, 'C') << endl;;


}