#include "Rectangle.h"
#include "Image.h"

Rectangle::Rectangle(int xBottomLeft, int yBottomLeft, int xUpRight, int yUpRight, const Color& color)
	: Shape(color)
	, xBottomLeft(xBottomLeft), yBottomLeft(yBottomLeft)
	, xUpRight(xUpRight), yUpRight(yUpRight)
{}

void Rectangle::draw(Image& img) const
{
	const Color color = getColor();

	const int xSign = (xBottomLeft < xUpRight) ? 1 : -1;
	const int ySign = (yBottomLeft < yUpRight) ? 1 : -1;

	for (int x = xBottomLeft; x != xUpRight + xSign; x += xSign) {
		for (int y = yBottomLeft; y != yUpRight + ySign; y += ySign) {
			img.setPixelColor(x, y, color);
		}
	}

}