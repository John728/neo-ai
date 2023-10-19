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
        exit(1);
    }

    return matrix->data[row][column];
}

// Matrix setters

void matrixSetElement(Matrix matrix, int row, int column, double value) {

    if (row < 0 || row >= matrixGetRows(matrix) || column < 0 || column >= matrixGetColumns(matrix)) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        exit(1);
    }

    matrix->data[row][column] = value;
}

// Matrix operations

Matrix matrixAdd(Matrix matrix1, Matrix matrix2) {

    // Raise error if matrices are not the same size
    if (matrixGetRows(matrix1) != matrixGetRows(matrix2) || matrixGetColumns(matrix1) != matrixGetColumns(matrix2)) {
        fprintf(stderr, "Error: Matrices must be the same size to add them.\n");
        exit(1);
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
        exit(1);
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

Matrix matrixMultiply(Matrix matrix1, Matrix matrix2) {
    
    // Raise error if matrices cannot be multiplied
    if (matrixGetColumns(matrix1) != matrixGetRows(matrix2)) {
        fprintf(stderr, "Error: Matrices cannot be multiplied.\n");
        exit(1);
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
            matrixSetElement(newMatrix, i, j, i + j % 1248);
        }
    }

    return newMatrix;
}