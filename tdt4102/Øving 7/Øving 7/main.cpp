#include "fibonacci.h"
#include "matrix.h"
#include "utils.h"
#include <iostream>
using namespace std;

void testMatrix_1();
void oppgave3();
void oppgave5();
Matrix vilkaarligMatrixFunksjon(Matrix matrixByValue);

int main()
{
	//createFibonacci();
	//testMatrix_1();
	//oppgave3();
	oppgave5();

	system("pause");
	return 0;
}

void testMatrix_1()
{
	cout << "\n *** matrix testing ***\n" << endl;
	Matrix a(4, 5);
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 5; col++) {
			a.set(row, col, row + col);
		}
	}
	Matrix b(10, 2);
	for (int row = 0; row < 10; row++) {
		for (int col = 0; col < 2; col++) {
			b.set(row, col, row*col);
		}
	}

	Matrix square(5);

	cout << "a(4,5); " << a << endl;
	cout << "b(10,2); " << b << endl;
	cout << "square(5); " << square << endl;
	
	cout << "square.getHeight(); " << square.getHeight() << endl;
	a.set(2, 2, 1324.123);
	cout << "a.set(2,2,1234.123); " << a << endl;
	cout << "a.getWidth(); " << a.getWidth() << endl;
	cout << "a.getHeight(); " << a.getHeight() << endl;
}

void oppgave3()
{
	Matrix A(3, 3);
	Matrix B(4, 4);
	//Matrix B(3, 3);
	for (unsigned int row = 0; row < A.getHeight(); row++) {
		for (unsigned int col = 0; col < A.getWidth(); col++) {
			A.set(row, col, 5);
		}
	}
	for (unsigned int row = 0; row < B.getHeight(); row++) {
		for (unsigned int col = 0; col < B.getWidth(); col++) {
			B.set(row, col, 1);
		}
	}

	// a)
	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	/*
	A = B; // bruker kompilatoren sin = operator
	cout << "A = B: " << A << endl;
	B.set(2, 2, 100);
	cout << "A after B.set(2,2,100); " << A << endl;
	A endrer seg også
	*/

	// b)
	/*
	Matrix C(A); // kompilatoren sin kopi-konstruktør brukes
	cout << "C: " << C << endl;
	A.set(1, 1, 100);
	cout << "C after A.set(2,2,100); " << C << endl;
	*/

	/*
	Matrix D = B; 
	// funker kun når = operatoren fungerer så bruker =
	cout << "Matrix D = B; " << D << endl;
	*/

	//cout << "Vilkårlig: " << vilkaarligMatrixFunksjon(A) << endl;
	// klager uten = operatoren

	/*
	a)  Kompilatoren lager en egen = operator for Matrix-klassen
		Den lager ikke nye variabler på heapen så etter A = B vil 
		A i praksis peke til B sine matrise og ikke sin egen kopi
		av B sin matrise.
		Det er grunnen til at A endres når man endrer verdiene til B
	b) 
	
	*/
	
	system("pause");
}

void oppgave5()
{
	Matrix A(2, 2);
	A.set(0, 0, 1.0); A.set(0, 1, 2.0);
	A.set(1, 0, 3.0); A.set(1, 1, 4.0);

	Matrix B(2, 2);
	B.set(0, 0, 4.0); B.set(0, 1, 3.0);
	B.set(1, 0, 2.0); B.set(1, 1, 1.0);

	Matrix C(2, 2);
	C.set(0, 0, 1.0); C.set(0, 1, 3.0);
	C.set(1, 0, 1.5); C.set(1, 1, 2.0);

	Matrix expected(2, 2);
	expected.set(0, 0, 6.0); expected.set(0, 1, 8.0);
	expected.set(1, 0, 6.5); expected.set(1, 1, 7.0);

	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C: " << C << endl;
	cout << "expected: " << expected << endl;

	A += B + C;
	
	cout << "result: " << A << endl;

}

Matrix vilkaarligMatrixFunksjon(Matrix matrixByValue)
{
	cout << "vilkårlig funksjon kalt!" << endl;
	return matrixByValue; // klager når = operatoren er borte
}
