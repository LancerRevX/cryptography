#pragma once

#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;

class MatrixIsNotInvertible : public exception {};

Matrix cut_row_column(Matrix const& matrix, size_t i);
int modular_inverse(int a, int n);
int determinant(Matrix const& matrix);
inline void check_square(Matrix const& matrix);
Matrix algebraic_complements(Matrix const& matrix);
int minor(Matrix const& matrix, size_t i, size_t j);
Matrix transpose(Matrix const& matrix);
Matrix modular_inverse(Matrix const& matrix, int modulus);
Matrix scalar_multiply(Matrix const& matrix, int scalar);
Matrix modular_divide(Matrix const& matrix, int modulus);
Matrix multiply(Matrix const& left, Matrix const& right);
Matrix modular_multiply(Matrix const& left, Matrix const& right, int modulus);
bool is_invertible(Matrix const& matrix, int modulus);
bool is_square(Matrix const& matrix);
