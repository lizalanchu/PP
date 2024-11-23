#ifndef MATRIXBLOCK_H
#define MATRIXBLOCK_H

#include "Matrix.h"
#include <vector>

class MatrixBlock  : public Matrix {
    // Код класса
public:

    Matrix* add(const Matrix& other) const override;
    Matrix* subtract(const Matrix& other) const override;
    Matrix* elementwiseMultiply(const Matrix& other) const override;
    Matrix* multiply(const Matrix& other) const override;
    Matrix* transpose() const override;

    void importFromFile(const std::string& filename) override;
    void exportToFile(const std::string& filename) const override;
};

#endif // MATRIXBLOCK_H 


