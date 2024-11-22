#ifndef MATRIX_H //смотрим используется ли уже файл
#define MATRIX_H // определяем 

#include <string> // подкл. библ. для работы с текстом

// Абстрактный класс Matrix
class Matrix {
public:
    virtual ~Matrix() = default; // деструктор

    virtual Matrix* add(const Matrix& other) const = 0; //сложение
    virtual Matrix* subtract(const Matrix& other) const = 0;//вычитание 
    virtual Matrix* elementwiseMultiply(const Matrix& other) const = 0;//умножение двух матриц поэлементно
    virtual Matrix* multiply(const Matrix& other) const = 0;//умножение матриц, но по правилам матричного умножения
    virtual Matrix* transpose() const = 0;//транспонирование матрицы

    virtual void importFromFile(const std::string& filename) = 0; //функция для считывания данных матрицы из файла
    virtual void exportToFile(const std::string& filename) const = 0;//функция для записи матрицы в файл
};

#endif // MATRIX_H
