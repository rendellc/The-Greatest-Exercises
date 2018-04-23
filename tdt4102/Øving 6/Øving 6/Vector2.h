#pragma once
#include "Matrix2x2_Vector2.h"
#include <iostream>
using namespace std;

class Vector2 {
private:
	static const int ROWS = 2;

	double element[ROWS];
public:
	// constructor
	Vector2();
	Vector2(double el1, double el2);

	// error check
	bool validIndex(int row) const;

	// operations
	double dot(const Vector2& dotVector) const;
	double lengthSquared() const;
	double length() const;
	
	// access
	void set(int row, double value);
	double get(int row) const;
	
	// operators
	bool operator=(Vector2& vector) const;
	bool operator!=(Vector2& vector) const;
	friend ostream& operator<<(ostream& outStream, const Vector2& vector);
	friend Vector2 operator*(const Matrix2x2& matrix, const Vector2& vector);


};