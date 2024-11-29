#ifndef MATRIXDIAGONAL_H
#define MATRIXDIAGONAL_H

#include "Matrix.h"
#include <vector>

class MatrixDiagonal : public Matrix {
private:
    std::vector<double> data;
    int size;

public:
    MatrixDiagonal(int size);

    Matrix* add(const Matrix& other) const override;
    Matrix* subtract(const Matrix& other) const override;
    Matrix* elementwiseMultiply(const Matrix& other) const override;
    Matrix* multiply(const Matrix& other) const override;
    Matrix* transpose() const override;

    void set(int row, int col, double value);

    void importFromFile(const std::string& filename) override;
    void exportToFile(const std::string& filename) const override;
    void print() const override;
};

#endif // MATRIXDIAGONAL_H
