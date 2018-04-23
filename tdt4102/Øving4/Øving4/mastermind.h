#pragma once

void playMastermind();

int checkCharactersAndPosition(char code[], char guess[], int SIZE);

int checkCharacters(char code[], char guess[], int SIZE, char FIRST_CHAR, char LAST_CHAR);

void printGuessResults(int correctChar, int correctCharAndPos);