#pragma once
#include <iostream>
#include "Matrix2x2_Vector2.h"
using namespace std;


class Matrix2x2 {
private:
	static const int ROWS = 2;
	static const int COLUMNS = 2;

	double element[ROWS][COLUMNS];
public:
	// constructor
	Matrix2x2();
	Matrix2x2(double el_00, double el_01, double el_10, double el_11);

	// error check
	bool indexBoundCheck(int row, int col) const;

	// access
	double get(int row, int col) const;
	void set(int row, int col, double value);
	
	// operations/utilities
	void print() const;
	double det() const;
	void scalarMult(double scalar);
	Matrix2x2 inverse() const;

	// operators
	void operator+=(const Matrix2x2& addMatrix);
	void operator-=(const Matrix2x2& addMatrix);
	void operator*=(const Matrix2x2& multMatrix);
	const Matrix2x2 operator+(const Matrix2x2& addMatrix) const;
	const Matrix2x2 operator-(const Matrix2x2& subMatrix) const;
	const Matrix2x2 operator*(const Matrix2x2& multMatrix) const;
	
	friend Vector2 operator*(const Matrix2x2& matrix, const Vector2& vector);
	friend ostream& operator<<(ostream& outStream, const Matrix2x2& matrix);
};
