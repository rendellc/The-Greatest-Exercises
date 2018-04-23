#include <iostream>
#include <string>
#include <sstream>
#include "BlackJack.h"
#include "globals.h"
#include "utils.h"
using namespace std;

void test1()
{
	// lager testkort
	CardStruct card1; card1.s = HEARTS;	card1.r = FIVE;
	CardStruct card2; card2.s = CLUBS; card2.r = JACK;
	CardStruct card3; card3.s = DIAMONDS; card3.r = ACE;
	CardStruct card4; card4.s = SPADES; card4.r = TWO;

	// funksjonene
	cout << "suit\t\trank\t\ttoString()\t\ttoStringShort()" << endl;
	cout << suitToString(card1.s) + "\t\t" + rankToString(card1.r) + 
		"\t\t" + toString(card1) + "\t\t" + toStringShort(card1) << endl;
	cout << suitToString(card2.s) + "\t\t" + rankToString(card2.r) +
		"\t\t" + toString(card2) + "\t\t" + toStringShort(card2) << endl;
	cout << suitToString(card3.s) + "\t" + rankToString(card3.r) +
		"\t\t" + toString(card3) + "\t\t" + toStringShort(card3) << endl;
	cout << suitToString(card4.s) + "\t\t" + rankToString(card4.r) +
		"\t\t" + toString(card4) + "\t\t" + toStringShort(card4) << endl;
}

void testCards()
{
	CardDeck deck;

	deck.print();
	cout << endl;
	deck.printShort();
	deck.shuffle();
	cout << endl;
	deck.printShort();
}

int main()
{
	//test1();
	//testCards();

	BlackJack game;
	
	game.playGame();

	system("pause");
	return 0;
}