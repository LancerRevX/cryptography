#include "matrix.hpp"

#include <cmath>
#include <numeric>

Matrix cut_row_column(Matrix const& matrix, size_t i) {
    Matrix result {matrix};
    result.erase(result.begin());
    for (auto& row : result) {
        row.erase(row.begin() + i);
    }
    return result;
}

int determinant(Matrix const& matrix) {
    if (matrix.size() == 1) {
        return matrix[0][0];
    } else if (matrix.size() == 2) {
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    } else {
        int sum {0};
        for (int i {1}; i <= (int)matrix.size(); i++) {
            sum += pow(-1, i+1) * matrix[0][i-1] * determinant(cut_row_column(matrix, i-1));
        }
        return sum;
    }
}

int modular_inverse(int a, int n) {
    for (int i {1}; i < n; i++) {
        if (a%n * i % n == 1) {
            return i;
        }
    }
    return 0;
}

Matrix algebraic_complements(const Matrix& matrix) {
    Matrix result {matrix};
    for (size_t i {0}; i < result.size(); i++) {
        for (size_t j {0}; j < result[i].size(); j++) {
            result[i][j] = pow(-1, i+j+2) * minor(matrix, i, j);
        }
    }
    return result;
}

int minor(const Matrix& matrix, size_t i, size_t j) {
    Matrix cut_matrix {matrix};
    cut_matrix.erase(cut_matrix.begin() + i);
    for (auto& row : cut_matrix) {
        row.erase(row.begin() + j);
    }
    return determinant(cut_matrix);
}

Matrix transpose(const Matrix& matrix) {
    Matrix result {matrix};
    for (size_t i {0}; i < matrix.size(); i++) {
        for (size_t j {0}; j < matrix[i].size(); j++) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

Matrix modular_inverse(const Matrix& matrix, int modulus) {
    Matrix result {matrix};
    result = algebraic_complements(result);
    result = transpose(result);
    result = modular_divide(result, modulus);
    result = scalar_multiply(result, modular_inverse(determinant(matrix), modulus));
    result = modular_divide(result, modulus);
    return result;
}

Matrix scalar_multiply(const Matrix& matrix, int scalar) {
    Matrix result {matrix};
    for (size_t i {0}; i < matrix.size(); i++) {
        for (size_t j {0}; j < matrix[i].size(); j++) {
            result[i][j] *= scalar;
        }
    }
    return result;
}

Matrix modular_divide(const Matrix& matrix, int modulus) {
    Matrix result {matrix};
    for (size_t i {0}; i < matrix.size(); i++) {
        for (size_t j {0}; j < matrix[i].size(); j++) {
            result[i][j] %= modulus;
            if (result[i][j] < 0) {
                result[i][j] += modulus;
            }
        }
    }
    return result;
}

Matrix multiply(const Matrix& left, const Matrix& right) {
    Matrix result(left.size());
    for (auto& row : result) {
        row.resize(right[0].size());
    }

    for (size_t i {0}; i < result.size(); i++) {
        for (size_t j {0}; j < result[i].size(); j++) {
            result[i][j] = 0;
            for (size_t k {0}; k < left[i].size(); k++) {
                result[i][j] += left[i][k] * right[k][j];
            }
        }
    }

    return result;
}

bool is_invertible(const Matrix& matrix, int modulus) {
    return determinant(matrix) != 0 and gcd(determinant(matrix), modulus) == 1;
}

bool is_square(const Matrix& matrix) {
    for (auto& row : matrix) {
        if (row.size() != matrix.size()) {
            return false;
        }
    }
    return true;
}

Matrix modular_multiply(const Matrix& left, const Matrix& right, int modulus) {
    return modular_divide(multiply(left, right), modulus);
}
