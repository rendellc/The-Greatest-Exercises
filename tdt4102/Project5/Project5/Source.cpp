#include <iostream>
using namespace std;

int main() 
{
	int found = 0, value = 5;

	if (!found || --value == 0) {
		cout << "!found = " << !found << endl;
		cout << "danger ";

	}
	cout << "value = " << value << endl;

	system("pause");
	return 0;
}