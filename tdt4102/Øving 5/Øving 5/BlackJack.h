#pragma once
#include <string>
#include "BlackJack.h"
#include "CardDeck.h"
#include "Card.h"

class BlackJack {
private:
	const int LIMIT = 21;
	const int DEALER_LIMIT = 17;

	CardDeck deck;
	int playerHand;
	int dealerHand;
	int playerCardsDrawn;
	int dealerCardsDrawn;
	int playerAces; // aces som spilleren har valgt til å ha verdi 11
	int dealerAces; // aces som dealeren har velgt til å a verdi 11
public:
	BlackJack();
	bool isAce(Card* card);
	int getCardValue(Card* card);
	int getPlayerCardValue(Card* card);
	int getDealerCardValue(Card* card, int handValue);
	bool askPlayerDrawCard();
	void playerDrawCard();
	bool checkDealerDrawCard(); // returnerer false om dealeren ikke skal trekke flere kort
	void drawInitialCards();
	string determineWinner();
	void playGame();
};