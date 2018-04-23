#include <iostream>
using namespace std;

void changeVariableUsingPointer(int* pointer, int newInt)
{
	*pointer = newInt;
}

int main()
{
	int x = 31;
	int* pointer = &x;
	cout << "x: " << x << endl;
	cout << "&x: " << x << endl;
	cout << "Pointer: " << pointer << endl;
	cout << "*Pointer: " << *pointer << endl;

	int newInt = -10;

	changeVariableUsingPointer(pointer, newInt);

	cout << "x: " << x << endl;
	cout << "&x: " << x << endl;
	cout << "Pointer: " << pointer << endl;
	cout << "*Pointer: " << *pointer << endl;

	return 0;
}