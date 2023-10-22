#include "../../test_framework/src/test_framework.h"
#include "../src/matrix.h"

// Test creation and deletion

TEST(testZeroMatrix) {

    Matrix m = matrixCreateZeros(3, 3);
    for (int i = 0; i < matrixGetRows(m); i++) {
        for (int j = 0; j < matrixGetColumns(m); j++) {
            ASSERT(matrixGetElement(m, i, j) == 0);
        }
    }

    matrixFree(m);
}

// Test getters

TEST(testGetters) {

    Matrix m = matrixCreateZeros(10, 10);

    ASSERT(matrixGetRows(m) == 10);
    ASSERT(matrixGetColumns(m) == 10);

    matrixFree(m);
}

// Test setters

TEST(testSetters) {

    Matrix m = matrixCreateZeros(50, 50);

    for (int i = 0; i < matrixGetRows(m); i++) {
        for (int j = 0; j < matrixGetColumns(m); j++) {
            matrixSetElement(m, i, j, i + j);
        }
    }

    for (int i = 0; i < matrixGetRows(m); i++) {
        for (int j = 0; j < matrixGetColumns(m); j++) {
            ASSERT(matrixGetElement(m, i, j) == i + j);
        }
    }

    matrixFree(m);

}

// Test operations

TEST(testAdd) {

    Matrix m = matrixCreateZeros(10, 10);

    for (int i = 0; i < matrixGetRows(m); i++) {
        for (int j = 0; j < matrixGetColumns(m); j++) {
            matrixSetElement(m, i, j, i + j);
        }
    }

    Matrix n = matrixCreateZeros(10, 10);

    for (int i = 0; i < matrixGetRows(n); i++) {
        for (int j = 0; j < matrixGetColumns(n); j++) {
            matrixSetElement(n, i, j, i + j);
        }
    }

    Matrix sum = matrixAdd(m, n);

    for (int i = 0; i < matrixGetRows(sum); i++) {
        for (int j = 0; j < matrixGetColumns(sum); j++) {
            ASSERT(matrixGetElement(sum, i, j) == 2 * (i + j));
        }
    }

    matrixFree(m);
    matrixFree(n);
    matrixFree(sum);
}

TEST(testSubtract) {

    Matrix m1 = matrixCreateZeros(10, 10);

    for (int i = 0; i < matrixGetRows(m1); i++) {
        for (int j = 0; j < matrixGetColumns(m1); j++) {
            matrixSetElement(m1, i, j, i + j);
        }
    }

    Matrix m2 = matrixCreateZeros(10, 10);

    for (int i = 0; i < matrixGetRows(m2); i++) {
        for (int j = 0; j < matrixGetColumns(m2); j++) {
            matrixSetElement(m2, i, j, i + j);
        }
    }

    Matrix sum = matrixSubtract(m1, m2);

    for (int i = 0; i < matrixGetRows(sum); i++) {
        for (int j = 0; j < matrixGetColumns(sum); j++) {
            ASSERT(matrixGetElement(sum, i, j) == 0);
        }
    }

    matrixFree(m1);
    matrixFree(m2);
    matrixFree(sum);
}

TEST(testTranspose) {

    Matrix m = matrixCreateZeros(5, 10);

    for (int i = 0; i < matrixGetRows(m); i++) {
        for (int j = 0; j < matrixGetColumns(m); j++) {
            matrixSetElement(m, i, j, i + j);
        }
    }

    Matrix transpose = matrixTranspose(m);

    for (int i = 0; i < matrixGetRows(transpose); i++) {
        for (int j = 0; j < matrixGetColumns(transpose); j++) {
            ASSERT(matrixGetElement(transpose, i, j) == matrixGetElement(m, j, i));
        }
    }

    matrixFree(transpose);
    matrixFree(m);
}

TEST(testMultiply) {
    
    double data1[3][2] = {{3, 4}, {3, 6}, {1, 3}};
    double data2[2][4] = {{5, 4, 3, 5}, {3, 5, 3, 3}};
    double productData[3][4] = {{27, 32, 21, 27}, {33, 42, 27, 33}, {14, 19, 12, 14}};

    Matrix m1 = matrixCreate(3, 2, data1);
    Matrix m2 = matrixCreate(2, 4, data2);

    Matrix product = matrixMultiply(m1, m2);

    for (int i = 0; i < matrixGetRows(product); i++) {
        for (int j = 0; j < matrixGetColumns(product); j++) {
            ASSERT(matrixGetElement(product, i, j) == productData[i][j]);
        }
    }

    matrixFree(m1);
    matrixFree(m2);
    matrixFree(product);
}

TEST(testIdentitiyMatrix) {
    
    Matrix m = matrixEye(10);

    for (int i = 0; i < matrixGetRows(m); i++) {
        for (int j = 0; j < matrixGetColumns(m); j++) {
            if (i == j) {
                ASSERT(matrixGetElement(m, i, j) == 1);
            } else {
                ASSERT(matrixGetElement(m, i, j) == 0);
            }
        }
    }

    matrixFree(m);
}

// Test I/O

TEST(testPrinting) {

    // this is just for visual validation and memory validation

    printf("\n");
    Matrix m = matrixRandom(10, 10);
    matrixPrint(m);
    matrixFree(m);
    printf("\n");
}

// needed for test framework
int main() {
    run_tests();
    return 0;
}
