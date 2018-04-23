#include <iostream>

void printArray(int arr[size], int size)
{
	for (auto& elem : arr) {
		std::cout << elem << " ";
	}
}

int main()
{
	int arr[10];

	int i = 0;
	for (auto& n : arr) {
		n = i++;
	}

	for (auto& n : arr) {
		std::cout << n << " ";
	}

	system("pause");
	return 0;
}

