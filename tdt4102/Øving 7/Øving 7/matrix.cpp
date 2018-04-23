#include "matrix.h"
#include <iostream>

using namespace std;

// *** constructors / destructor ***

// default constructor
Matrix::Matrix(unsigned int rows, unsigned int columns)
{
	ROWS = rows;
	COLUMNS = columns;
	allocateMatrix(rows, columns);
}


// unititalized constructor
Matrix::Matrix() 
{ 
	makeInvalid();
}

// square identity-matrix of size "rows"
Matrix::Matrix(unsigned int rows) 
	: Matrix(rows, rows)
{
	makeIdentityMatrix();
}

// copy-constructor
Matrix::Matrix(const Matrix& input) 
	: Matrix(input.ROWS, input.COLUMNS)
{
	for (unsigned int row = 0; row < ROWS; row++) {
		for (unsigned int col = 0; col < COLUMNS; col++) {
			this->matrix[row][col] = input.matrix[row][col];
		}
	}
}

// destructor
Matrix::~Matrix()
{
	for (unsigned int row = 0; row < ROWS; row++) {
		delete[] matrix[row];
	}
	delete matrix;
}

// *** private utils ***

// allocates memory for a columns X rows matrix
void Matrix::allocateMatrix(unsigned int rows, unsigned int columns)
{
	matrix = new double*[rows];
	for (unsigned int i = 0; i < rows; i++) {
		matrix[i] = new double[columns];
	}
}

// makes current matrix into the identity-matrix
void Matrix::makeIdentityMatrix()
{
	if (ROWS == COLUMNS) {
		for (unsigned int row = 0; row < ROWS; row++) {
			for (unsigned int col = 0; col < COLUMNS; col++) {
				matrix[row][col] = static_cast<int>(row == col);	
			}
		}
	}
}

// returns true for valid indexes, false otherwise
bool Matrix::validIndex(unsigned int row, unsigned int column) const
{
	return (row < ROWS) && (column < COLUMNS);
}


// *** access ***

// returns value at position
double Matrix::get(unsigned int row, unsigned int column) const
{
	if (validIndex(row, column))
		return matrix[row][column];
	else {
		cerr << "ERROR - Invalid index in Matrix::get method" << endl;
		cerr << "row = " << row << ", column = " << column << endl;
		return 0;
	}
}

// sets value at position
void Matrix::set(unsigned int row, unsigned int column, double value)
{
	if (validIndex(row, column))
		matrix[row][column] = value;
	else {
		cerr << "ERROR - Invalid index in Matrix::set method" << endl;
		cerr << "row = " << row << ", column = " << column << endl;
	}
}

// return number of rows
unsigned int Matrix::getHeight() const
{
	return ROWS;
}

// return number of columns
unsigned int Matrix::getWidth() const
{
	return COLUMNS;
}

// returns true if matrix is valid, false otherwise
bool Matrix::isValid() const
{
	return (matrix != nullptr);
}

// returns true if rhs is same size as this
bool Matrix::sameSize(const Matrix& rhs) const
{
	return (ROWS == rhs.ROWS) && (COLUMNS == rhs.COLUMNS);
}

// makes this an invalid matrix
void Matrix::makeInvalid() 
{
	ROWS = NULL;
	COLUMNS = NULL;
	matrix = nullptr;
}

// overloads
ostream& operator<<(ostream& outputStream, const Matrix& matrix)
{
	outputStream << "\n"; // add newline to prevent formatting errors
	if (matrix.isValid()) {
		for (unsigned int row = 0; row < matrix.ROWS; row++) {
			for (unsigned int col = 0; col < matrix.COLUMNS; col++) {
				outputStream << matrix.matrix[row][col] << "\t";
			}
			outputStream << "\n";
		}
	}
	else {
		cerr << "ERROR - Invalid matrix" << endl;
	}

	return outputStream;
}

Matrix& Matrix::operator=(Matrix rhs)
{
	std::swap(*this, rhs);
	return *this;
}

void Matrix::operator+=(const Matrix& rhs)
{
	if (this->sameSize(rhs)) {
		for (unsigned int row = 0; row < ROWS; row++) {
			for (unsigned int col = 0; col < COLUMNS; col++) {
				this->matrix[row][col] += rhs.matrix[row][col];
			}
		}
	}
	else {
		makeInvalid();
	}
}

void Matrix::operator-=(const Matrix& rhs)
{
	*this += (-rhs);
}

const Matrix Matrix::operator+(const Matrix& rhs) const
{
	Matrix temp(*this);
	temp += rhs;
	return Matrix(temp);
}

const Matrix Matrix::operator-() const
{
	Matrix temp(*this);

	for (unsigned int row = 0; row < ROWS; row++) {
		for (unsigned int col = 0; col < COLUMNS; col++) {
			temp.matrix[row][col] = -temp.matrix[row][col];
		}
	}

	return temp;
}

const Matrix Matrix::operator-(const Matrix& rhs) const
{
	return *this + (-rhs);
}

