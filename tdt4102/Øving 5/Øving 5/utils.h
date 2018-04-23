#pragma once
#include "globals.h"
#include <string>
using namespace std;


string suitToString(Suit suit);
string rankToString(Rank rank);
string toString(CardStruct card);
string toStringShort(CardStruct card);

int randomNumberGen(int lowerBound, int upperBound);