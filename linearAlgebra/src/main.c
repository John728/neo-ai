#include "matrix.h"

// For manual testing

int main() {
    double data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};
    Matrix m = matrixCreate(3, 3, data);

    printf("det: %f\n", matrixDet(m));

    matrixFree(m);
}