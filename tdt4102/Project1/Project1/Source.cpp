#include <iostream>
#include <fstream>
using namespace std;

class Year {
public:
	static bool isLeapYear(int year) {
		return year % 4 == 0;
	}
};

int main() {

	cout << "-5 % 2\t" << (-5) % 2 << endl;


	cout << boolalpha << Year::isLeapYear(2016);
	system("pause");
	return 0;
}