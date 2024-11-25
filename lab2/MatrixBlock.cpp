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
    const MatrixBlock* otherBlock = dynamic_cast<const MatrixBlock*>(&other); // Приведение параметра other к типу MatrixBlock
    if (!otherBlock || subRows != otherBlock->subRows || subCols != otherBlock->subCols) {
        throw std::invalid_argument("Размеры матрицы не совпадают при поэлементном умножении.");
    }

    // Создаем новую матрицу для результата
    MatrixBlock* result = new MatrixBlock(blockRows, blockCols, subRows, subCols); 

    // Проходим по каждому блоку и выполняем поэлементное умножение
    for (int b = 0; b < subRows * subCols; ++b) {
        for (int i = 0; i < blockRows; ++i) {
            for (int j = 0; j < blockCols; ++j) {
                result->blocks[b][i][j] = blocks[b][i][j] * otherBlock->blocks[b][i][j]; // Умножаем соответствующие элементы
            }
        }
    }
    return result; // Возвращаем результат 
}



Matrix* MatrixBlock::multiply(const Matrix& other) const {
    const MatrixBlock* otherBlock = dynamic_cast<const MatrixBlock*>(&other);

    // Проверка совместимости типов
    if (!otherBlock) {
        throw std::invalid_argument("Несоответствие типа матрицы: ожидаемый MatrixBlock.");
    }

    // Проверка совместимости размеров блоков
    if (blockCols != otherBlock->blockRows) {
        throw std::invalid_argument("Размеры блоков не совпадают для умножения.");
    }

    // Проверка совместимости структур матриц
    if (subCols != otherBlock->subRows) {
        throw std::invalid_argument("Блочная структура матрицы не подходит для умножения.");
    }

    // Создание результирующей матрицы
    MatrixBlock* result = new MatrixBlock(blockRows, otherBlock->blockCols, subRows, otherBlock->subCols);

    // Умножение блоков
    for (int i = 0; i < subRows; ++i) {                // Блоки строк первой матрицы
        for (int j = 0; j < otherBlock->subCols; ++j) { // Блоки столбцов второй матрицы
            for (int k = 0; k < subCols; ++k) {        // Общие блоки (столбцы первой = строки второй)
                // Умножение блоков (i, k) * (k, j)
                for (int bi = 0; bi < blockRows; ++bi) { // Внутренние строки блока
                    for (int bj = 0; bj < otherBlock->blockCols; ++bj) { // Внутренние столбцы блока
                        for (int bk = 0; bk < blockCols; ++bk) { // Внутренние элементы блока
                            result->blocks[i * result->subCols + j][bi][bj] += 
                                blocks[i * subCols + k][bi][bk] * 
                                otherBlock->blocks[k * otherBlock->subCols + j][bk][bj];
                        }
                    }
                }
            }
        }
    }

    return result; // Возвращаем указатель на новую матрицу
}



Matrix* MatrixBlock::transpose() const {
    MatrixBlock* result = new MatrixBlock(blockCols, blockRows, subCols, subRows); // Новый объект для транспонированной матрицы

    // Проходим по блокам и меняем их местами
    for (int b1 = 0; b1 < subRows; ++b1) {
        for (int b2 = 0; b2 < subCols; ++b2) {
            result->blocks[b2][b1] = blocks[b1][b2]; // Меняем местами блоки
        }
    }
    return result; // Возвращаем транспонированную матрицу
}
