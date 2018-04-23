#include "Image.h"
#include <iostream>

#define NDEBUG
#include <cassert>

/*****************************************************
 * You _should_ change the functions in this file.   *
 * The following functions are provided so that      *
 * the code will compile, note however that the      *
 * program will not run before you have implemented  *
 * all the functions in this file.                   *
 *****************************************************/

Image::Image( size_t width, size_t height )
	: width(width), height(height)
{
	data = new Pixel[width*height];
}

Image::~Image()  {
	delete[] data;
}

size_t Image::getWidth() const {
   return width;
}
size_t Image::getHeight() const  {
   return height;
}

const Pixel * Image::getScanLine(size_t line) const  {
   return &data[width*line];
}
Pixel * Image::getScanLine(size_t line) {
   return &data[width*line];
}

Color Image::getPixelColor( size_t x, size_t y ) const {
   return data[arrIndex(x, y)];
}
void Image::setPixelColor( size_t x, size_t y, const Color &color) {
	//assert(x < width && y < height);
	//std::cout << "Index: x=" << x << ", y=" << y << std::endl;
	if (0 <= x && x < width && 0 <= y && y < height ) {
		data[arrIndex(x, y)] = color;
	}
}

void Image::fill( const Color &color ) {
	for (size_t x = 0; x < width; ++x) {
		for (size_t y = 0; y < height; ++y) {
			//data[arrIndex(x,y)] = color;
			setPixelColor(x, y, color);
		}
	}
}

size_t Image::arrIndex(size_t x, size_t y) const
{	
	return x + width*y;
}