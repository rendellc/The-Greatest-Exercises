#pragma once
#include <iostream>
using namespace std;

class Matrix {
private:
	unsigned int ROWS;
	unsigned int COLUMNS;

	double** matrix;

	// private utils
	void allocateMatrix(unsigned int rows, unsigned int columns);
	void makeIdentityMatrix();
	void makeInvalid();
	bool sameSize(const Matrix& rhs) const; // checks if this is same size as rhs
	
	// error check
	bool validIndex(unsigned int row, unsigned int column) const;
	bool isValid() const; // checks if matrix is valid
	
public:
	// constructors / destructors
	Matrix();
	
	Matrix(unsigned int rows, unsigned int columns);
	explicit Matrix(unsigned int rows);
	Matrix(const Matrix& input); // copy-constructor
	~Matrix(); // destructor

	// access
	double get(unsigned int row, unsigned int column) const;
	void set(unsigned int row, unsigned int column, double value);
	unsigned int getHeight() const;
	unsigned int getWidth() const;

	// overloads
	Matrix& operator=(Matrix rhs);
	void operator+=(const Matrix& rhs);
	void operator-=(const Matrix& rhs);
	const Matrix operator+(const Matrix& rhs) const;
	const Matrix operator-() const;
	const Matrix operator-(const Matrix& rhs) const;
	friend ostream& operator<<(ostream& outputStream, const Matrix& matrix);

};
