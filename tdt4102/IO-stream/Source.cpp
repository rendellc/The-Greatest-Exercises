#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	// lese til fil
	ofstream outFile;
	outFile.open("hei.txt");

	if (outFile.fail()) {
		cerr << "Fant ikke filen! " << endl;
	}
	else {
		outFile << "Hoppsann!\n";
	}
	outFile.close();

	// lese fra fil
	ifstream inn;
	inn.open("hei.txt");
	if (inn.fail()) {
		cerr << "Fant ikke filen! " << endl;
	}
	
	while (!inn.eof()) {
		string text;
		getline(inn, text);
		cout << text << endl;
	}

	inn.close();

	system("pause");
}