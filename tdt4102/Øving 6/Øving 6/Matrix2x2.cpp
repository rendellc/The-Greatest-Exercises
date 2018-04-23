#include "Matrix2x2.h"
#include "Vector2.h"
#include <iostream>
using namespace std;

// *** Constructor ***
Matrix2x2::Matrix2x2()
{
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLUMNS; col++) {
			if (row == col)
				set(row, col, 1.0);
			else
				set(row, col, 0.0);
		}
	}
}
Matrix2x2::Matrix2x2(double el_00, double el_01, double el_10, double el_11)
{
	set(0, 0, el_00);
	set(0, 1, el_01);
	set(1, 0, el_10);
	set(1, 1, el_11);
}

// *** Error checks ***
bool Matrix2x2::indexBoundCheck(int row, int col) const 
{
	if ((row >= 0 && row < ROWS) && (col >= 0 && col < COLUMNS)) {
		return true;
	}
	else {
		cerr << "Invalid indexes\n"
			<< "Row=" << row << " Col=" << col << endl;
		return false;
	}
}

/// *** Access ***
double Matrix2x2::get(int row, int col) const 
{
	if (indexBoundCheck(row, col))
		return element[row][col];
	else
		return 0.0;
}
void Matrix2x2::set(int row, int col, double value) 
{
	if (indexBoundCheck(row, col))
		element[row][col] = value;
}
void Matrix2x2::print() const 
{
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLUMNS; col++) {
			cout << get(row, col) << "\t";
		}
		cout << endl;
	}
}

// *** Operations/Utilities ***
double Matrix2x2::det() const
{
	return element[0][0] * element[1][1] - element[0][1] * element[1][0];
}
Matrix2x2 Matrix2x2::inverse() const
{
	Matrix2x2 temp(0, 0, 0, 0);
	double determinant = det();

	if (determinant != 0) {
		// inverse() er mulig
		
		temp.element[0][0] = element[1][1];
		temp.element[0][1] = -element[0][1];
		temp.element[1][0] = -element[1][0];
		temp.element[1][1] = element[0][0];

		temp.scalarMult(1/determinant);
	}
	else {
		cout << "Determinant = 0 so Inverse is undefined\n"
			<< "zero-matrix returned" << endl;
	}

	return temp; // returns zero-matrix if invalid determinant
}
void Matrix2x2::scalarMult(double scalar)
{
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLUMNS; col++) {
			element[row][col] = element[row][col] * scalar;
		}
	}
}

// *** Operator Overloads ***
void Matrix2x2::operator +=(const Matrix2x2& addMatrix)
{
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLUMNS; col++) {
			element[row][col] += addMatrix.element[row][col];
		}
	}
}
void Matrix2x2::operator -=(const Matrix2x2& addMatrix)
{
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLUMNS; col++) {
			element[row][col] -= addMatrix.element[row][col];
		}
	}
}
void Matrix2x2::operator *=(const Matrix2x2& multMatrix)
{
	*this = *this * multMatrix;
}
const Matrix2x2 Matrix2x2::operator +(const Matrix2x2& addMatrix) const
{
	Matrix2x2 temp = *this;
	temp += addMatrix;
	return temp;
}
const Matrix2x2 Matrix2x2::operator -(const Matrix2x2& subMatrix) const
{
	Matrix2x2 temp = *this;
	temp -= subMatrix;
	return temp;
}
const Matrix2x2 Matrix2x2::operator *(const Matrix2x2& multMatrix) const
{
	Matrix2x2 temp(0, 0, 0, 0);
	
	for (int resCol = 0; resCol < multMatrix.COLUMNS; resCol++) {
		for (int firstRow = 0; firstRow < ROWS; firstRow++) {
			for (int firstCol = 0; firstCol < COLUMNS; firstCol++) {
				temp.element[firstRow][resCol]
					+= element[firstRow][firstCol] * multMatrix.element[firstCol][resCol];
			}
		}
	}

	return temp;
}
ostream& operator <<(ostream& outStream, const Matrix2x2& matrix)
{
	outStream << matrix.element[0][0] << "\t" << matrix.element[0][1]
	  << "\n" << matrix.element[1][0] << "\t" << matrix.element[1][1]
	  << "\n";
	return outStream;
}
