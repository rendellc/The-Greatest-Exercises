#include "Matrix2x2.h"
#include "Vector2.h"
#include "Matrix2x2_Vector2.h"
#include <iostream>
using namespace std;

void test1()
{
	Matrix2x2 mat(1, 2, 3, 4);
	Matrix2x2 addMat(-1, -2, -3, -4);
	cout << mat << endl;
	cout << addMat << endl;

	mat += addMat;
	addMat += mat;

	cout << "mat:\n" << mat << endl;
	cout << "addMat:\n" << addMat << endl;
}

void testMatrix() 
{
	cout << "Oppgave 2c:" << endl;
	
	Matrix2x2 A(1, 2, 3, 4);
	Matrix2x2 B(4, 3, 2, 1);
	Matrix2x2 C(1.0, 3.0, 1.5, 2.0);
	cout << "A:\n" << A << endl;
	cout << "B:\n" << B << endl;
	cout << "C:\n" << C << endl;


	A += B;
	cout << "A += B;\n" << A << "\n" << endl;
	A -= B;
	cout << "A -= B;\n" << A << "\n" << endl;
	
	Matrix2x2 D = A + B;
	cout << "D = A + B;\n" << D << endl;
	D = D*B - A + C;
	cout << "D = D*B - A + C;\n" << D << endl;

	D *= B;
	cout << "D *= B;\n" << D << endl;

	cout << endl;
	Matrix2x2 mult1(1, 2, 3, 4);
	Matrix2x2 mult2(5, 6, 7, 8);

	cout << mult1*mult2 << endl;


}

int main()
{
	//testMatrix();
	getSystemFromUserAndSolve();
	
	//Vector2 test(2, 4);
	//cout << test << endl;

	system("pause");
	return 0;
}