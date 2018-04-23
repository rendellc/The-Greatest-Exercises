/*
TDT4102, Vår 2016
Dette er eit eksempelkode frå Hjelp i R1 den 2. mars 2016
Denne koden brukar SFML, som kan lastast ned frå www.sfml-dev.org/downloads.php.
Sjå it's learning (under øving 9) eller på www.sfml-dev.org/tutorials/2.3
for guidar til korleis bruke SFML i prosjektet ditt.
Bruk også forumet på it's learning dersom det ikkje fungerer

Du treng også eit bilete ved navn "spaceship.png" for å teikne romskipet. Eit slikt bilete
er også å finne på it's learning under Hjelp i R1 -> Uke 9. Dette biletet kan du plassere i 
mappa saman med .cpp-filene.

Dersom du lurer på noko anna i dette eksempelet, ta gjerne kontakt på e-post
sivertkr@stud.ntnu.no
*/

#pragma once
#include<SFML/Graphics.hpp>
#include<string>

//Desse konstantane avgjer kor raskt romskipet roterer, og kor raskt det køyrer framover.
//Prøv gjerne ut forskjellige verdiar og sjå kva som skjer
const float ROTATION_SPEED = 1.0f;
const float VELOCITY = 2.5f;


class Spaceship {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Keyboard::Key left, right, throttle;

	//Desse funksjonane flyttar på romskipet vårt.
	//Dei er private fordi vi ikkje vil flytte på det
	//utanfor tick()-funksjonen.
	void center();
	void goStraight(float velocity);
	void rotate(float angle); //degrees

public:
	//tick() oppdaterer posisjonen og rotasjonen til romskipet
	//basert på kva knappar som er trykte inn.
	//Blir kalt frå main-loop éin gong kvar iterasjon, før vindauget blir oppdatert
	void tick();

	//getSprite() er ein aksessfunksjon, som gir andre funksjonar (td. main()) tilgang til å bruke
	//sprite-objektet som høyrer til klassen. Trengs for å teikne i vindauget.
	const sf::Sprite& getSprite() { return sprite; };

	//Desse funksjonane initialiserer (eller endrar) medlemmane sprite og texture. 
	//Biletet er spesifisert ved inputparameteren filename
	void loadTexture(std::string filename);
	Spaceship(std::string filename);
	Spaceship(std::string filename, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key throttleKey);
};
