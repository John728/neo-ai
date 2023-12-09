#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix *Matrix;

// Matrix creation and destruction

Matrix matrixCreateZeros(int rows, int columns);
Matrix matrixCreateEmpty(int rows, int columns);
Matrix matrixCreate(int rows, int columns, double data[][columns]);
void matrixFree(Matrix matrix);

// Matrix operations

Matrix matrixAdd(Matrix matrix1, Matrix matrix2);
Matrix matrixSubtract(Matrix matrix1, Matrix matrix2);
Matrix matrixMultiply(Matrix matrix1, Matrix matrix2);
Matrix matrixTranspose(Matrix matrix);
Matrix matrixScalarMultiply(Matrix matrix, double scalar);
Matrix matrixEye(int n);
Matrix matrixRandom(int rows, int columns);
double matrixDet(Matrix matrix);
Matrix matrixGetSubMatrix(Matrix matrix, int x1, int y1, int x2, int y2);
Matrix matrixJoin(Matrix m1, Matrix m2);
Matrix matrixPool(Matrix matrix, int n, char *type);
Matrix matrixConvolve(Matrix matrix, Matrix kernal);
double matrixDot(Matrix matrix1, Matrix matrix2);
// Matrix getters 

int matrixGetRows(Matrix matrix);
int matrixGetColumns(Matrix matrix);
double matrixGetElement(Matrix matrix, int row, int column);
double **matrixGetData(Matrix matrix);

// Matrix setters

void matrixSetElement(Matrix matrix, int row, int column, double value);

// Matrix I/O

void matrixPrint(Matrix matrix);
void matrixSaveToFile(Matrix matrix, char* filename);


