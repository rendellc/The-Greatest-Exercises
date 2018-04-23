#pragma once
#include "Shape.h"

class Circle
	: public Shape {
private:
	int radius, x0, y0;

	int yUpperHalf(int x) const;
	int yLowerHalf(int x) const;
public:
	Circle(int radius, int x0, int y0, const Color& color);

	void draw(Image& img) const;
};