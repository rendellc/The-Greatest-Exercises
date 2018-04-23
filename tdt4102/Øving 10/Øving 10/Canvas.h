#pragma once
#include <vector>
#include "Shape.h"
#include "Image.h"


class Canvas {
private:
	std::vector<Shape*> canvas;
public:
	// adds Shape to canvas
	void addShape(Shape* shape);

	// draws all shapes in canvas to the image
	void rasterizeTo(Image& img) const;
};