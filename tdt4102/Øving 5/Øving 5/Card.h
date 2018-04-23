#pragma once
#include "globals.h"
using namespace std;

class Card {
private:
	Suit s;
	Rank r;
	bool invalid;
public:
	Card::Card() { invalid = true; } //error constructor
	Card::Card(Suit s, Rank r) { initialize(s, r); } // constructor
	void initialize(Suit s, Rank r);
	string toString();
	string toStringShort();
	Suit getSuit() { return s; }
	Rank getRank() { return r; }
};