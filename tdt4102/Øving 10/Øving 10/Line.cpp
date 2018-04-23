#include "Line.h"
#include <limits>
#include <iostream>

Line::Line(int xStart, int yStart, int xEnd, int yEnd, const Color& color)
	: Shape(color)
	, xStart(xStart), xEnd(xEnd)
	, yStart(yStart), yEnd(yEnd)
	, deltaX(xEnd - xStart)
	, deltaY(yEnd - yStart)
{}

void Line::draw(Image& img) const 
{
	const Color color = getColor(); // reduces function calls

	if (deltaX != 0) {
		float slope = static_cast<float>(deltaY) / deltaX;

		if (abs(slope) <= 1) {
			// draw y = f(x)
			int sign = (xStart < xEnd) ? 1 : -1;
			for (int x = xStart; x != xEnd + sign; x += sign) {
				img.setPixelColor(x, yFunc(x), color);
			}
		}
		else {
			// steep slope => draw x = f(y)
			int sign = (yStart < yEnd) ? 1 : -1;
			for (int y = yStart; y != yEnd + sign; y += sign) {
				img.setPixelColor(xFunc(y), y, color);
			}
		}
	}
	else {
		// deltaX == 0
		int sign = (yStart < yEnd) ? 1 : -1;
		for (int y = yStart; y != yEnd + sign; y += sign) {
			img.setPixelColor(xStart, y, color);
		}
	}
}

int Line::yFunc(int x) const
{
	// assumes xEnd != xStart
	float slope = static_cast<float>(deltaY) / deltaX;
	return static_cast<int>(slope * (x - xStart)) + yStart;
}

int Line::xFunc(int y) const
{
	// assumes yEnd != yStart
	float slope = static_cast<float>(deltaX) / deltaY;
	return static_cast<int>(slope * (y - yStart)) + xStart;
}