#include <iostream>
#include <string>
#include "header.h"
using namespace std;

int main()
{
	cin.sync_with_stdio(false);
	string input;

	while (cin >> input) {
		cout << recursiveReverse(input) << endl;
	}

	return 0;
}

void mySwap(char& left, char& right)
{
	char temp = left;
	left = right;
	right = temp;
}

string swapReverse(string& input)
{
	// bytt første og siste element
	// bytt andre og nest siste
	// etc.

	// hvis partall elementer
	int length = input.size();
	for (int i = 0; i < length / 2; i++) {
		mySwap(input[i], input[length - 1 - i]);
	}
	return input;
}

string recursiveReverse(string input)
{
	int length = input.length();

	if (length >= 2)
		return input.back() + recursiveReverse(input.substr(0, length - 1));

	return input;
}
