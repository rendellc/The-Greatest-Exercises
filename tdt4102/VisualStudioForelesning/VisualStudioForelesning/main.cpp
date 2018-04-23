#include <iostream>
using namespace std;

int sumList(int v[], int length);

/*
int main() {
	int v[] = { 1, 2, 3 };
	cout << sumList(v, 3) << endl;
	return 0;
}
*/

int sumList(int v[], int length) {
	int sum = 0;
	for (int i = 0; i < length; i++) {
		sum += v[i];
	}
	return sum;
}