#include <iostream>
#include <clocale>
using namespace std;

int fibonacci(int n);
void triangleNumbersBelow(int n);
bool isTriangleNumber(int n);
int squareNumberSum(int n);
float max(float a, float b);
bool isPrime(int n);
void naivePrimeSearch(int n);
int findGreatestDivisor(int n);
void compareListOfNumbers(double l[], int size);



int fibonacci(int n)
{
	int a = 0;
	int b = 1;
	cout << "Fibonacci numbers:" << endl;
	for (int x = 1; x < n; x++) {
		int temp = b;
		b = a + b;
		a = temp;
		cout << x << " - " << b << endl;
	}
	cout << "----" << endl;
	return b;
}

void triangleNumbersBelow(int n)
{
	int acc = 1;
	int num = 2;
	cout << "Triangle numbers below " << n << ":" << endl;
	while (acc + num < n) {
		acc = acc + num;
		num++;
		cout << acc << endl;
	}
	cout << endl;
}

bool isTriangleNumber(int n)
{
	int acc = 1;
	while (n > 0) {
		n -= acc;
		acc++;
	}
	return n == 0;
}

int squareNumberSum(int n)
{
	int totalSum = 0;
	for (int i = 0; i<n; i++) {
		totalSum += i*i;
		cout << i*i << endl;
	}
	cout << totalSum << endl;
	return totalSum;
}

float max(float a, float b)
{
	if (a>b) {
		cout << "A is greater than b" << endl;
		return a;
	}
	else {
		cout << "B is greater than or equal to A" << endl;
		return b;
	}
}

bool isPrime(int n)
{
	bool primeness = true;
	for (int j = 2; j<n; j++) {
		if (n % j == 0) {
			primeness = false;
			break;
		}
	}
	return primeness;
}

void naivePrimeSearch(int n)
{
	for (int number = 2; number < n; number++) {
		if (isPrime(number)) {
			cout << number << " is a prime" << endl;
		}
	}
}

int findGreatestDivisor(int n)
{
	for (int divisor = n - 1; divisor>0; divisor--) {
		if (n % divisor == 0) {
			return divisor;
		}
	}
}

void compareListOfNumbers(double l[], int size)
{
	int r[] = { 0,0,0 };

	for (int i = 0; i < size; i++) {
		double num = l[i];

		if (num < 0) {
			r[0]++;
		}
		else if (num == 0) {
			r[1]++;
		}
		else {
			r[2]++;
		}
	}
	cout << r[0] << " numbers were below zero" << endl;
	cout << r[1] << " numbers were zero" << endl;
	cout << r[2] << " numbers were greater than zero" << endl;
}


int main()
{
	int n = 30;

	//system("chcp 1252"); //Norsk tegnsett
	setlocale(LC_ALL, "nb-NO");
	cout << "æøåæøåaøsdfllas" << endl;

	cout << endl;
	fibonacci(n);

	cout << endl;
	triangleNumbersBelow(n);

	cout << endl;
	cout << isTriangleNumber(n) << endl;
	
	cout << endl;
	cout << "19 prime? " << isPrime(19) << endl;

	cout << endl;
	naivePrimeSearch(50);

	cout << endl;
	double list[] = { -1.2, -23.0, 43.0, 1.0, 0, 0, 0 };
	compareListOfNumbers(list, 7);
	
	
	return 0;
}
