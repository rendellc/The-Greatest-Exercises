#include "BlackJack.h"
#include "globals.h"
#include <algorithm> //std::min()
#include <iostream>
using namespace std;

BlackJack::BlackJack() {
	playerHand = 0;
	dealerHand = 0;
	playerCardsDrawn = 0;
	dealerCardsDrawn = 0;
	playerAces = 0; 
	dealerAces = 0; 
}

bool BlackJack::isAce(Card* card)
{
	if (card->getRank() == ACE) {
		return true;
	}
	else {
		return false;
	}
}

int BlackJack::getCardValue(Card* card)
{
	if (isAce(card)) {
		return -1;
	}
	else {
		int cardValue = static_cast<int>(card->getRank());
		return min(10, cardValue);
	}
}

int BlackJack::getPlayerCardValue(Card* card)
{
	int cardValue;

	if (isAce(card)) {
		// player has ace, ask for value
		cout << "Should the ace have a value of 1 or 11? " << endl;

		// validate input
		do {
			cout << "Type in 1 or 11 ";
			cin >> cardValue;
		} while (cardValue != 1 && cardValue != 11);

		// increment playerAces (maybe)
		if (cardValue == 11)
			playerAces += 1;
	}
	else {
		cardValue = getCardValue(card);
	}

	return cardValue;
}

int BlackJack::getDealerCardValue(Card* card, int dealerHand)
{
	if (isAce(card)) {
		if (dealerHand >= 11)
			return 1;
		else {
			dealerAces += 1;
			return 11;
		}
	}
	else
		return getCardValue(card);
}

bool BlackJack::askPlayerDrawCard()
{
	char input;
	cout << "Draw one more card? (y/n)" << endl;

	while (true) {
		cin >> input;
		if (input == 'y')
			return true;
		if (input == 'n')
			return false;

		cout << "Invalid input\nType 'y' or 'n': ";
	}
}

void BlackJack::playerDrawCard() {
	Card temp = deck.drawCard();
	playerHand += getPlayerCardValue(&temp);
	playerCardsDrawn += 1;
}

void BlackJack::drawInitialCards()
{
	// trekk kort
	Card dealerCard1 = deck.drawCard();
	Card dealerCard2 = deck.drawCard();
	Card playerCard1 = deck.drawCard();
	Card playerCard2 = deck.drawCard();

	// oppdater verdier
	dealerHand += getDealerCardValue(&dealerCard1, dealerHand) + getDealerCardValue(&dealerCard2, dealerHand);
	dealerCardsDrawn += 2;
	playerHand += getPlayerCardValue(&playerCard1) + getPlayerCardValue(&playerCard2);
	playerCardsDrawn += 2;

	// informer bruker
	cout << "Dealers first card was " + dealerCard1.toString() << endl;
}

bool BlackJack::checkDealerDrawCard()
{
	if (dealerHand < DEALER_LIMIT) {
		Card temp = deck.drawCard();
		dealerHand += getDealerCardValue(&temp, dealerHand);
		dealerCardsDrawn += 1;
		return true;
	}
	else if (dealerHand > LIMIT && dealerAces >= 1) {
		// gi en ace verdien 1 istedenfor 11
		dealerAces -= 1;
		dealerHand -= 10;
		return true;
	}
	
	return false;
}

string BlackJack::determineWinner()
{
	// messages
	const string TIED = "The game was tied :|";
	const string PLAYER_WIN = "The player won!";
	const string DEALER_WIN = "The dealer won :(";
	const string ERROR = "ERROR";

	// logic
	bool playerBlackJack = (playerCardsDrawn == 2) && (playerHand == 21);
	bool dealerBlackJack = (dealerCardsDrawn == 2) && (dealerHand == 21);
	bool playerBust = playerHand > LIMIT;
	bool dealerBust = dealerHand > LIMIT;

	if (playerBlackJack && dealerBlackJack) 
		return TIED;
	else if (playerBlackJack) 
		return PLAYER_WIN;
	else if (dealerBlackJack) 
		return DEALER_WIN;
	else if (playerHand == dealerHand && !playerBust) 
		return TIED;
	else if (playerHand > dealerHand && !playerBust) 
		return PLAYER_WIN;
	else if (dealerHand > playerHand && !dealerBust)
		return DEALER_WIN;
	else if (dealerBust == playerBust)
		return TIED;
	else if (dealerBust)
		return PLAYER_WIN;
	else if (playerBust)
		return DEALER_WIN;
	else	
		cerr << "ERROR - unable to determine winner" << endl;

	return ERROR;
}

void BlackJack::playGame()
{
	// setup
	deck.shuffle();
	drawInitialCards();
	//cout << "Game setup - Complete\n" << endl;


	// game-loop
	bool playerDone = false; // lagrer om spiller har sagt nei til nye kort
	bool dealerDone = false; // lagrer om dealer høy nok score til å avslutte
	do {
		if (!playerDone) {
			cout << "Current score: " << playerHand << endl;
			playerDone = !askPlayerDrawCard();
			if (!playerDone) {
				playerDrawCard();
				playerDone = playerHand >= LIMIT;
			}
		}
		
		if (!dealerDone) {
			dealerDone = !checkDealerDrawCard();
		}
	} while (!playerDone || !dealerDone);

	// game ended
	cout << "\n*** Game Ended ***\n" << endl;
	cout << "DealerHand: " << dealerHand << " with " << dealerCardsDrawn << " cards" << endl;
	cout << "Player-hand: " << playerHand << " with " << playerCardsDrawn << " cards" << endl;
	cout << determineWinner() << endl;
}
