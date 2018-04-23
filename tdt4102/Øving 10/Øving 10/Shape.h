#pragma once
#include "Image.h"

class Shape {
private:
	Color color;
public:
	Shape(const Color& color);

	Color getColor() const;

	virtual void draw(Image& img) const = 0;
	// pure virtual: implementeres ikke i klassen
	//		betyr at alle klasser som arver Shape må implementere draw
	// abstrakt klasse: kan ikke lages objekter av
};