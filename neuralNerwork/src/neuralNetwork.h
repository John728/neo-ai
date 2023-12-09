#include <stdio.h>
#include <stdlib.h>
#include "../../linearAlgebra/src/matrix.h"

typedef struct network *Network;
typedef struct module *Module;
typedef struct layer *Layer;
typedef struct plane *Plane;
typedef struct cell *Cell;

struct network {
    char *name;
    int numberOfLayers;
    Layer layers[];
};

struct layer {
    char *name;
    int index;
    int numberOfPlanesInLayer;
    Plane planes[];
    Matrix (*connectionFunction)(int layer, int plane, int x, int y)
};

struct plane {
    char *name;
    int index;
    Cell* cellArray[];
};

struct cell {
    char *name;
    int x;
    int y;
    Matrix connections;
};


Plane createPlane(int x, int y, int index, char *name);
Layer createLayer(int numPlanes, char *name);
Network createNetwork(int numLayers, char *name);
Plane createInputPlane(int x, int y, int index, Matrix input);
Layer createSimpleLayer(int numPlanes, char *name, Matrix (*connectionFunction)(int layer, int plane, int x, int y));

void defineLayer(Network network, int Layer);

Layer getLayer(Network network);
Plane getPlaneFromNetwork(Network network, int layerIndex, int planeIndex);
Plane getPlaneFromLayer(Layer layer, int planeIndex);

Matrix getConnections(int layerIndex, int planeIndex, int x, int y);