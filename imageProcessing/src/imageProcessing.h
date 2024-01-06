#include "../../linearAlgebra/src/matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct image *Image;

Matrix convolve(Matrix image, Matrix kernel);

Image imageImport(char* filename);
Image imageCreate(int width, int height, int channels);
Image imageCreateFromMatrix(Matrix matrix);
Image imageCreateFromData(int width, int height, int channels, double data[][width][channels]);
Matrix imageGetData(Image image);
void imageFree(Image image);
void imageSave(Image image, char* filename);


// Getters and setters

int imageGetWidth(Image image);
int imageGetHeight(Image image);
int imageGetChannels(Image image);
Matrix imageGetData(Image image);
Matrix imageGetDataFromPath(char* filename);

void imageSetWidth(Image image, int width);
void imageSetHeight(Image image, int height);
void imageSetChannels(Image image, int channels);
