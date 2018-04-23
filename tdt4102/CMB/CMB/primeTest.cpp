#include <iostream>
using namespace std;


bool isPrimeNumber(int n) 
{
	if (n > 2) {
		for (int i = 2; i < n / 2 + 1; i++) {
			if (n%i == 0)
				return false;
		}
	}
	return true;
}

int main_prime()
{
	int input;

	while (cin >> input) {
		cout << isPrimeNumber(input) << endl;;
	}
	return 0;
}