#include "./matrixInverse.h"

// subtract row 1 from row 2
void matrixSubtractRow(Matrix matrix, int row1, int row2, double scalar) {
    for (int i = 0; i < matrixGetColumns(matrix); i++) {
        matrixSetElement(matrix, row2, i,
            matrixGetElement(matrix, row2, i) - matrixGetElement(matrix, row1, i) * scalar
        );
    }
}

void matrixScaleRow(Matrix matrix, int row, double scalar) {
    for (int i = 0; i < matrixGetColumns(matrix); i++) {
        matrixSetElement(matrix, row, i,
            matrixGetElement(matrix, row, i) * scalar
        );
    }
}

Matrix matrixInverse(Matrix matrix) {

}


// https://online.stat.psu.edu/statprogram/reviews/matrix-algebra/gauss-jordan-elimination
Matrix matrixInverseGaussJordan(Matrix matrix) {
    int n = matrixGetRows(matrix);
    int m = matrixGetColumns(matrix);
    if (n != m) {
        // Matrix is not square, cannot find inverse.
        return NULL;
    }

    Matrix augmented = matrixCreateEmpty(n, 2 * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrixSetElement(augmented, i, j, matrixGetElement(matrix, i, j));
            if (i == j) {
                matrixSetElement(augmented, i, j + n, 1.0);
            } else {
                matrixSetElement(augmented, i, j + n, 0.0);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        double pivot = matrixGetElement(augmented, i, i);
        if (pivot == 0) {
            int swapRow = -1;
            for (int k = i + 1; k < n; k++) {
                if (matrixGetElement(augmented, k, i) != 0) {
                    swapRow = k;
                    break;
                }
            }
            if (swapRow == -1) {
                // Matrix is singular, cannot find inverse.
                matrixFree(augmented);
                return NULL;
            }

            // Swap rows
            for (int j = 0; j < 2 * n; j++) {
                double temp = matrixGetElement(augmented, i, j);
                matrixSetElement(augmented, i, j, matrixGetElement(augmented, swapRow, j));
                matrixSetElement(augmented, swapRow, j, temp);
            }
            pivot = matrixGetElement(augmented, i, i);
        }

        // Scale current row to make pivot element 1
        for (int j = 0; j < 2 * n; j++) {
            matrixSetElement(augmented, i, j, matrixGetElement(augmented, i, j) / pivot);
        }

        // Zero out above and below the pivot
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = matrixGetElement(augmented, k, i);
                for (int j = 0; j < 2 * n; j++) {
                    matrixSetElement(augmented, k, j, matrixGetElement(augmented, k, j) - factor * matrixGetElement(augmented, i, j));
                }
            }
        }
    }

    // Extract the inverse matrix
    Matrix inverse = matrixCreateEmpty(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrixSetElement(inverse, i, j, matrixGetElement(augmented, i, j + n));
        }
    }
    matrixFree(augmented);
    return inverse;
}



void main() {

    double data[2][2] = {{1, 5, 3}, {2, 6, 4}};

    Matrix m = matrixCreate(2, 2, data);

    matrixPrint(matrixInverseGaussJordan(m))    ;
}