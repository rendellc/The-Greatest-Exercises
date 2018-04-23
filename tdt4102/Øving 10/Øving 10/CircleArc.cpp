#include "CircleArc.h"
#include "Image.h"
#include <cmath>
#include <iostream>

CircleArc::CircleArc(int radius, int x0, int y0, int fromDegree, int toDegree, const Color& color)
	: Shape(color)
	, radius(radius), x0(x0), y0(y0) 
	, fromDegree(fromDegree % 361) , toDegree(toDegree % 361)
{}

void CircleArc::draw(Image& img) const
{
	const Color color = getColor();
	const int drawStep = 1;
	
	for (int deg = fromDegree; deg <= toDegree; deg += drawStep) {
		int x = x0 + radius*static_cast<double>(cos(deg*180/PI));
		int y = y0 + radius*static_cast<double>(sin(deg*180/PI));

		std::cout << "radius*cos: " << radius*static_cast<int>(cos(deg * 180 / PI)) << "  x: " << x << "  y: " << y << "\t";
		std::cout << "cos(deg): " << cos(deg) << std::endl;

		img.setPixelColor(x, y, color);
	}
}