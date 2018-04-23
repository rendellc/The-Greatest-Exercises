#include "Matrix2x2_Vector2.h"
#include "Matrix2x2.h"
#include "Vector2.h"
using namespace std;

// *** Common operators ***
Vector2 operator*(const Matrix2x2& matrix, const Vector2& vector)
{
	Vector2 temp(0, 0);

	for (int row = 0; row < vector.ROWS; row++) {
		for (int col = 0; col < matrix.COLUMNS; col++) {
			double newValue = temp.get(row);
			newValue += matrix.get(row, col) * vector.get(col);
			temp.set(row, newValue);
		}
	}

	return temp;
}
Vector2 operator*(const Vector2& vector, const Matrix2x2& matrix)
{
	return matrix * vector;
}


// *** System Solving ***
Vector2 solveSystem(const Matrix2x2& matrix, const Vector2& vector)
{
	return matrix.inverse() * vector;
}
void getSystemFromUserAndSolve()
{
	double a = 0, b = 0, c = 0, d = 0, p = 0, q = 0;

	cout << "This function solves matrix equations of the form\n"
		<< "a\tb\t * \tx\t = \tp\n"
		<< "c\td\t   \ty\t   \tq\n" << endl;

	cout << "a: "; cin >> a;
	cout << "b: "; cin >> b;
	cout << "c: "; cin >> c;
	cout << "d: "; cin >> d;
	cout << "p: "; cin >> p;
	cout << "q: "; cin >> q;

	Matrix2x2 matrix(a, b, c, d);
	Vector2 vector(p, q);
	Vector2 solution = solveSystem(matrix, vector);
	


	Vector2 ZERO_VECTOR(0, 0);
	if (solution != ZERO_VECTOR)
		cout << "The solution is " << solution << endl;
	else
		cout << "This system has no solution" << endl;
}