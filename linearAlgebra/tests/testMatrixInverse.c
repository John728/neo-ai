#include "../../test_framework/src/test_framework.h"
#include "../src/matrixInverse.h"

TEST_FAIL(testInverseOfNonInvertibleMatrix) {
    
    double data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m = matrixCreate(3, 3, data);

    Matrix inverse = matrixInverseGaussJordan(m);

    matrixFree(m);
    matrixFree(inverse);
}

TEST_FAIL(testNoneSquareMatrix) {
    double data[3][2] = {{1, 2}, {4, 5}, {7, 8}};
    Matrix m = matrixCreate(3, 2, data);

    Matrix inverse = matrixInverseGaussJordan(m);

    matrixFree(m);
    matrixFree(inverse);
}

int main() {
    run_tests();
    return 0;
}