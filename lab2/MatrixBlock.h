#ifndef MATRIXBLOCK_H
#define MATRIXBLOCK_H

#include "Matrix.h"
#include <vector>
#include "MatrixDense.h"

class MatrixBlock  : public Matrix {
private:
    std::vector<MatrixDense> blocks;
    int blockRows, blockCols;

public:
    MatrixBlock(int blockRows, int blockCols, int subRows, int subCols);

    Matrix* add(const Matrix& other) const override;
    Matrix* subtract(const Matrix& other) const override;
    Matrix* elementwiseMultiply(const Matrix& other) const override;
    Matrix* multiply(const Matrix& other) const override;
    Matrix* transpose() const override;

    void importFromFile(const std::string& filename) override;
    void exportToFile(const std::string& filename) const override;
};

#endif // MATRIXBLOCK_H 


