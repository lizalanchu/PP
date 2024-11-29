#ifndef MATRIXDENSE_H
#define MATRIXDENSE_H

#include "Matrix.h"
#include <vector>

class MatrixDense : public Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows, cols;

public:
    MatrixDense(int rows, int cols);

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

#endif // MATRIXDENSE_H 
