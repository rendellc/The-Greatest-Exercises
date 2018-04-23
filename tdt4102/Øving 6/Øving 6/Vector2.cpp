#include "Vector2.h"
#include "Matrix2x2.h"
#include <iostream>
#include <cmath>
using namespace std;

// *** Constructors ***
Vector2::Vector2()
{
	for (int row = 0; row < ROWS; row++) {
		element[row] = 0;
	}
}
Vector2::Vector2(double el1, double el2)
{
	element[0] = el1;
	element[1] = el2;
}

// *** Error checks ***
bool Vector2::validIndex(int row) const
{
	if (row >= 0 && row < ROWS)
		return true;
	else {
		cerr << "ERROR - invalid index" << endl;
		return false;
	}
}

// *** Access ***
void Vector2::set(int row, double value)
{
	if (validIndex(row))
		element[row] = value;
}
double Vector2::get(int row) const
{
	if (validIndex(row))
		return element[row];
	else
		return 0;
}

// *** Operations/Utilities ***
double Vector2::dot(const Vector2& dotVector) const
{
	double dotProduct = 0;

	for (int i = 0; i < ROWS; i++) {
		dotProduct += element[i] * dotVector.element[i];
	}

	return dotProduct;

}
double Vector2::lengthSquared() const
{
	return dot(*this);
}
double Vector2::length() const
{
	return sqrt(lengthSquared());
}

// *** Operator Overloads ***
bool Vector2::operator=(Vector2& vector) const
{
	for (int i = 0; i < ROWS; i++) {
		if (this->element[i] != vector.element[i])
			return false;
	}
	return true;
}

bool Vector2::operator!=(Vector2& vector) const
{
	return !(*this = vector);
}

ostream& operator <<(ostream& outStream, const Vector2& vector)
{
	for (int i = 0; i < vector.ROWS; i++) {
		outStream << "\n" << vector.element[i];
	}
	outStream << "\n";
	return outStream;
}