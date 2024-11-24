#include "MatrixDense.h"


MatrixDense::MatrixDense(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<double>(cols)) {}

Matrix* MatrixDense::add(const Matrix& other) const {
    // Реализация операции сложения
} 

Matrix* MatrixDense::subtract(const Matrix& other) const {
    // Реализация операции вычитания
}

Matrix* MatrixDense::elementwiseMultiply(const Matrix& other) const {
    // Реализация поэлементного умножения
}

Matrix* MatrixDense::multiply(const Matrix& other) const {
    // Реализация матричного умножения
}

Matrix* MatrixDense::transpose() const {
    // Реализация транспонирования
}
