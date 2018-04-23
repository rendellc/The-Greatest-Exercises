#include "Matrix.h"
#include "Vector.h"
#include <cmath> // nan("")

Vector::Vector() 
	: Matrix() 
{ //empty
}

Vector::Vector(unsigned int nRows, double fill)
	: Matrix(nRows, 1, fill)
{ // empty
}

Vector::Vector(const Matrix& other)
	: Matrix() // initialiseres til ugyldig matrise
{
	if (other.getColumns() == 1) {
		*this = other;
	}
}

void Vector::set(unsigned int nRows, double value)
{
	Matrix::set(nRows, 0, value);
}

double Vector::get(unsigned int row) const
{
	return Matrix::get(row, 0);
}

double Vector::dot(const Vector& other) const
{
	// check for errors
	if (this->getRows() != other.getRows() || !this->isValid()) {
		return nan("");
	}

	// no errors found so calculate dot
	double dot = 0;
	for (unsigned int i = 0; i < getRows(); ++i) {
		dot += this->get(i) * other.get(i);
	}
	return dot;
}

double Vector::lengthSquared() const
{
	return dot(*this); // dot with self
}

double Vector::length() const
{
	return sqrt(lengthSquared());
}
