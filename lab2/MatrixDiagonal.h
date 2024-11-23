#ifndef MATRIXDIAGONAL_H
#define MATRIXDIAGONAL_H

#include "Matrix.h"
#include <vector>

class MatrixDiagonal : public Matrix {
//код
public:
    
    Matrix* add(const Matrix& other) const override;
    Matrix* subtract(const Matrix& other) const override;
    Matrix* elementwiseMultiply(const Matrix& other) const override;
    Matrix* multiply(const Matrix& other) const override;
    Matrix* transpose() const override;

    void importFromFile(const std::string& filename) override;
    void exportToFile(const std::string& filename) const override;
};

#endif // MATRIXDIAGONAL_H
