#pragma once

// a)
double acclY();

// b)
double velY(double initVelocityY, double time);

// c)
double posX(double initVelocity, double time);
double posY(double initVelocity, double time);

// d)
void printTime(double time);

// e)
double flightTime(double initVelocityY);


// Oppgave 4
void getUserInput(double *theta, double *absVelocity);

double getVelocityX(double theta, double absVelocity);
double getVelocityY(double theta, double absVelocity);

void getVelocityVector(double theta, double absVelocity,
	double *velocityX, double *velocityY);

double getDistanceTraveled(double velocityX, double velocityY);

double targetPractice(double distanceToTarget,
	double velocityX,
	double velocityY);

// Oppgave 6
void playTargetPractice();