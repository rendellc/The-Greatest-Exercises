#pragma once
#include "Shape.h"

const double PI = 3.14159265;


class CircleArc
	: public Shape {
private:
	int radius, x0, y0;
	int fromDegree, toDegree;
public:
	int getRadius() const { return radius; }
	int getCenterX() const { return x0; }
	int getCenterY() const { return y0; }
	double getFromDegree() const { return fromDegree; }
	double getToDegree() const { return toDegree; }
	CircleArc(int radius, int x0, int y0, int fromDegree, int toDegree, const Color& color);
	void draw(Image& img) const;
};

