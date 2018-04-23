#include <iostream>
#include "tests.h"
#include "utilities.h"
#include "mastermind.h"
using namespace std;

/* *** Oppgave 1 ***
 a) v0 vil fortsatt være 5
*/ 

int main()
{
	int option = 0;
	cout << "1: testPart1()" << endl;
	cout << "2: testPart2()" << endl;
	cout << "3: testPart3()" << endl;
	cout << "4: Play Mastermind" << endl;
	cin >> option;
	switch (option) {
	case 1:
		cout << "\nrunning testPart1():" << endl;
		testPart1();
		break;
	case 2:
		cout << "\nrunning testPart2():" << endl;
		testPart2();
		break;
	case 3:
		cout << "\nrunning testPart3():" << endl;
		testPart3();
		break;
	case 4:
		playMastermind();
		break;
	default:
		break;
	}

}