#include "matrix.h"
#include "matrixInverse.h"

// For manual testing

int main() {
    double data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};
    Matrix m = matrixCreate(3, 3, data);

    double kernalData[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};
    Matrix kernal = matrixCreate(2, 2, kernalData);

    matrixPrint(
        matrixConvolve(m, kernal)
    );

    matrixFree(m);
}