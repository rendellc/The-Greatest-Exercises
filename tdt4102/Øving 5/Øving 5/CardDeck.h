#pragma once
#include "globals.h"
#include "CardDeck.h"
#include "Card.h"

class CardDeck {
private:
	static const int DECK_SIZE = 52;

	Card cards[DECK_SIZE];
	int currentCardIndex;

public:
	CardDeck::CardDeck();
	void swap(int pos1, int pos2);
	void shuffle();
	void print();
	void printShort();
	Card drawCard();
};