#include "../../linearAlgebra/src/matrix.h"
#include <stdlib.h>

typedef struct image *Image;

Matrix convolve(Matrix image, Matrix kernel);

Image imageImport(char* filename);
Image imageCreate(int width, int height, int channels);
Image imageCreateFromMatrix(Matrix matrix);
Image imageCreateFromData(int width, int height, int channels, double data[][width][channels]);
Matrix imageGetData(Image image);
void imageFree(Image image);
void imageSave(Image image, char* filename);