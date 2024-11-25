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
     // Транспонирование 
}
