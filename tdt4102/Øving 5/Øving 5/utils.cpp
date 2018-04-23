#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <random>
#include <ctime> // time()
#include "globals.h"
#include "utils.h"
using namespace std;

// *** extra ***

string intToString(int number) 
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}

int randomNumberGen(int lowerBound, int upperBound)
{
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<int> uniform(lowerBound, upperBound);

	return uniform(generator);
}

// *** main utilities ***

string suitToString(Suit suit)
{
	switch (suit) {
	case CLUBS:		return "Clubs";
	case DIAMONDS:	return "Diamonds";
	case HEARTS:	return "Hearts";
	case SPADES:	return "Spades";
	default: cerr << "ERROR - suitToString"; return "";
	}
}

string rankToString(Rank rank)
{
	switch (rank) {
	case TWO:	return "Two";
	case THREE:	return "Three";
	case FOUR:	return "Four";
	case FIVE:	return "Five";
	case SIX:	return "Six";
	case SEVEN: return "Seven";
	case EIGHT: return "Eight";
	case NINE:	return "Nine";
	case TEN:	return "Ten";
	case JACK:	return "Jack";
	case QUEEN: return "Queen";
	case KING:	return "King";
	case ACE:	return "Ace";
	default: cerr << "ERROR - rankToString()"; return "";
	}
}

string toString(CardStruct card)
{
	return suitToString(card.s) + " of " + rankToString(card.r);
}

string toStringShort(CardStruct card)
{
	string suit = suitToString(card.s);
	string rank = intToString(card.r);
	
	// shorten formatting
	suit = suit.substr(0, 1);

	return suit + rank;
}