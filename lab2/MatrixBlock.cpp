#include "MatrixBlock.h"
#include <fstream>       // Для работы с файлами
#include <stdexcept>     // Для обработки исключений
#include <iostream>      // Для отладки



MatrixBlock::MatrixBlock(int blockRows, int blockCols, int subRows, int subCols)
    : blockRows(blockRows),   // Инициализация количества строк в одном блоке
      blockCols(blockCols),   // Инициализация количества столбцов в одном блоке
      subRows(subRows),       // Инициализация количества блоков по вертикали
      subCols(subCols) {      // Инициализация количества блоков по горизонтали
    // Изменение размера массива blocks: каждый элемент — это блок размером blockRows x blockCols
    blocks.resize(subRows * subCols, std::vector<std::vector<double>>(blockRows, std::vector<double>(blockCols)));
}

Matrix* MatrixBlock::add(const Matrix& other) const {
     // Приведение параметра other к типу MatrixBlock
    const MatrixBlock* otherBlock = dynamic_cast<const MatrixBlock*>(&other);

    // Проверка: если приведение не удалось или размеры матриц не совпадают, выбрасываем исключение
    if (!otherBlock || subRows != otherBlock->subRows || subCols != otherBlock->subCols) {
        throw std::invalid_argument("Размеры матрицы не совпадают для сложения.");
    }

    // Создаем новую матрицу для хранения результата сложения
    MatrixBlock* result = new MatrixBlock(blockRows, blockCols, subRows, subCols);

    // Проходим по каждому блоку матрицы
    for (int b = 0; b < subRows * subCols; ++b) {
        for (int i = 0; i < blockRows; ++i) {
            for (int j = 0; j < blockCols; ++j) {
                // Складываем соответствующие элементы блоков
                result->blocks[b][i][j] = blocks[b][i][j] + otherBlock->blocks[b][i][j];
            }
        }
    }
    return result; // Возвращаем указатель на результирующую матрицу
}




Matrix* MatrixBlock::subtract(const Matrix& other) const {
    const MatrixBlock* otherBlock = dynamic_cast<const MatrixBlock*>(&other); // Приведение параметра other к типу MatrixBlock
    if (!otherBlock || subRows != otherBlock->subRows || subCols != otherBlock->subCols) {
        throw std::invalid_argument("Размеры матрицы не совпадают для вычитания.");
    }

    MatrixBlock* result = new MatrixBlock(blockRows, blockCols, subRows, subCols); // Создаем новую матрицу для результата

    // Проходим по каждому блоку матрицы и вычитаем элементы
    for (int b = 0; b < subRows * subCols; ++b) {
        for (int i = 0; i < blockRows; ++i) {
            for (int j = 0; j < blockCols; ++j) {
                result->blocks[b][i][j] = blocks[b][i][j] - otherBlock->blocks[b][i][j];
            }
        }
    }
    return result; // Возвращаем указатель на результирующую матрицу
}




Matrix* MatrixBlock::elementwiseMultiply(const Matrix& other) const {
    // Реализация поэлементного умножения 
}

Matrix* MatrixBlock::multiply(const Matrix& other) const {
    // Реализация матричного умножения 
}

Matrix* MatrixBlock::transpose() const {
    // Транспонирование
}
