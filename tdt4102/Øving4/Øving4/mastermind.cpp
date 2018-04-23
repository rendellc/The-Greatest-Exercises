#include <iostream>
#include <algorithm> // std::min
#include "utilities.h"
#include "mastermind.h"
using namespace std;

void playMastermind()
{
	// Konstanter
	const int SIZE = 4; // antall tegn i koden
	const int LETTERS = 6; // antall forskjellige bokstaver
	const char FIRST_CHAR = 'A';
	const char LAST_CHAR = 'A' + (LETTERS - 1);
	const int NO_OF_TRIES = 15; // antall forsøk brukeren får på tippe

	// *** PROGRAM ***
	char code[SIZE + 1] = {};	code[SIZE] = 0; // lager tabell og setter siste element til 0
	char guess[SIZE + 1] = {};	guess[SIZE] = 0;

	// generer code
	randomizeCString(code, SIZE, FIRST_CHAR, LAST_CHAR);
	cout << "Kode på " << SIZE << " bokstaver generert.\n"
		<< "Koden består av tegn mellom " << FIRST_CHAR << " og " << LAST_CHAR << "\n"
		<< "Lykke til! " << endl;

	// cout << code << endl;

	int correctChar = 0;
	int correctCharAndPos = 0;
	
	// evig løkke versjon
	/*
	do {
		// gjett
		cout << "Gjett en kode: ";
		readInputToCString(guess, SIZE, FIRST_CHAR, LAST_CHAR);

		// sjekk riktige
		correctChar = checkCharacters(code, guess, SIZE, FIRST_CHAR, LAST_CHAR);
		correctCharAndPos = checkCharactersAndPosition(code, guess, SIZE);

		// skriv ut resultat
		printGuessResults(correctChar, correctCharAndPos);
	} while (correctCharAndPos < SIZE);	
	*/

	for (int i = NO_OF_TRIES; i >= 0; i--) {
		cout << "Du har " << i << " forsøk igjen " << endl;
		// gjett
		cout << "Gjett en kode: ";
		readInputToCString(guess, SIZE, FIRST_CHAR, LAST_CHAR);

		// sjekk riktige
		correctChar = checkCharacters(code, guess, SIZE, FIRST_CHAR, LAST_CHAR);
		correctCharAndPos = checkCharactersAndPosition(code, guess, SIZE);

		// skriv ut resultat
		printGuessResults(correctChar, correctCharAndPos);
		cout << endl;
		if (correctCharAndPos >= SIZE) { break; }

	}
	char playAgain = 'n';
	if (correctCharAndPos < SIZE) {
		// tapte spillet
		cout << "Beklager, det gikk dessverre ikke denne gangen :(\n"
			<< "Prøve igjen? (y/n) " << endl;
	}
	else {
		// vant spillet
		cout << "Gratulerer med seieren!\n"
			<< "Vil du prøve igjen? (y/n) " << endl;
	}
	
	// sjekker om brukeren vil spille igjen
	cin >> playAgain;
	if (playAgain == 'y') { playMastermind(); }
}

void printGuessResults(int correctChar, int correctCharAndPos)
{
	cout << "Du gjettet " << correctCharAndPos << " med riktig posisjon\n"
		<< "og " << correctChar << " riktige tegn. " << endl;
}

int checkCharactersAndPosition(char code[], char guess[], int SIZE)
{
	int correctCounter = 0;
	for (int i = 0; i < SIZE; i++) {
		if (code[i] == guess[i]) {
			correctCounter++;
		}
	}
	return correctCounter;
}

int checkCharacters(char code[], char guess[], int SIZE, char FIRST_CHAR, char LAST_CHAR)
{
	// code = { a e c f }
	// guess = { a b a e }

	int correctCount = 0;
	for (char ch = FIRST_CHAR; ch <= LAST_CHAR; ch++) {
		// teller ch i code og guess
		int codeCount = countOccurencesOfCharacter(code, SIZE, ch);
		int guessCount = countOccurencesOfCharacter(guess, SIZE, ch);

		correctCount += min(codeCount, guessCount);
	}

	return correctCount;
}