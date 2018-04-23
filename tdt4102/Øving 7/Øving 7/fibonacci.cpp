#include "fibonacci.h"
#include "utils.h"
#include <iostream>
using namespace std;

void fillInnFibonacciNumbers(int result[], int length)
{
	if (length >= 1)
		result[0] = 0;
	if (length >= 2)
		result[1] = 1;
	if (length >= 3) {
		for (int i = 2; i < length; i++) {
			result[i] = result[i - 2] + result[i - 1];
		}
	}
}

void createFibonacci()
{
	cout << "How many Fibonacci numbers should be generated? ";
	int length;
	do {	
		cin >> length;
	} while (length < 0);

	int* result = new int[length];

	fillInnFibonacciNumbers(result, length);
	
	printArray(result, length);

	delete[] result;
}
