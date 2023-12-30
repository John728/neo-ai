#include <stdio.h>
#include <stdlib.h>
#include "../../linearAlgebra/src/matrix.h"
#include "imageProcessing.h"

int main(void) {
    
    Image image = imageImport("../../images/6/1.png");
    Matrix matrix = imageGetData(image);
    matrixPrint(matrix);
    
    Image image2 = imageCreateFromMatrix(matrix);
    imageSave(image2, "1.png");
}