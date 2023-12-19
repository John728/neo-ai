#include <stdio.h>
#include <stdlib.h>
#include "../../linearAlgebra/src/matrix.h"
#include "../../imageProcessing/src/imageProcessing.h"

typedef struct network *Network;
typedef struct module *Module;
typedef struct layer *Layer;
typedef struct plane *Plane;

Plane createPlane(int x, int y, int index, char *name, Matrix pattern);
Layer createLayer(char *name, int index, int numPlanes, Matrix (*connectionFunction)(int layer, int plane, int x, int y), double inhibitor);
Network createNetwork(int numLayers, char *name);
Plane createInputPlane(Image image);

Layer createSimpleLayer(int numPlanes, char *name, Matrix (*connectionFunction)(int layer, int plane, int x, int y), double inhibitor);
Layer createComplexLayer(int numPlanes, char *name, Matrix (*connectionFunction)(int layer, int plane, int x, int y));

Matrix simpleConnectionFunction(int layer, int plane, int x, int y);
Matrix complexConnectionFunction(int layer, int plane, int x, int y);


Layer getLayer(Network network);
Plane getPlaneFromNetwork(Network network, int layerIndex, int planeIndex);
Plane getPlaneFromLayer(Layer layer, int planeIndex);

Matrix getConnections(int layerIndex, int planeIndex, int x, int y);


void printPlane(Plane plane);