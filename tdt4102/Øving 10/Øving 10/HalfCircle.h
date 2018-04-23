#pragma once
#include "Shape.h"
#include "Image.h"

class HalfCircle 
	: public Shape{
private:
	int radius, x0, y0;

	int yLowerHalf(int x) const;
	int yUpperHalf(int x) const;
public:
	HalfCircle(int radius, int x0, int y0, const Color& color);

	void draw(Image& img) const;
};