#pragma once

int randomWithLimits(int lowerLimit, int upperLimit);

int modernRandomWithLimits(int lowerLimit, int upperLimit);

void swapNumbers(int* num1, int* num2);

void printArray(int table[], int SIZE);

void randomizeArray(int table[], int SIZE);

void insertionSortArray(int table[], int SIZE);

int medianOfArray(int table[], int SIZE);

// NB: size of table must be 1 greater than SIZE (appends '\0' to the end)
void randomizeCString(char table[], int SIZE, char minBound, char maxBound);

// NB: size of table must be 1 greater than numberOfGrades (appends '\0' to the end)
void readInputToCString(char table[], int numberOfGrades, char minBound, char maxBound);

int countOccurencesOfCharacter(char table[], int SIZE, char character);