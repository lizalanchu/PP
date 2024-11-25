#ifndef MATRIXBLOCK_H
#define MATRIXBLOCK_H

#include "Matrix.h"
#include <vector>
#include <string>

class MatrixBlock  : public Matrix {
private:
    int blockRows; // Размер строк в блоке
    int blockCols; // Размер столбцов в блоке
    int subRows;   // Количество блоков по строкам
    int subCols;   // Количество блоков по столбцам

    // Вектор блоков матрицы (каждый блок — это двумерный вектор)
    std::vector<std::vector<std::vector<double>>> blocks;

public:
    MatrixBlock(int blockRows, int blockCols, int subRows, int subCols);

    Matrix* add(const Matrix& other) const override;
    Matrix* subtract(const Matrix& other) const override;
    Matrix* elementwiseMultiply(const Matrix& other) const override;
    Matrix* multiply(const Matrix& other) const override;
    Matrix* transpose() const override;

    void importFromFile(const std::string& filename) override;
    void exportToFile(const std::string& filename) const override;
    void print() const override;
};

#endif // MATRIXBLOCK_H 


