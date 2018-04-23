#include <iostream>
#include <cmath>
#include "cannonball.h"
#include "utilities.h"

const double GRAVITY = -9.81; // m/s^2
const double PI = 3.14;

double acclY()
{
	return GRAVITY;
}

double velY(double initVelocityY, double time)
{
	return initVelocityY + acclY()*time;
}

double posX(double initVelocity, double time)
{
	return initVelocity*time;
}

double posY(double initVelocity, double time)
{
	return initVelocity*time + (acclY()*time*time) / 2;
}

void printTime(double time)
{
	using namespace std;

	int remainingTime = static_cast<int>(time); // hvor mye av tiden som ikke har blitt gjort om til timer/minutter

	int hours = remainingTime % 3600;
	remainingTime -= hours * 3600;

	int minutes = remainingTime % 60;
	remainingTime -= minutes * 60;

	cout << hours << " : " << minutes << " : " << remainingTime << endl;
}

double flightTime(double initVelocityY)
{
	return -2 * initVelocityY / acclY(); //second solution for when posY = 0
}


// *** Oppgave 4 ***
void getUserInput(double *theta, double *absVelocity)
{
	using namespace std;

	cout << "Angle (grader): ";
	cin >> *theta;

	*theta = *theta * 180 / PI; // konverterer til radianer

	cout << "Speed: ";
	cin >> *absVelocity;
}

double getVelocityX(double theta, double absVelocity)
{
	return absVelocity*cos(theta);
}

double getVelocityY(double theta, double absVelocity)
{
	return absVelocity*sin(theta);
}

void getVelocityVector(double theta, double absVelocity,
	double *velocityX, double *velocityY)
{
	*velocityX = getVelocityX(theta, absVelocity);
	*velocityY = getVelocityY(theta, absVelocity);
}


double getDistanceTraveled(double velocityX, double velocityY)
{
	double time = flightTime(velocityY);
	return velocityX * time;
}

double targetPractice(double distanceToTarget,
	double velocityX, double velocityY)
{
	double distanceTraveled = getDistanceTraveled(velocityX, velocityY);
	double distanceFromTarget = distanceTraveled - distanceToTarget;
	
	return distanceFromTarget;
}

// *** Oppgave 6 ***
void playTargetPractice()
{
	using namespace std;

	// konstanter, innstillinger
	int MAX_ATTEMPTS = 10;
	int SHORTEST = 100; // kortest avstand til blink
	int LONGEST = 1000; // lengst avstand til blink

	// variabeldeklarasjoner
	double theta = 0;
	double absVelocity = 0;
	double velocityX = 0;
	double velocityY = 0;
	double deviationFromTarget = 0;

	// spill
	int blinkDistance = randomWithLimits(SHORTEST, LONGEST);
	cout << "Blinken har blitt plassert" << endl;

	for (int attempt = 0; attempt < MAX_ATTEMPTS; attempt++) {
		getUserInput(&theta, &absVelocity); // brukerinput

		// beregner x- og y-komponent
		getVelocityVector(theta, absVelocity, &velocityX, &velocityY);

		// beregner avvik
		deviationFromTarget = targetPractice(blinkDistance, velocityX, velocityY); 
		
		switch (-5 <= deviationFromTarget && deviationFromTarget <= 5) {
		case true:
			// seier
			cout << "Gratulerer, du traff blinken!" << endl;

			attempt = MAX_ATTEMPTS;
			return; //avslutter programmet
		default:
			// try again
			cout << "Du bommet med " << abs(deviationFromTarget) << " meter og skuddet var for ";
			if (deviationFromTarget < 0)
				cout << "kort " << endl;
			else
				cout << "langt " << endl;

			break;
		}	
	}

	// tapte spillet
	cout << "Du vant dessverre ikke denne gang :(" << endl;

}
