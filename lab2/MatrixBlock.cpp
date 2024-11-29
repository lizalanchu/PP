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
    for (int i = 0; i < subRows; ++i) {
        for (int j = 0; j < subCols; ++j) {
            // Перемещаем блоки
            int newRow = j;
            int newCol = i;

            // Перебираем все элементы внутри блока
            for (int k = 0; k < blockRows; ++k) {
                for (int l = 0; l < blockCols; ++l) {
                    // Перемещаем элементы внутри блока
                    result->blocks[newRow * subCols + newCol][l][k] = blocks[i * subCols + j][k][l];
                }
            }
        }
    }
    return result; // Возвращаем транспонированную матрицу
}



void MatrixBlock::set(int blockRow, int blockCol, int subRow, int subCol, double value) {
    if (blockRow >= blockRows || blockCol >= blockCols || subRow >= subRows || subCol >= subCols || blockRow < 0 || blockCol < 0 || subRow < 0 || subCol < 0) {
        throw std::out_of_range("Matrix block index out of range");
    }
    blocks[blockRow * blockRows + blockCol][subRow][subCol] = value;
}

        

// Импорт матрицы из файла
void MatrixBlock::importFromFile(const std::string& filename) {
    std::ifstream file(filename); // Открываем файл
    if (!file.is_open()) { // Проверка, открытие файла прошло успешно
        throw std::runtime_error("Unable to open file.");
    }

    std::string className;
    file >> className; // Читаем имя класса
    if (className != "MatrixBlock") { // Проверяем, совпадает ли имя класса с ожидаемым
        throw std::runtime_error("Invalid matrix type.");
    }

    file >> blockRows >> blockCols >> subRows >> subCols; // Читаем размеры блоков и матрицы
    blocks.resize(subRows * subCols, std::vector<std::vector<double>>(blockRows, std::vector<double>(blockCols))); // Изменяем размер массива

    // Читаем элементы каждого блока
    for (int b = 0; b < subRows * subCols; ++b) {
        for (int i = 0; i < blockRows; ++i) {
            for (int j = 0; j < blockCols; ++j) {
                if (!(file >> blocks[b][i][j])) { // Если возникла ошибка при чтении
                    throw std::runtime_error("Error reading block data.");
                }
            }
        }
    }

    file.close(); // Закрываем файл
}

// Экспорт матрицы в файл
void MatrixBlock::exportToFile(const std::string& filename) const {
    std::ofstream file(filename); // Открываем файл для записи
    if (!file.is_open()) { // Проверка успешного открытия файла
        throw std::runtime_error("Unable to open file.");
    }

    file << "MatrixBlock\n"; // Пишем тип матрицы
    file << blockRows << " " << blockCols << " " << subRows << " " << subCols << "\n"; // Пишем размеры

    // Записываем элементы каждого блока
    for (const auto& block : blocks) {
        for (const auto& row : block) {
            for (double value : row) {
                file << value << " "; // Пишем значения
            }
            file << "\n"; // Новая строка
        }
        file << "\n"; // Разделяем блоки пустой строкой
    }

    file.close(); // Закрываем файл
}

// Для отладки: вывод матрицы на консоль
void MatrixBlock::print() const {
    for (const auto& block : blocks) {
        for (const auto& row : block) {
            for (double value : row) {
                std::cout << value << " "; // Печать значений в строке
            }
            std::cout << "\n"; // Переход на новую строку
        }
        std::cout << "\n"; // Разделяем блоки пустой строкой
    }
}
