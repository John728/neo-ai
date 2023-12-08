#include "../../test_framework/src/test_framework.h"
#include "../src/matrix.h"

// ------------------------------------------------
// Test creation and deletion
// ------------------------------------------------

TEST(testZeroMatrix) {

    Matrix m = matrixCreateZeros(3, 3);
    for (int i = 0; i < matrixGetRows(m); i++) {
        for (int j = 0; j < matrixGetColumns(m); j++) {
            ASSERT(matrixGetElement(m, i, j) == 0);
        }
    }

    matrixFree(m);
}

// ------------------------------------------------
// Test getters
// ------------------------------------------------

TEST(testGetters) {

    Matrix m = matrixCreateZeros(10, 10);

    ASSERT(matrixGetRows(m) == 10);
    ASSERT(matrixGetColumns(m) == 10);

    matrixFree(m);
}

// ------------------------------------------------
// Test setters
// ------------------------------------------------

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

// ------------------------------------------------
// Test operations
// ------------------------------------------------

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

TEST_FAIL(testFailAddWrongDimensions) {
    
        Matrix m = matrixCreateZeros(10, 10);
        Matrix n = matrixCreateZeros(10, 11);
    
        Matrix sum = matrixAdd(m, n);
    
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

TEST_FAIL(testFailSubtractWrongDimensions) {
    
        Matrix m = matrixCreateZeros(10, 10);
        Matrix n = matrixCreateZeros(10, 11);
    
        Matrix sum = matrixSubtract(m, n);
    
        matrixFree(m);
        matrixFree(n);
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

TEST_FAIL(testFailMultiplyWrongDimensions) {
    
    Matrix m = matrixCreateZeros(2, 10);
    Matrix n = matrixCreateZeros(9, 11);

    Matrix sum = matrixMultiply(m, n);

    matrixFree(m);
    matrixFree(n);
    matrixFree(sum);
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

TEST_FAIL(testAccessOutOfBounds) {
    Matrix m = matrixCreateZeros(2, 2);
    matrixGetElement(m, 10, 10);
    matrixFree(m);
}

TEST(testDeterminant) {
    double data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m = matrixCreate(3, 3, data);

    ASSERT(matrixDet(m) == 0);

    matrixFree(m);


    double data1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};
    Matrix m1 = matrixCreate(3, 3, data1);

    ASSERT(matrixDet(m1) == -3);

    matrixFree(m1);
}

TEST_FAIL(testDetFailsOnNonSquare) {
    double data[3][2] = {{1, 2}, {4, 5}, {7, 8}};
    Matrix m = matrixCreate(3, 2, data);

    ASSERT(matrixDet(m) == 0);

    matrixFree(m);
}

TEST(testPoolMax) {
    double data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m = matrixCreate(3, 3, data);

    Matrix pooled = matrixPool(m, 2, "max");

    ASSERT(matrixGetElement(pooled, 0, 0) == 5);
    ASSERT(matrixGetElement(pooled, 0, 1) == 6);
    ASSERT(matrixGetElement(pooled, 1, 0) == 8);
    ASSERT(matrixGetElement(pooled, 1, 1) == 9);

    matrixFree(m);
    matrixFree(pooled);
}

TEST(testPoolMaxFullSize) {
    double data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m = matrixCreate(3, 3, data);

    Matrix pooled = matrixPool(m, 3, "max");

    ASSERT(matrixGetElement(pooled, 0, 0) == 9);

    matrixFree(m);
    matrixFree(pooled);
}

TEST(testPoolMaxNonSquare) {
    double data[3][2] = {{1, 2}, {4, 5}, {7, 8}};
    Matrix m = matrixCreate(3, 2, data);

    Matrix pooled = matrixPool(m, 2, "max");

    ASSERT(matrixGetElement(pooled, 0, 0) == 5);
    ASSERT(matrixGetElement(pooled, 0, 1) == 6);
    ASSERT(matrixGetElement(pooled, 1, 0) == 8);

    matrixFree(m);
    matrixFree(pooled);
}

TEST(testPoolMin) {
    double data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m = matrixCreate(3, 3, data);

    Matrix pooled = matrixPool(m, 2, "min");

    ASSERT(matrixGetElement(pooled, 0, 0) == 1);
    ASSERT(matrixGetElement(pooled, 0, 1) == 2);
    ASSERT(matrixGetElement(pooled, 1, 0) == 4);
    ASSERT(matrixGetElement(pooled, 1, 1) == 5);

    matrixFree(m);
    matrixFree(pooled);

}

TEST(testPoolAvg) {
    double data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m = matrixCreate(3, 3, data);

    Matrix pooled = matrixPool(m, 2, "avg");

    ASSERT(matrixGetElement(pooled, 0, 0) == 3);
    ASSERT(matrixGetElement(pooled, 0, 1) == 4);
    ASSERT(matrixGetElement(pooled, 1, 0) == 6);
    ASSERT(matrixGetElement(pooled, 1, 1) == 7);

    matrixFree(m);
    matrixFree(pooled);

}

TEST(testConvolve) {
    double data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m = matrixCreate(3, 3, data);

    double kernelData[2][2] = {{1, 2}, {3, 4}};
    Matrix kernel = matrixCreate(2, 2, kernelData);

    Matrix convolved = matrixConvolve(m, kernel);

    // ASSERT(matrixGetElement(convolved, 0, 0) == 1);
    // ASSERT(matrixGetElement(convolved, 0, 1) == 4);
    // ASSERT(matrixGetElement(convolved, 1, 0) == 10);
    // ASSERT(matrixGetElement(convolved, 1, 1) == 16);

    // matrixFree(m);
    // matrixFree(kernel);
    // matrixFree(convolved);
}

TEST(testDot) {
    
}

// ------------------------------------------------
// Test I/O
// ------------------------------------------------

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