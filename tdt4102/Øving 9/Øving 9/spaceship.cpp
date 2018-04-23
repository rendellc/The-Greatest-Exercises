#include "SFML\Graphics.hpp"
#include <string>
#include "spaceship.h"

void Spaceship::loadTexture(std::string filename) 
{
	texture.loadFromFile("spaceship.png");
	sprite.setTexture(texture);
}

void Spaceship::goStraight(float velocity)
{
	float angle = sprite.getRotation()  * 3.14 / 180;
	float xSpeed = velocity * cos(angle);
	float ySpeed = velocity * sin(angle);
	sprite.move(xSpeed, ySpeed);

}