#include "MatrixDense.h"
#include <stdexcept> // Подключение библиотеки для обработки исключений
#include <fstream> // Файловый ввод-вывод
#include <iostream>// Консоль ввод-вывод



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
    if (!otherDense || cols != otherDense->rows) {
        throw std::invalid_argument("Размеры матрицы не совпадают.");
    }

    // Создаем новую матрицу для результата.
    MatrixDense* result = new MatrixDense(rows, otherDense->cols);
    
    // Стандартное умножение матриц (поэлементное суммирование произведений).
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < otherDense->cols; ++j) {
            double sum = 0.0;
            // Внутренний цикл для произведений элементов.
            for (int k = 0; k < cols; ++k) {
                sum += data[i][k] * otherDense->data[k][j];
            }
            result->data[i][j] = sum;
        }
    }

    // Возвращаем указатель на новую матрицу.
    return result;
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



void MatrixDense::importFromFile(const std::string& filename) {
    std::ifstream file(filename); // Открываем файл для чтения.
    if (!file.is_open()) throw std::runtime_error("Не удается открыть файл."); 
    // Если файл не открылся, выбрасываем исключение.

    std::string className; 
    file >> className; // Читаем первую строку файла, где указано имя класса.
    if (className != "MatrixDense") throw std::runtime_error("Недопустимый тип матрицы.");
    // Если имя класса не соответствует "MatrixDense", выбрасываем исключение.

    file >> rows >> cols; // Считываем размеры матрицы (строки и столбцы).
    data.resize(rows, std::vector<double>(cols)); 
    // Устанавливаем размеры  `data`.

    for (int i = 0; i < rows; ++i) { // Внешний цикл по строкам.
        for (int j = 0; j < cols; ++j) { // Вложенный цикл по столбцам.
            if (!(file >> data[i][j])) { 
                // Пытаемся считать элемент из файла. Если не удается, выбрасываем исключение.
                throw std::runtime_error("Ошибка при считывании данных матрицы.");
            }
        }
    }

    file.close(); // Закрываем файл.
}



void MatrixDense::exportToFile(const std::string& filename) const {
    std::ofstream file(filename); // Открываем файл для записи.
    if (!file.is_open()) throw std::runtime_error("Не удается открыть файл.."); 
    // Если файл не открылся, выбрасываем исключение.

    file << "MatrixDense\n"; // Записываем имя класса "MatrixDense".
    file << rows << " " << cols << "\n"; 
    // Записываем размеры матрицы (строки и столбцы).

    for (const auto& row : data) { // Проходим по каждой строке матрицы.
        for (double value : row) { // Проходим по каждому элементу строки.
            file << value << " "; 
            // Записываем элемент строки в файл, разделяя пробелами.
        }
        file << "\n"; // Переходим на новую строку после записи одной строки матрицы.
    }

    file.close(); // Закрываем файл.
}


