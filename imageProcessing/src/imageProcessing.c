#include "imageProcessing.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image/stb_image_write.h"

struct image {
    int width;
    int height;
    int channels;
    Matrix data;
    size_t size;
};  

/**
 * For now, format is always Monochrome Bitmap
*/
Image imageImport(char* filename) {
    int width, height, channels;
    uint8_t* data = stbi_load(filename, &width, &height, &channels, 1);

    // Allocate a single block of memory for a 2D array
    double (*doubleData)[width] = malloc(height * sizeof(*doubleData));

    // Copy and convert uint8_t data to double
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            doubleData[i][j] = (double)data[i * width + j];
        }
    }

    Matrix matrix = matrixCreate(height, width, doubleData);

    Image image = malloc(sizeof(struct image));
    image->width = width;
    image->height = height;
    image->channels = channels;
    image->data = matrix;
    image->size = width * height * channels;

    // Free the doubleData array after use
    free(doubleData);

    return image;
}

void imageFree(Image image) {
    matrixFree(image->data);
    free(image);
}

void imageSave(Image image, char* filename) {
    // Allocate a single block of memory for a 2D array
    uint8_t (*uint8Data)[image->width] = malloc(image->height * sizeof(*uint8Data));

    // Copy and convert double data to uint8_t
    Matrix matrix = image->data;
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            uint8Data[i][j] = (uint8_t)matrixGetElement(matrix, i, j);
        }
    }

    stbi_write_png(filename, image->width, image->height, image->channels, uint8Data, image->width * image->channels);

    // Free the uint8Data array after use
    free(uint8Data);
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