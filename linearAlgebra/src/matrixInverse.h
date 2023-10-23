#include "matrix.h"

Matrix matrixInverseGaussJordan(Matrix matrix);
Matrix matrixInverse(Matrix matrix);
void matrixScaleRow(Matrix matrix, int row, double scalar);
void matrixSubtractRow(Matrix matrix, int row1, int row2, double scalar);