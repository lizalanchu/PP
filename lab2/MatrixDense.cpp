#include "MatrixDense.h"
#include <stdexcept> // Подключение библиотеки для обработки исключений


MatrixDense::MatrixDense(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<double>(cols)) {}

Matrix* MatrixDense::add(const Matrix& other) const { 
    // Преобразуем указатель на другую матрицу в указатель на MatrixDense.
    const MatrixDense* otherDense = dynamic_cast<const MatrixDense*>(&other);
    // Проверяем, что размеры совпадают.
    if (!otherDense || rows != otherDense->rows || cols != otherDense->cols) {
        throw std::invalid_argument("Размеры матрицы не совпадают.");
    }
} 

Matrix* MatrixDense::subtract(const Matrix& other) const {
    // Преобразуем указатель на другую матрицу в указатель на MatrixDense.
    const MatrixDense* otherDense = dynamic_cast<const MatrixDense*>(&other);
    // Проверяем, что размеры совпадают.
    if (!otherDense || rows != otherDense->rows || cols != otherDense->cols) {
        throw std::invalid_argument("Размеры матрицы не совпадают.");
    }
}

Matrix* MatrixDense::elementwiseMultiply(const Matrix& other) const {
    // Преобразуем указатель на другую матрицу в указатель на MatrixDense.
    const MatrixDense* otherDense = dynamic_cast<const MatrixDense*>(&other);
    // Проверяем, что размеры совпадают.
    if (!otherDense || rows != otherDense->rows || cols != otherDense->cols) {
        throw std::invalid_argument("Размеры матрицы не совпадают.");
    }
}

Matrix* MatrixDense::multiply(const Matrix& other) const {
    // Преобразуем указатель на другую матрицу в указатель на MatrixDense.
    const MatrixDense* otherDense = dynamic_cast<const MatrixDense*>(&other);
    // Проверяем, что количество столбцов первой матрицы совпадает с количеством строк второй.
    if (!otherDense || rows != otherDense->rows || cols != otherDense->cols) {
        throw std::invalid_argument("Размеры матрицы не совпадают.");
    }
}

Matrix* MatrixDense::transpose() const {
    
}
