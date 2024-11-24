#include "MatrixBlock.h"

MatrixBlock::MatrixBlock(int blockRows, int blockCols, int subRows, int subCols)
    : blockRows(blockRows), blockCols(blockCols) {
    blocks.resize(blockRows * blockCols, MatrixDense(subRows, subCols));
}

Matrix* MatrixBlock::add(const Matrix& other) const {
    // Реализация сложения 
}

Matrix* MatrixBlock::subtract(const Matrix& other) const {
    // Реализация вычитания 
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
