#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

struct matrix {
    int rows;
    int columns;
    double **data;
};

Matrix matrixCreateZeros(int rows, int columns) {
    Matrix newMatrix = matrixCreateEmpty(rows, columns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++){
            newMatrix->data[i][j] = 0;
        }
    }

    return newMatrix;
}

Matrix matrixCreateEmpty(int rows, int columns) {
    Matrix newMatrix = malloc(sizeof(struct matrix));
    newMatrix->data = malloc(sizeof(double) * rows);
    
    for (int i = 0; i < rows; i++) {
        newMatrix->data[i] = malloc(sizeof(double) * columns);
    }
    
    newMatrix->columns = columns;
    newMatrix->rows = rows;
    return newMatrix;
}

Matrix matrixCreate(int rows, int columns, double data[][columns]) {
    
    Matrix newMatrix = matrixCreateEmpty(rows, columns);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++){
            newMatrix->data[i][j] = data[i][j];
        }
    }

    return newMatrix;
}

void matrixFree(Matrix matrix) {

    for (int i = 0; i < matrixGetRows(matrix); i++) {
        free(matrix->data[i]);
    }

    free(matrix->data);
    free(matrix);
}

// Getters

int matrixGetRows(Matrix matrix) {
    return matrix->rows;
}

int matrixGetColumns(Matrix matrix) {
    return matrix->columns;
}

double matrixGetElement(Matrix matrix, int row, int column) {

    // Raise error if out of bounds
    if (row < 0 || row >= matrixGetRows(matrix) || column < 0 || column >= matrixGetColumns(matrix)) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        abort();
    }

    return matrix->data[row][column];
}

// Matrix setters

void matrixSetElement(Matrix matrix, int row, int column, double value) {

    if (row < 0 || row >= matrixGetRows(matrix) || column < 0 || column >= matrixGetColumns(matrix)) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        abort();
    }

    matrix->data[row][column] = value;
}

void matrixSetRow(Matrix matrix, int row, double *data) {

    if (row < 0 || row >= matrixGetRows(matrix)) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        abort();
    }

    for (int i = 0; i < matrixGetColumns(matrix); i++) {
        matrixSetElement(matrix, row, i, data[i]);
    }

}

// Matrix operations

Matrix matrixAdd(Matrix matrix1, Matrix matrix2) {

    // Raise error if matrices are not the same size
    if (matrixGetRows(matrix1) != matrixGetRows(matrix2) || matrixGetColumns(matrix1) != matrixGetColumns(matrix2)) {
        fprintf(stderr, "Error: Matrices must be the same size to add them.\n");
        abort(); 
    }

    // Actually add
    Matrix newMatrix = matrixCreateEmpty(matrixGetRows(matrix1), matrixGetColumns(matrix1));

    for (int i = 0; i < matrixGetRows(matrix1); i++) {
        for (int j = 0; j < matrixGetColumns(matrix1); j++) {
            matrixSetElement(newMatrix, i, j, matrixGetElement(matrix1, i, j) + matrixGetElement(matrix2, i, j));
        }
    }

    return newMatrix;
}

Matrix matrixSubtract(Matrix matrix1, Matrix matrix2) {
    
    // Raise error if matrices are not the same size
    if (matrixGetRows(matrix1) != matrixGetRows(matrix2) || matrixGetColumns(matrix1) != matrixGetColumns(matrix2)) {
        fprintf(stderr, "Error: Matrices must be the same size to subtract them.\n");
        abort();
    }

    // Actually subtract
    Matrix newMatrix = matrixCreateEmpty(matrixGetRows(matrix1), matrixGetColumns(matrix1));

    for (int i = 0; i < matrixGetRows(matrix1); i++) {
        for (int j = 0; j < matrixGetColumns(matrix1); j++) {
            matrixSetElement(newMatrix, i, j, matrixGetElement(matrix1, i, j) - matrixGetElement(matrix2, i, j));
        }
    }

    return newMatrix;

}

/**
 * Multiply matrix1 by matrix2.
 * 
 * O(n^3)
*/
Matrix matrixMultiply(Matrix matrix1, Matrix matrix2) {
    
    // Raise error if matrices cannot be multiplied
    if (matrixGetColumns(matrix1) != matrixGetRows(matrix2)) {
        fprintf(stderr, "Error: Matrices cannot be multiplied.\n");
        abort();
    }

    Matrix newMatrix = matrixCreateZeros(matrixGetRows(matrix1), matrixGetColumns(matrix2));

    for (int i = 0; i < matrixGetRows(matrix1); i++) {
        for (int j = 0; j < matrixGetColumns(matrix2); j++) {
            for (int k = 0; k < matrixGetColumns(matrix1); k++) {
                matrixSetElement(newMatrix, i, j, matrixGetElement(newMatrix, i, j) + matrixGetElement(matrix1, i, k) * matrixGetElement(matrix2, k, j));
            }
        }
    }

    return newMatrix;

}

Matrix matrixTranspose(Matrix matrix) {
    
    Matrix newMatrix = matrixCreateZeros(matrixGetColumns(matrix), matrixGetRows(matrix));

    for (int i = 0; i < matrixGetRows(matrix); i++) {
        for (int j = 0; j < matrixGetColumns(matrix); j++) {
            matrixSetElement(newMatrix, j, i, matrixGetElement(matrix, i, j));
        }
    }

    return newMatrix;
}

Matrix matrixScalarMultiply(Matrix matrix, double scalar) {
    
    Matrix newMatrix = matrixCreateEmpty(matrixGetRows(matrix), matrixGetColumns(matrix));

    for (int i = 0; i < matrixGetRows(matrix); i++) {
        for (int j = 0; j < matrixGetColumns(matrix); j++) {
            matrixSetElement(newMatrix, i, j, matrixGetElement(matrix, i, j) * scalar);
        }
    }

    return newMatrix;
}

Matrix matrixEye(int n) {

    Matrix newMatrix = matrixCreateZeros(n, n);

    for (int i = 0; i < n; i++) {
        matrixSetElement(newMatrix, i, i, 1);
    }

    return newMatrix;

}

Matrix matrixRandom(int rows, int columns) {
    Matrix newMatrix = matrixCreateZeros(rows, columns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrixSetElement(newMatrix, i, j, i);
        }
    }

    return newMatrix;
}


/**
 * Resursive determinant function. Returns the determinant of matrix.
*/
double matrixDet(Matrix matrix) {

    if (matrixGetColumns(matrix) != matrixGetRows(matrix)) {
        fprintf(stderr, "Error: Matrices cannot be multiplied.\n");
        abort();
    }

    int n = matrixGetRows(matrix);

    if (n == 2) {
        return matrixGetElement(matrix, 0, 0) * matrixGetElement(matrix, 1, 1) - matrixGetElement(matrix, 0, 1) * matrixGetElement(matrix, 1, 0);
    } else {

        double result = 0;

        for (int i = 0; i < n; i++) {

            Matrix subMatrix = matrixGetSubMatrix(matrix, 1, 0, n - 1, i);

            result += matrixGetElement(matrix, 0, i) * matrixDet(subMatrix) * (i % 2 == 0 ? 1 : -1);

            matrixFree(subMatrix);

        }

        return result;

    }
}

// Get a sub matrix of a matrix between (x1, y1) and (x2, y2)
Matrix matrixGetSubMatrix(Matrix matrix, int x1, int y1, int x2, int y2) {
    
    // Raise error if out of bounds
    if (x1 < 0 || x1 >= matrixGetRows(matrix) || y1 < 0 || y1 >= matrixGetColumns(matrix) || x2 < 0 || x2 >= matrixGetRows(matrix) || y2 < 0 || y2 >= matrixGetColumns(matrix)) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        abort();
    }

    Matrix newMatrix = matrixCreateEmpty(x2 - x1 + 1, y2 - y1 + 1);

    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            matrixSetElement(newMatrix, i - x1, j - y1, matrixGetElement(matrix, i, j));
        }
    }

    return newMatrix;
}


// I/O

void matrixPrint(Matrix matrix) {
    for (int i = 0; i < matrixGetRows(matrix); i++) {
        for (int j = 0; j < matrixGetColumns(matrix); j++) {
            printf("%.3g ", matrixGetElement(matrix, i, j));
        }
        printf("\n");
    }
}