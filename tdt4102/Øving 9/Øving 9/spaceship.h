#pragma once
#include "SFML\Graphics.hpp"
#include <string>


class Spaceship {
private:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	void loadTexture(std::string filename);
	const sf::Sprite& getSprite() { return sprite; }

	void goStraight(float velocity); // flytt romskipet rett frem

};