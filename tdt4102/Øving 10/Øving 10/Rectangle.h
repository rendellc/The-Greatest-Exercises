#pragma once
#include "Image.h"
#include "Shape.h"


class Rectangle
	: public Shape {
private:
	int xBottomLeft, yBottomLeft, xUpRight, yUpRight;


public:
	Rectangle(int xBottomLeft, int yBottomLeft, int xUpRight, int yUpRight, const Color& color);

	void draw(Image& img) const;
};