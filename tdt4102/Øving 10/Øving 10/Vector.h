#pragma once

class Matrix;

class Vector 
	: public Matrix {
public:
	// constructors
	Vector();
	explicit Vector(unsigned int nRows, double fill = 0.0);
	Vector(const Matrix& other);

	// access
	void set(unsigned int nRows, double value);
	double get(unsigned int nRown) const;

	// operations
	double dot(const Vector& other) const;
	double lengthSquared() const;
	double length() const;

};