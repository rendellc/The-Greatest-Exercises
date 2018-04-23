#include "Canvas.h"
#include <vector>

void Canvas::addShape(Shape* shape)
{
	canvas.push_back(shape);
}

void Canvas::rasterizeTo(Image& img) const
{
	for ( const auto& iter : canvas) {
		iter->draw(img);
	}
}