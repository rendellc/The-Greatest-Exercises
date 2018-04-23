#include "Matrix.h"
#include <ostream>

Matrix::Matrix() : rows(0), columns(0), data(nullptr) {
	// Ingenting her
}

Matrix::Matrix(unsigned int N) : Matrix( N, N, 0.0 )
{
	for ( unsigned int i = 0; i < N; ++i )
		set(i, i, 1.0); // Set equal to identity
}

Matrix::Matrix(unsigned int rows, unsigned int columns, const double fill)
	: rows(rows)
	, columns(columns)
	, data(nullptr)
{
	data = new double[rows*columns];
	for ( unsigned int i = 0; i < rows*columns; ++i)
		data[i] = fill;
}

Matrix::Matrix(const Matrix & rhs) 
	: rows(rhs.rows)
	, columns(rhs.columns)
	, data(0)
{
	// If rhs was not valid, we know that rhs.row and columns == 0, therefore we have an invalid matrix and can stop.
	if (!rhs.isValid())
		return;
	
	data = new double[rows*columns];
	for ( unsigned int i = 0; i < rows*columns; ++i)
		data[i] = rhs.data[i];
}

Matrix::~Matrix() {
	invalidate();
}

void Matrix::invalidate() {
	delete [] data;
	data = nullptr;
	rows = 0;
	columns = 0;

}

bool Matrix::isValid() const {
	return !!data; // Forcing pointer to bool
}

Matrix & Matrix::operator=(const Matrix & rhs)
{
	if (!rhs.isValid())
	{
		this->invalidate();
	}
	else {
		// If we already have the correct number of elements, don't reallocate.
		if (this->rows*this->columns != rhs.rows*rhs.columns)
		{
			// Exception safe allocation
			double * oldData = this->data;

			// Allocate using rhs' dimensions.
			this->data = new double[rhs.rows*rhs.columns];
			
			// Free old data.
			delete[] oldData;
		}

		// But still make sure the dimensions are set correctly.
		this->rows = rhs.rows;
		this->columns = rhs.columns;
		
		for ( unsigned int i = 0; i < rows*columns; ++i)
			this->data[i] = rhs.data[i];
	}
	return *this;
}



Matrix & Matrix::operator +=(const Matrix & rhs) {
	if ( this->rows == rhs.rows && this->columns == rhs.columns )
	{
		for ( unsigned int row = 0; row < rows; ++row )
			for ( unsigned int column = 0; column < columns; ++column )
				this->at(row,column) += rhs.at(row,column);
	}
	else
		invalidate();

	return *this;
}
	
Matrix Matrix::operator+(const Matrix & rhs) const {
	if ( this->rows == rhs.rows && this->columns == rhs.columns )
		return Matrix(*this) += rhs;
	else
		return Matrix();
}

std::ostream & operator<<( std::ostream & out, const Matrix & elem )
{
	if (!elem.isValid())
		out << "The matrix is not valid.";
	else
	{
		for ( unsigned int row = 0; row < elem.getRows(); ++row )
		{
			out << "| ";
			for ( unsigned int column = 0; column < elem.getColumns(); ++column )
				out << elem.get(row, column) << ' ';
			out << '|' << std::endl;
		}
	}
	return out;
}

// The code below contains additional functionality, not part of the exercise.

Matrix & Matrix::operator-=(const Matrix & rhs) {
	if ( this->rows == rhs.rows && this->columns == rhs.columns )
	{
		for ( unsigned int row = 0; row < rows; ++row )
			for ( unsigned int column = 0; column < columns; ++column )
				this->at(row,column) -= rhs.at(row,column);
	}
	else
		invalidate();

	return *this;
}

Matrix Matrix::operator-(const Matrix & rhs) const {
	if ( this->rows == rhs.rows && this->columns == rhs.columns )
		return Matrix(*this) -= rhs;
	else
		return Matrix();
}

Matrix Matrix::operator *(const Matrix & rhs) const {
	if (this->isValid() && this->columns == rhs.rows  )
	{
		Matrix temp(this->rows, rhs.columns);

		for ( unsigned int row = 0; row < this->rows; ++row )
			for ( unsigned int column = 0; column < rhs.columns; ++column )
			{
				temp.at(row,column) = 0.0;
				for ( unsigned int i = 0; i < this->columns; ++i )
					temp.at(row,column) += this->at(row,i) * rhs.at(i,column);
			}
		return temp;
	}
	else
		return Matrix();
}

Matrix & Matrix::operator *=(const Matrix & rhs) {
	return *this = *this * rhs;
}

Matrix Matrix::operator*(double rhs) const {
	return Matrix(*this) *= rhs;
}

Matrix operator*(double lhs, const Matrix & rhs) {
	return rhs*lhs;
}

Matrix & Matrix::operator*=(double rhs) {
	for ( unsigned int i = 0; i < this->rows * this->columns; ++i )
		this->data[i] *= rhs;
	return *this;
}

Matrix Matrix::operator-() const {
	Matrix temp(*this);
	
	for (unsigned int i = 0; i < this->rows * this->columns; ++i )
		temp.data[i] = -temp.data[i];

	return temp;
}
