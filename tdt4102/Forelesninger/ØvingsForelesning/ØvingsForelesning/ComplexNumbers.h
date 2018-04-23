#pragma once
#include <iostream>

class Complex {
private:
	double real;
	double imag;
public:
	Complex();
	explicit Complex(double real);
	Complex(double real, double imag);
	double abs();
	
	Complex operator +(const Complex& rhs) const;
	Complex& operator +=(const Complex& rhs);
	Complex operator *(double rhs) const;
	bool operator ==(const Complex& rhs) const;
	Complex operator -() const;
	double operator[](int index);

	friend std::ostream& operator <<(std::ostream &out, Complex& rhs);
};

