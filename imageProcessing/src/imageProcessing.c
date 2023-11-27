#include "imageProcessing.h"

struct image {
    int width;
    int height;
    int channels;
    Matrix data;
};

Image imageImport(char* filename) {

}

Image imageCreate(int width, int height, int channels) {

}

Image imageCreateFromMatrix(Matrix matrix) {

}

Image imageCreateFromData(int width, int height, int channels, double data[][width][channels]) {

}

Matrix imageGetData(Image image) {

}

void imageFree(Image image) {

}

void imageSave(Image image, char* filename) {

}