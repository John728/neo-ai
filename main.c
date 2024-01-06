#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linearAlgebra/src/matrix.h"
#include "imageProcessing/src/imageProcessing.h"
#include "neuralNerwork/src/neuralNetwork.h"

Layer createSimpleLayer1(Network network) {
    Layer layer = createLayer("S1", 1.7);

    int numPlanes = 12;

    for (int i = 0; i < numPlanes; i++) {
        
        char *name = malloc(sizeof(char) * 10);
        sprintf(name, "Plane %d", i + 1);
        char *path = malloc(sizeof(char) * 30);
        sprintf(path, "./images/patterns/a1/%d.png", i + 1);

        Plane plane = createPlane(3, 3, name);
        addPatternToPlane(plane, imageGetDataFromPath(path));
        addPlaneToLayer(layer, plane);
    }


    return layer;
}

int main(int argc, char *argv[]) {

    // Image image = imageImport("./images/6/1.bmp");
    // Plane input = createInputPlane(image);




    // printLayer(layer1, true);

    Network network = createNetwork("Test network");


    Layer layer1 = createSimpleLayer1(network);
    addLayerToNetwork(network, layer1);

    printNetwork(network, true, true);

    return EXIT_SUCCESS;
}

