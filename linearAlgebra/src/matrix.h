#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct matrix *Matrix;

// Matrix creation and destruction

Matrix matrixCreateZeros(int rows, int columns);
Matrix matrixCreateEmpty(int rows, int columns);
Matrix matrixCreate(int rows, int columns, double data[][columns]);
void matrixFree(Matrix matrix);

void matrixFree(Matrix matrix);

// Matrix operations

Matrix matrixAdd(Matrix matrix1, Matrix matrix2);
Matrix matrixSubtract(Matrix matrix1, Matrix matrix2);
Matrix matrixMultiply(Matrix matrix1, Matrix matrix2);
Matrix matrixTranspose(Matrix matrix);
Matrix matrixScalarMultiply(Matrix matrix, double scalar);
Matrix matrixEye(int n);
Matrix matrixRandom(int rows, int columns);

// Matrix getters 

int matrixGetRows(Matrix matrix);
int matrixGetColumns(Matrix matrix);
double matrixGetElement(Matrix matrix, int row, int column);

// Matrix setters

void matrixSetElement(Matrix matrix, int row, int column, double value);

// Matrix I/O

void matrixPrint(Matrix matrix);
void matrixSaveToFile(Matrix matrix, char* filename);