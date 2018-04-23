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
#include<iostream>
#include<cmath>

using std::cout;
using std::endl;

void Spaceship::tick()
{
	/*
	void Spaceship::tick()
	Denne funksjonen blir kj�rt �in gong for kvar iterasjon av main-loop.
	Den sjekkar tastaturet som knappane for rotering eller framdrift er trykte,
	og oppdaterer sprite-objektet tilsvarande ved hjelp av medlemsfunksjonane 
	rotate() og goStraight().

	sf::Keyborad::isKeyPressed() er ein funksjon i SFML som returnerer true dersom 
	knappen ein sender inn som argument er trykt, og false ellers.
	*/

	//check keyboard input
	if (sf::Keyboard::isKeyPressed(left)) {
		//rotate left
		rotate(-ROTATION_SPEED);
	}
	else if (sf::Keyboard::isKeyPressed(right)) {
		//rotate right
		rotate(ROTATION_SPEED);
	}

	//go forward
	if (sf::Keyboard::isKeyPressed(throttle)) {
		if (sprite.getPosition().x > 0 || sprite.getPosition().y > 600) // 600 = y maks
			goStraight(VELOCITY);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
		center();
	}

	// tyngdekraft
	sprite.move(0, 0.5f);
}

void Spaceship::center()
{
	/*
	void Spaceship::center()
	Denne funksjonen set posisjonen til romskipet (sprite-objektet)
	til midten av skjermen (400,300) i dette eksempelet

	Denne b�r eigentlig ta inn storleiken til vinduaget for � fungere skikkelig 
	for storleikar som ikkje er 800x600
	*/
	sprite.setPosition(400, 300);
}

void Spaceship::goStraight(float velocity)
{
	/*
	void Spaceship::goStraight(float)
	Denne funksjonen tar inn hastigheit, og flyttar romskipet tilsvarande.
	Medlemsfunksjonen sf::Sprite::move(float,float) blir brukt til � flytte rommskipet.
	Denne funksjonen tar inn avstand i x- og y-retning, s� vi m� finne x- og
	y-komponenten til farten. D� treng vi vinkelen, som vi f�r fr� getRotation(), som er ein
	medlemsfunksjon i sf::Sprite. 
	*/
	float angle = sprite.getRotation() / 180 * 3.14159265; //konverterer vinkelen til radianar
	float xspeed = velocity*sin(angle); //dekomponerer fartsvektoren
	float yspeed = -velocity*cos(angle);

	sprite.move(xspeed, yspeed);
}

void Spaceship::rotate(float angle)
{
	/*
	void Spaceship::rotate(float)
	Denne funksjonen roterer romskipet. For � f� til det
	bruker vi sf::Sprite sim medlemsfunksjon med same navn.
	Denne funksjonen tek inn vinkelen i grader, og roterer
	sprite-objektet tilsvarande
	*/
	sprite.rotate(angle);
}

void Spaceship::loadTexture(std::string filename)
{
	/*
	void::Spaceship::loadTexture(std::string)
	Denne funksjonen lastar inn eit bilete (eller texture) til sprite-objektet. 
	Det er dette biletet som blir teikna n�r vi skal teikne romskipet.

	Biletet i "spaceship.png" har ein kvit bakgrunn som vi har lyst � gjere gjennomsiktig,
	for � f� til det lagar vi f�rst eit Image-objekt, som har muligheit til � gjere dette ved 
	help av medlemsfunksjonen createMaskFromColor(sf::Color), som set ein farge til � vere 
	gjennomsiktig i det endelige biletet.
	Deretter lastar vi biletet inn som ein texture, og legg denne til sprite-objektet v�rt
	ved hjelp av medlemsfunksjonen setTexture(sf::Texture).

	P� slutten av funksjonen plasserer vi ogs� romskipet i midten av vinduet, i tillegg til � 
	gi det ein ny "origin" vha. setOrigin(float,float). Origin er det punktet alle transformasjonar 
	tek utgangspunt i, s� det er dette punktet romskipet vil rotere rundt n�r vi brukar rotate(float).
	Vi set origin til � vere i midten
	*/

	sf::Image image;
	if (!image.loadFromFile(filename)) {
		//fann ikkje fila, her m� vi gjere noko
		cout << "Failed to load " << filename << endl;
		return;
	}
	image.createMaskFromColor(sf::Color::White); //set fargen kvit (sf::Color(255,255,255)) til � vere gjennomsiktig
	texture.loadFromImage(image); //lastar biletet (image) inn i texture (som er ein medlemsvariabel i Spaceship-klassen!)
	
	sprite.setTexture(texture); //Gir medlemsvariabelen sprite ein tekstur, gitt av texture.

	//Set origin for sprite til � vere midt i biletet
	int centerx = sprite.getTextureRect().width / 2;
	int centery = sprite.getTextureRect().height / 2;
	sprite.setOrigin(centerx, centery);

	//Posisjonerer romskipet midt i vindauget (gjeld kun for 800x600 vindu!)
	sprite.setPosition(400, 300); //midten av eit 800x600-vindu

	//Endrar storleiken p� biletet ved � skalere det langs b�de x- og y-aksen
	sprite.scale(0.5, 0.5);

}

Spaceship::Spaceship(std::string filename) : Spaceship(filename, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right, sf::Keyboard::Key::Up)
{
	/*
	Spaceship::Spaceship(std::string)
	Konstrukt�r. Denne lastar inn biletet fr� filnavnet som er spesifisert
	Ved hjelp av loadTexture(std::string), som er implementert lenger oppe i denne fila.
	*/
}

Spaceship::Spaceship(std::string filename, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key throttleKey) : left(leftKey), right(rightKey), throttle(throttleKey)
{
	loadTexture(filename);
}
