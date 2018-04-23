#include <iostream>
using namespace std;

int myRound(double d)
{
	int wholePart = static_cast<int>(d);
	double fracPart = d - wholePart;

	if (fracPart >= 0.50) {
		return wholePart + 1;
	}
	else {
		return wholePart;
	}
}


int coolRound(double d)
{
	if (d >= 0) {
		return static_cast<int>(d + 0.5);
	}
	else {
		return static_cast<int>(d - 0.5);
	}


int adjecent_find(int arr[], int first, int last)
{
	for (int i = first; i < (last-1); i++) {
		if (arr[i] == arr[i + 1]) {
			return i;
		}
	}
	// no adjecent found
	return -1;
}

void print_adjecent(int arr[], int size)
{
	int first = 0;
	int adjecent = -1;
	int index = -1; //index til første tall av et par

	while (first < (size - 1)) {
		index = adjecent_find(arr[], first, size);
		if (index != -1) {
			cout << arr[index] << " " << arr[index + 1] << endl;
		}

		first = index + 1; //moves to next index
	}
}

int main()
{
	cout << myRound(0.7) << "\n" << myRound(912.2) << endl;

	int x[] = { 0,4,4,5,3,3,3,7 };
	int size = 8;

	print_adjecent({ 0,4,4,5,3,3,3,7 }, 8);

	return 0;
}