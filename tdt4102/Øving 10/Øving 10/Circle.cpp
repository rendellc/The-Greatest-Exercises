#include "Circle.h"
#include "Image.h"
#include <math.h>
#include <iostream>
#include <cassert>

Circle::Circle(int radius, int x0, int y0, const Color& color)
	: Shape(color)
	, radius(abs(radius)) // note absolute value of radius
	, x0(x0), y0(y0)
{}

void Circle::draw(Image& img) const
{
	const Color color = getColor();
	
	int left = x0 - radius;
	int right = x0 + radius;
	
	for (int x = left; x <= right; ++x) {
		int lower = yLowerHalf(x);
		int upper = yUpperHalf(x);
		assert(lower <= upper);
		for (int y = lower; y <= upper; ++y) {
			img.setPixelColor(x, y, color);
		}
	}
	
}

// return y on upper half of circle
int Circle::yUpperHalf(int x) const
{
	return y0 + static_cast<int>(sqrt(pow(radius, 2) - pow((x - x0), 2)));
}

// return y on lower half of circle
int Circle::yLowerHalf(int x) const
{
	return  2 * y0 - yUpperHalf(x);
}