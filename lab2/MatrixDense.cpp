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
     // Создаем новую матрицу для результата.
    MatrixDense* result = new MatrixDense(rows, cols);
    
    // Сложение поэлементно.
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result->data[i][j] = data[i][j] + otherDense->data[i][j];
        }
    }

    // Возвращаем указатель на новую матрицу.
    return result;
} 



Matrix* MatrixDense::subtract(const Matrix& other) const {
    // Преобразуем указатель на другую матрицу в указатель на MatrixDense.
    const MatrixDense* otherDense = dynamic_cast<const MatrixDense*>(&other);
    // Проверяем, что размеры совпадают.
    if (!otherDense || rows != otherDense->rows || cols != otherDense->cols) {
        throw std::invalid_argument("Размеры матрицы не совпадают.");
    }
     // Создаем новую матрицу для результата.
    MatrixDense* result = new MatrixDense(rows, cols);
    
    // Вычитание поэлементно.
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result->data[i][j] = data[i][j] - otherDense->data[i][j];
        }
    }

    // Возвращаем указатель на новую матрицу.
    return result;
}



Matrix* MatrixDense::elementwiseMultiply(const Matrix& other) const {
    // Преобразуем указатель на другую матрицу в указатель на MatrixDense.
    const MatrixDense* otherDense = dynamic_cast<const MatrixDense*>(&other);
    // Проверяем, что размеры совпадают.
    if (!otherDense || rows != otherDense->rows || cols != otherDense->cols) {
        throw std::invalid_argument("Размеры матрицы не совпадают.");
    }
    // Создаем новую матрицу для результата.
    MatrixDense* result = new MatrixDense(rows, cols);
    
    // Поэлементное умножение.
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result->data[i][j] = data[i][j] * otherDense->data[i][j];
        }
    }

    // Возвращаем указатель на новую матрицу.
    return result;
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
    // Создаем новую матрицу с перевернутыми размерами.
    MatrixDense* result = new MatrixDense(cols, rows);
    
    // Транспонирование: меняем местами индексы строк и столбцов.
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result->data[j][i] = data[i][j];
        }
    }

    // Возвращаем указатель на транспонированную матрицу.
    return result;
    
}
