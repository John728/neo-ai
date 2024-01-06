#include "../../test_framework/src/test_framework.h"
#include "../../linearAlgebra/src/matrix.h"
#include "../src/imageProcessing.h"


TEST(testCreatingImageFromMatrix) {

    double data[2][2] = {{1,0},{0,1}};

    Matrix matrix = matrixCreate(2, 2, data);
    Image image = imageCreateFromMatrix(matrix);

    ASSERT(imageGetWidth(image) == 2);
    ASSERT(imageGetHeight(image) == 2);
    ASSERT(imageGetChannels(image) == 1);

    imageFree(image);
    matrixFree(matrix);
}

TEST(testSaveAndLoad) {
    
    double data[19][19] = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
    };


    Matrix matrix = matrixCreate(19, 19, data);
    Image image = imageCreateFromMatrix(matrix);

    imageSave(image, "test.png");
    Image loadedImage = imageImport("test.png");

    ASSERT(imageGetWidth(loadedImage) == 19);
    ASSERT(imageGetHeight(loadedImage) == 19);
    ASSERT(imageGetChannels(loadedImage) == 1);

    imageFree(image);
    imageFree(loadedImage);
    matrixFree(matrix);
}

TEST(testDataFromPath) {

    // create image

    double data[2][2] = {{1,0},{0,1}};

    Matrix matrix = matrixCreate(2, 2, data);
    Image image = imageCreateFromMatrix(matrix);
    imageSave(image, "test.png");

    matrixFree(matrix);
    imageFree(image);

    // preform test

    Matrix loadedMatrix = imageGetDataFromPath("test.png");

    ASSERT(matrixGetRows(loadedMatrix) == 2);
    ASSERT(matrixGetColumns(loadedMatrix) == 2);
    ASSERT(matrixGetElement(loadedMatrix, 0, 0) == 1);
    ASSERT(matrixGetElement(loadedMatrix, 0, 1) == 0);
    ASSERT(matrixGetElement(loadedMatrix, 1, 0) == 0);
    ASSERT(matrixGetElement(loadedMatrix, 1, 1) == 1);

    matrixFree(loadedMatrix);
}



// needed for test framework
int main() {
    run_tests();
    return 0;
}