#include <string>
#include "globals.h"
#include "utils.h"
#include "Card.h"
using namespace std;

void Card::initialize(Suit s, Rank r)
{
	this->s = s;
	this->r = r;
	this->invalid = false;
}

string Card::toString()
{
	if (this->invalid) {
		return "Invalid card";
	}
	else {
		CardStruct card;
		card.s = this->s;
		card.r = this->r;
		return ::toString(card);
	}
}

string Card::toStringShort()
{
	if (this->invalid) {
		return "Invalid card";
	}
	else {
		CardStruct card;
		card.s = this->s;
		card.r = this->r;
		return ::toStringShort(card);
	}
}
