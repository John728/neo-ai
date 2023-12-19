#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linearAlgebra/src/matrix.h"
#include "imageProcessing/src/imageProcessing.h"
#include "neuralNerwork/src/neuralNetwork.h"

int main(int argc, char *argv[]) {

    Image image = imageImport("./images/6/1.bmp");
    Plane input = createInputPlane(image);

    printPlane(input);

    return EXIT_SUCCESS;
}
