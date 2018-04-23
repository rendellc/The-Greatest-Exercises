#include <iostream>
#include <ctime>
#include "cannonball.h"
#include "utilities.h"

void functionTesting();
void utilitiesTesting();


int main()
{
	using namespace std;
	
	// cout << "acclY\t" << acclY() << endl;
	// cout << "velY\t" << velY(25.0, 0.0) << "\t" << velY(25.0, 2.5) << "\t" << velY(25.0, 5.0) << endl;
	// cout << "posX\t" << posX(50, 0) << "\t" << posX(50, 2.5) << "\t" << posX(50, 5.0) << "\t" << endl;
	// cout << "posY\t" << posY(25,0) << "\t" << posY(25, 2.5) <<  "\t" << posY(25, 5.0) << "\t" << endl;

	// functionTesting();
	// utilitiesTesting();

	playTargetPractice();

	return 0;
}

// tester funksjonene fra oppgave 4
void functionTesting()
{
	using namespace std;

	double theta = 0;
	double absVelocity = 0;
	double velocityX = 0;
	double velocityY = 0;
	double userGuess = 0;
	double guessError = 5;
	bool correctGuess = false;
	
	do{
		getUserInput(&theta, &absVelocity);

		getVelocityVector(theta, absVelocity, &velocityX, &velocityY);

		cout << "Gjett avstanden: ";
		cin >> userGuess;

		guessError = targetPractice(userGuess, velocityX, velocityY);

		if (guessError < 5) {
			correctGuess = true;
		}
		else {
			cout << "Du bommet med " << guessError << " meter. " << endl;
		}
	} while (!correctGuess);
}

void utilitiesTesting()
{
	using namespace std;
	srand(time(NULL)); // seed til tilfeldige tall

	const int N = 30;
	const int LOW = 50;
	const int HIGH = 55;

	cout << "\nrandomWithLimits" << endl;
	for (int i = 0; i < N; i++) {
		cout << randomWithLimits(LOW, HIGH) << endl;
	}
	cout << "\nmodernRandomWithLimits" << endl;
	for (int i = 0; i < N; i++) {
		cout << modernRandomWithLimits(LOW, HIGH) << endl;
	}
}

