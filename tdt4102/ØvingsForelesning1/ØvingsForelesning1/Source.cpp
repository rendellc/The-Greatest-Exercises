#include <iostream>

double myAbs(double number)
{
	if (number >= 0) {
		return number;
	}
	else {
		return -number;
	}
}

bool isEven(int number)
{
	return number % 2 == 0;
}

void parityInRange(int start, int end)
{
	using namespace std;
	
	for (int i = start; i <= end; i++) {
		if (isEven(i)) {
			cout << i << " er partall" << endl;
		} 
		else {
			cout << i << " er oddetall" << endl;
		}
	}
}

// 3: fizz
// 5: buzz
// 3og5: fizzbuzz

bool divisibleBy3(int n)
{
	return n % 3 == 0;
}

bool divisibleBy5(int n)
{
	return n % 5 == 0;
}

void fizzbuzz(int start, int end)
{
	using namespace std;

	for (int i = start; i < end; i++) {
		if (divisibleBy3(i) && divisibleBy5(i))
			cout << "fizzbuzz" << endl;
		else if (divisibleBy5(i))
			cout << "buzz" << endl;
		else if (divisibleBy3(i))
			cout << "fizz" << endl;
		else
			cout << i << endl;
	}
}
/*
int printAndFillArray()
{
	int *x = new int[];

	for (int i = 0; i < 5; i++) {
		
		std::cout << *x[i] << std::endl;
	}

	return *x;
}

int main()
{
	std::cout << myAbs(18) << std::endl;
	
	parityInRange(-5, 30);

	fizzbuzz(0, 100);

	printAndFillArray();

	return 0;
}

*/

int main()
{
	using namespace std;
	
	int x = 3;
	cout << x << "\t" << &x << endl;

	int *y = &x;
	*y = 4;
}