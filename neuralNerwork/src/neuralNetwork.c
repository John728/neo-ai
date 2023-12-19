#include "./neuralNetwork.h"

struct network {
    char *name;
    int numberOfLayers;
    Layer layers[];
};

struct layer {
    char *name;
    int index;
    int numberOfPlanesInLayer;
    Plane *planes;
    Matrix (*connectionFunction)(int layer, int plane, int x, int y);
    double inhibitor;
};

struct plane {
    char *name;
    int index;
    Matrix pattern;
    int height;
    int width;
    Matrix output;
};

Plane createPlane(int x, int y, int index, char *name, Matrix pattern) {
    Plane plane = malloc(sizeof(struct plane));
    plane->name = name;
    plane->index = index;
    plane->pattern = pattern;
    plane->height = y;
    plane->width = x;

    plane->output = matrixCreateZeros(x, y);

    return plane;
}

Layer createLayer(char *name, int index, int numPlanes, Matrix (*connectionFunction)(int layer, int plane, int x, int y), double inhibitor) {
    Layer layer = malloc(sizeof(struct layer));
    layer->name = name;
    layer->index = index;
    layer->numberOfPlanesInLayer = 0;
    layer->planes = malloc(sizeof(Plane) * numPlanes);
    layer->connectionFunction = connectionFunction;
    layer->inhibitor = inhibitor;
    return layer;
}

void addPlaneToLayer(Layer layer, Plane plane) {
    layer->planes[layer->numberOfPlanesInLayer] = plane;
    layer->numberOfPlanesInLayer++;
}
Plane createInputPlane(Image image) {
    Plane plane = malloc(sizeof(struct plane));
    plane->name = "Input image plane";
    plane->index = 0;
    plane->height = imageGetHeight(image);
    plane->width = imageGetWidth(image);
    plane->output = imageGetData(image);
    return plane;
}

void printPlane(Plane plane) {
    printf("-------------------------\n");
    printf("Plane: %s\n", plane->name);
    printf("-------------------------\n");
    printf("Index: %d\n", plane->index);
    printf("Height: %d\n", plane->height);
    printf("Width: %d\n", plane->width);
    printf("-------------------------\n");
}