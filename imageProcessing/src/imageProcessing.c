#include "imageProcessing.h"


struct image {
    int width;
    int height;
    int channels;
    Matrix data;
};

/**
 * For now, format is always Monochrome Bitmap
*/
Image imageImport(char* filename) {

    FILE* file = fopen(filename, "r");
    
    // If file does not exist, display error and abort
    if (file == NULL) {
        fprintf(stderr, "Error: file %s does not exist\n", filename);
        abort();
    }

    char header[2];
    fread(header, sizeof(char), 2, file);
    if (strcmp(header, "BM") != 0) {
        fprintf(stderr, "Error: file %s is not Monochrome Bitmap\n", filename);
        abort();
    }

    // read data into a Matrix
    int width, height;
    fread(&width, sizeof(int), 1, file);
    fread(&height, sizeof(int), 1, file);

    double data[height][width];
    fread(data, sizeof(double), height * width, file);

    fclose(file);

    Matrix matrix = matrixCreate(height, width, data);

    Image image = malloc(sizeof(struct image));
    image->width = width;
    image->height = height;
    image->channels = 1;
    image->data = matrix;

    return image;
}

void imageFree(Image image) {
    matrixFree(image->data);
    free(image);
}

void imageSave(Image image, char* filename) {
    FILE* file = fopen(filename, "w");

    // Write header
    char header[2] = "BM";
    fwrite(header, sizeof(char), 2, file);

    // Write width and height
    fwrite(&(image->width), sizeof(int), 1, file);
    fwrite(&(image->height), sizeof(int), 1, file);

    // Write data
    fwrite(image->data, sizeof(double), image->width * image->height, file);

    fclose(file);
}

// Image imageCreateFromData(int width, int height, int channels, double data[][width]) {
//     Matrix matrix = matrixCreate(height, width, data);

//     Image image = malloc(sizeof(struct image));
//     image->width = width;
//     image->height = height;
//     image->channels = channels;
//     image->data = matrix;

//     return image;
// }

Image imageCreateFromMatrix(Matrix matrix) {
    Image image = malloc(sizeof(struct image));
    image->width = matrixGetColumns(matrix);
    image->height = matrixGetRows(matrix);
    image->channels = 1;
    
    image->data = matrixCopy(matrix);

    return image;
}


// Getters

int imageGetWidth(Image image) {
    return image->width;
}

int imageGetHeight(Image image) {
    return image->height;
}

int imageGetChannels(Image image) {
    return image->channels;
}

Matrix imageGetData(Image image) {
    return image->data;
}