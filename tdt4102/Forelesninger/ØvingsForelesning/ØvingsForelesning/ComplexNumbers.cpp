#include "ComplexNumbers.h"
#include <cmath>

using namespace std;

Complex::Complex() {
	real = 0;
	imag = 0;
}

Complex::Complex(double real) {
	this->real = real;
	imag = 0;
}

Complex::Complex(double real, double imag) {
	this->real = real;
	this->imag = imag;
}

double Complex::abs() {
	return sqrt(real*real + imag*imag);
}

Complex Complex::operator+(const Complex& rhs) const {
	Complex retVal;
	retVal.real = rhs.real + real;
	retVal.imag = rhs.imag + imag;
	return retVal;
}

Complex& Complex::operator +=(const Complex& rhs) {
	*this = *this + rhs;
	return *this;
}



std::ostream& operator <<(std::ostream &out, Complex& rhs) {
	out << rhs.real << " + " << rhs.imag << "i";
	return out;
}

Complex Complex::operator*(double rhs) const {
	Complex retVal(real*rhs, imag*rhs);
	return retVal;
}

Complex operator*(const double lhs, const Complex& rhs) {
	return rhs*lhs;
}

bool Complex::operator==(const Complex& rhs) const {
	return (this->real == rhs.real) && (this->imag == rhs.imag);
}

Complex Complex::operator -() const {
	Complex retVal(-real, -imag);
	return retVal;
}

double Complex::operator[](int index) {
	if (index == 0)
		return real;
	else if (index == 1)
		return imag;
	else {
		cerr << "Invalid index";
		return 0.0;
	}
}