#pragma once
#include "Shape.h"

class Line 
	: public Shape {
private:
	int xStart, yStart, xEnd, yEnd;
	int deltaX, deltaY;

	int yFunc(int x) const;
	int xFunc(int y) const;
public:
	Line(int xStart, int yStart, int xEnd, int yEnd, const Color& color);
	void draw(Image& img) const;
};