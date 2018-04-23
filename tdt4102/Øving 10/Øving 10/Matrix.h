#pragma once
#include <ostream>

class Matrix {
	unsigned int rows, columns;
	double * data;
public:
	
	Matrix();
	explicit Matrix(unsigned int N); // The explicit is *NOT* part of the cirriculum, but we need it here to get the behaviour we want.
	Matrix(unsigned int rows, unsigned int columns, const double fill = 0.0 );
	Matrix(const Matrix & rhs);
	~Matrix();

	Matrix & operator=(const Matrix & rhs);

	void invalidate();
	bool isValid() const;
	
	unsigned int getRows() const { return rows; }
	unsigned int getColumns() const { return columns; }
	
	double & at(unsigned int row, unsigned int column) {
		return data[row*columns + column];
	}
	
	const double & at(unsigned int row, unsigned int column) const {
		return data[row*columns + column];
	}

	void set(unsigned int row, unsigned int column, double value) {
		at(row,column) = value;
	}

	double get(unsigned int row, unsigned int column) const {
		return at(row,column);
	}

	Matrix & operator +=(const Matrix & rhs);
	Matrix & operator -=(const Matrix & rhs);

	Matrix operator -(const Matrix & rhs) const;
	Matrix operator +(const Matrix & rhs) const;

	Matrix operator *(const Matrix & rhs) const;
	Matrix & operator *=(const Matrix & rhs);

	// Additional functionality, not part of the exercise.
	Matrix operator-() const;				// Unary -(minus)
	Matrix operator*(double rhs) const;		// Multiply on the righthandside with a double.
	Matrix & operator*=(double rhs);		// Multiply-assign on the righthandside with a double.
};

std::ostream & operator<<( std::ostream & out, const Matrix & elem );

// Additional functionality, not part of the exercise.
Matrix operator*(double lhs, const Matrix & rhs); // Multiply on the lefthandside with a double.
