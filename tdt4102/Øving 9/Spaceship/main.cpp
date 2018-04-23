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

#include "spaceship.h"

#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;

int main() {
	//Vi startar med � opprette eit vindu. Vi brukar SFML sin RenderWindow-klasse, som kan teikne sprites.
	int width = 800, height = 600;
	string windowName = "Spaceship";
	sf::RenderWindow window(sf::VideoMode(width, height), windowName);

	//Oppretter eit Spaceship-objekt, og lastar biletet fr� fila "spaceship.png"
	Spaceship spaceship("spaceship.png");
	Spaceship romskip("spaceship.png", sf::Keyboard::Key::Z, sf::Keyboard::Key::X, sf::Keyboard::Key::Space);

	while (window.isOpen()) {
		//Dette er main-loop, den kj�rer s� lenge vindauget er ope
		sf::Event event;
		while (window.pollEvent(event)) {
			//Dette er event-loop, som trengs for at vindauget skal kunne oppdaterast
			//med hendingar utanfr� (endre storleik, flyttast, lukkast osv).
			//Vi kan ogs� handtere andre hendingar, som t.d. museklikk og tastetrykk her
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Key::Escape)
					window.close();
				break;
			//add additional event handlers here
			}
		}

		//her oppdaterer vi romskipet v�rt, sjekk spaceship.cpp for meir informasjon.
		//dette skjer �in gong for kvar gong vi oppdaterer vindauget (fleire gongar per sekund)
		spaceship.tick();
		romskip.tick();

		//Oppdaterer innhaldet i vindauget ved � f�rst fjerne alt som er der (window.clear()), teikne det vi vil ha til eit
		//buffer i minnet (window.draw(...)) og s� vise innhaldet p� skjermen (window.display()).
		window.clear();
		window.draw(spaceship.getSprite());
		window.draw(romskip.getSprite());
		window.display();
		window.setFramerateLimit(60);
	}

	return 0;
}