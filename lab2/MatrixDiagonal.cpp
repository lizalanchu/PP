#include "MatrixDiagonal.h"
#include <stdexcept> // Подключение библиотеки для обработки исключений
#include <fstream> // Файловый ввод-вывод
#include <iostream>// Консоль ввод-вывод

MatrixDiagonal::MatrixDiagonal(int size) : size(size), data(size) {}

Matrix* MatrixDiagonal::add(const Matrix& other) const {
    //Приведение указателя other к типу MatrixDiagonal.
    const MatrixDiagonal* otherDiag = dynamic_cast<const MatrixDiagonal*>(&other);
    //Проверка, что переданная матрица того же типа и размера, иначе выбрасывается исключение.
    if (!otherDiag || size != otherDiag->size) {
        throw std::invalid_argument("Размеры матрицы не совпадают");
    }
    
    //Создание новой диагональной матрицы для хранения результата.
    MatrixDiagonal* result = new MatrixDiagonal(size);

    //Сложение соответствующих элементов диагоналей двух матриц.
    for (int i = 0; i < size; ++i) {
        result->data[i] = data[i] + otherDiag->data[i];
    }
  
    return result;
  
} 



Matrix* MatrixDiagonal::subtract(const Matrix& other) const {
    //Приведение указателя other к типу MatrixDiagonal.
    const MatrixDiagonal* otherDiag = dynamic_cast<const MatrixDiagonal*>(&other);
    //Проверка, что переданная матрица того же типа и размера, иначе выбрасывается исключение.
    if (!otherDiag || size != otherDiag->size) {
        throw std::invalid_argument("Размеры матрицы не совпадают");
    }
    
    //Создание новой диагональной матрицы для хранения результата.
    MatrixDiagonal* result = new MatrixDiagonal(size);

    //Сложение соответствующих элементов диагоналей двух матриц.
    for (int i = 0; i < size; ++i) {
        result->data[i] = data[i] - otherDiag->data[i];
    }
  
    return result; 
}



Matrix* MatrixDiagonal::elementwiseMultiply(const Matrix& other) const {
    //Приведение указателя other к типу MatrixDiagonal.
    const MatrixDiagonal* otherDiag = dynamic_cast<const MatrixDiagonal*>(&other);
    //Проверка, что переданная матрица того же типа и размера, иначе выбрасывается исключение.
    if (!otherDiag || size != otherDiag->size) {
        throw std::invalid_argument("Размеры матрицы не совпадают");
    }
    
    //Создание новой диагональной матрицы для хранения результата.
    MatrixDiagonal* result = new MatrixDiagonal(size);

    //Сложение соответствующих элементов диагоналей двух матриц.
    for (int i = 0; i < size; ++i) {
        result->data[i] = data[i] * otherDiag->data[i];
    }
  
    return result;  
}



Matrix* MatrixDiagonal::multiply(const Matrix& other) const {
    //Приведение указателя other к типу MatrixDiagonal.
    const MatrixDiagonal* otherDiag = dynamic_cast<const MatrixDiagonal*>(&other);
    //Проверка, что переданная матрица того же типа и размера, иначе выбрасывается исключение.
    if (!otherDiag || size != otherDiag->size) {
        throw std::invalid_argument("Размеры матрицы не совпадают");
    }
    
    //Создание новой диагональной матрицы для хранения результата.
    MatrixDiagonal* result = new MatrixDiagonal(size);

    //Сложение соответствующих элементов диагоналей двух матриц.
    for (int i = 0; i < size; ++i) {
        result->data[i] = data[i] * otherDiag->data[i];
    }
  
    return result; 
}



Matrix* MatrixDiagonal::transpose() const {
      // Создаётся копия текущей матрицы, так как транспонированная версия диагональной матрицы совпадает с оригиналом
    return new MatrixDiagonal(*this);
   
    
}



// Импорт матрицы из файла
void MatrixDiagonal::importFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не удается открыть файл.");

    std::string className;
    file >> className;
    if (className != "MatrixDiagonal") throw std::runtime_error("Недопустимый тип матрицы.");

    file >> size;
    data.resize(size);

    for (int i = 0; i < size; ++i) {
        if (!(file >> data[i])) {
                throw std::runtime_error("Ошибка при считывании матричных данных.");
        }
    }

    file.close();
}



// Экспорт матрицы в файл
void MatrixDiagonal::exportToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не удается открыть файл.");

    file << "MatrixDiagonal\n";
    file << size << "\n";
    for (double value : data) {
        file << value << " ";
    }
    file << "\n";

    file.close();
}



//вывод матрицы на экран
void MatrixDiagonal::print() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                std::cout << data[i] << " ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
}
