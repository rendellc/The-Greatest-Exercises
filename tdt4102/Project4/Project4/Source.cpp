#include <utility>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <ctime>
#include <algorithm>
#include <array>
using namespace std;

class Dice {
private:
	int value;
public:
	Dice(int value) : value(value) {}
	Dice() : value(0) {
		throwDice();
	}
	int get() const {
		return value;
	}

	int throwDice() {
		return value = 1 + (rand() % 100);
	}


	friend bool operator<(const Dice& lhs, const Dice& rhs);
};

bool operator<(const Dice& lhs, const Dice& rhs) {
	return lhs.value < rhs.value;
}

int main()
{
	srand(time(NULL));
	//set<string> namesInUse;
	
	array<Dice, 5> chances;
	for (int i = 0; i < chances.size(); ++i) {
		chances[i] = Dice();
	}

	sort(chances.begin(), chances.end());

	for (auto d : chances) {
		cout << d.get() << endl;
	}

	sort(chances.begin(), chances.end());

	auto it = chances.begin();
	//it->throwDice();

	/*
	try {
		throw InfileError("Filename.file", "me mess messag message");
	}
	catch (InfileError& e){
		cout << e.what() << endl;
	}

	if (nullptr)
		cout << "life is great";
	*/
	system("pause");
	return 0;
}