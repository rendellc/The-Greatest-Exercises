#pragma once

class Matrix2x2;
class Vector2;

Vector2 solveSystem(const Matrix2x2& matrix, const Vector2& vector);
void getSystemFromUserAndSolve();

// *** Operators ***
Vector2 operator*(const Matrix2x2& matrix, const Vector2& vector);
Vector2 operator*(const Vector2& vector, const Matrix2x2& matrix);
