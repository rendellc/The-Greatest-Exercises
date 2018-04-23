#include <iostream>
#include "utils.h"
#include "globals.h"
#include "CardDeck.h"


CardDeck::CardDeck()
{
	currentCardIndex = 0;

	int indexCounter = 0;
	for (int s = CLUBS; s <= SPADES; s++) {
		Suit suit = static_cast<Suit>(s);
		for (int r = TWO; r <= ACE; r++) {
			Rank rank = static_cast<Rank>(r);

			cards[indexCounter] = Card(suit, rank);
			indexCounter++;
		}
	}
}

void CardDeck::swap(int pos1, int pos2)
{
	Card temp = cards[pos1];
	cards[pos1] = cards[pos2];
	cards[pos2] = temp;
}

void CardDeck::print()
{
	for (int i = 0; i < DECK_SIZE; i++) {
		Card card = cards[i];
		cout << card.toString() << endl;
	}
}

void CardDeck::printShort()
{
	for (int i = 0; i < DECK_SIZE; i++) {
		Card card = cards[i];
		cout << card.toStringShort() << endl;
	}
}

void CardDeck::shuffle()
{

	for (int i = 0; i < DECK_SIZE; i++) {
		int randomIndex = randomNumberGen(0, DECK_SIZE - 1);
		swap(i, randomIndex);
	}
}

Card CardDeck::drawCard()
{
	Card drawn = cards[currentCardIndex];
	currentCardIndex++;
	return drawn;
}
