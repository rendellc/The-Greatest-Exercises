/*
TDT4102, V�r 2016
Dette er eit eksempelkode fr� Hjelp i R1 den 2. mars 2016
Denne koden brukar SFML, som kan lastast ned fr� www.sfml-dev.org/downloads.php.
Sj� it's learning (under �ving 9) eller p� www.sfml-dev.org/tutorials/2.3
for guidar til korleis bruke SFML i prosjektet ditt.
Bruk ogs� forumet p� it's learning dersom det ikkje fungerer

Du treng ogs� eit bilete ved navn "spaceship.png" for � teikne romskipet. Eit slikt bilete
er ogs� � finne p� it's learning under Hjelp i R1 -> Uke 9. Dette biletet kan du plassere i 
mappa saman med .cpp-filene.

Dersom du lurer p� noko anna i dette eksempelet, ta gjerne kontakt p� e-post
sivertkr@stud.ntnu.no
*/

#pragma once
#include<SFML/Graphics.hpp>
#include<string>

//Desse konstantane avgjer kor raskt romskipet roterer, og kor raskt det k�yrer framover.
//Pr�v gjerne ut forskjellige verdiar og sj� kva som skjer
const float ROTATION_SPEED = 1.0f;
const float VELOCITY = 2.5f;


class Spaceship {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Keyboard::Key left, right, throttle;

	//Desse funksjonane flyttar p� romskipet v�rt.
	//Dei er private fordi vi ikkje vil flytte p� det
	//utanfor tick()-funksjonen.
	void center();
	void goStraight(float velocity);
	void rotate(float angle); //degrees

public:
	//tick() oppdaterer posisjonen og rotasjonen til romskipet
	//basert p� kva knappar som er trykte inn.
	//Blir kalt fr� main-loop �in gong kvar iterasjon, f�r vindauget blir oppdatert
	void tick();

	//getSprite() er ein aksessfunksjon, som gir andre funksjonar (td. main()) tilgang til � bruke
	//sprite-objektet som h�yrer til klassen. Trengs for � teikne i vindauget.
	const sf::Sprite& getSprite() { return sprite; };

	//Desse funksjonane initialiserer (eller endrar) medlemmane sprite og texture. 
	//Biletet er spesifisert ved inputparameteren filename
	void loadTexture(std::string filename);
	Spaceship(std::string filename);
	Spaceship(std::string filename, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key throttleKey);
};
