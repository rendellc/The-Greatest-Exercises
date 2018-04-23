#include <map>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

int main()
{

	const int MAX = 10;
	const int LENGTH = 30;
	int randomList[LENGTH];

	srand(time(NULL));
	for (int i = 0; i < LENGTH; i++) {
		randomList[i] = rand() % MAX;
	}

	map<int, int> counter;
	for (int i = 0; i < LENGTH; i++) {
		int number = randomList[i];
		counter[number]++;
	}
	
	for (int num = 0; num < MAX; num++) {
		cout << num << ": " << counter[num] << endl;
	}

	system("pause");
	return 0;
}

