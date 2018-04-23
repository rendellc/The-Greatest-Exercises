#include "HalfCircle.h"
#include "Image.h"
#include <iostream>
#include <cassert>


HalfCircle::HalfCircle(int radius, int x0, int y0, const Color& color)
	: Shape(color)
	, radius(abs(radius)) // note absolute value of radius
	, x0(x0), y0(y0)
{}

void HalfCircle::draw(Image& img) const
{
	const Color color = getColor();

	auto left = x0 - radius;
	auto right = x0 + radius;
	auto upper = y0;

	for (auto x = left; x <= right; ++x) {
		auto lower = yLowerHalf(x);
		assert(lower <= upper);

		for (auto y = lower; y <= upper; ++y) {
			img.setPixelColor(x, y, color);
		}
	}

}


// return y on upper half of circle
int HalfCircle::yUpperHalf(int x) const
{
	return y0 + static_cast<int>(sqrt(pow(radius, 2) - pow((x - x0), 2)));
}

// return y on lower half of circle
int HalfCircle::yLowerHalf(int x) const
{
	return  2 * y0 - yUpperHalf(x);
}