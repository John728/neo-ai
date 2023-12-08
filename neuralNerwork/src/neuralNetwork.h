#include <stdio.h>
#include <stdlib.h>
#include "../../linearAlgebra/src/matrix.h"

typedef struct network *Network;
typedef struct module *Module;
typedef struct layer *Layer;
typedef struct plane *Plane;

struct network {
    char *name;
    int numberOfLayers;
    Layer layers[];
    Matrix (*connectionFunction)(int layer, int plane, int x, int y)
};

struct layer {
    char *name;
    int index;
    int numberOfPlanesInLayer;
    Plane planes[];
};

struct plane {
    char *name;
    int index;
    Matrix cells;
};


Plane createPlane(int x, int y, int index, char *name);
Layer createLayer(int numPlanes, char *name);
Network createNetwork(int numLayers, char *name);

Plane createInputPlane(int x, int y, int index, Matrix input);

void defineLayer(Network network, int Layer);

Layer getLayer(Network network);
Plane getPlaneFromNetwork(Network network, int layerIndex, int planeIndex);
Plane getPlaneFromLayer(Layer layer, int planeIndex);

Matrix getConnections(int layerIndex, int planeIndex, int x, int y);