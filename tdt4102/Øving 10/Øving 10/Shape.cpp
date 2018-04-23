#include "Shape.h"


Shape::Shape(const Color& color)
	: color(color)
{
}

Color Shape::getColor() const {
	return color;
}