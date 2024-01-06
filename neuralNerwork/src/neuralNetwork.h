#include <stdio.h>
#include <stdlib.h>
#include "../../linearAlgebra/src/matrix.h"
#include "../../imageProcessing/src/imageProcessing.h"

typedef struct network *Network;
typedef struct module *Module;
typedef struct layer *Layer;
typedef struct plane *Plane;
typedef struct link *Link;


Plane createPlane(int x, int y, char *name, Link links);
Layer createLayer(char *name, double inhibitor);
Network createNetwork(char *name);
Plane createInputPlane(Image image);
Link createLink(Plane plane);

Layer createSimpleLayer(int numPlanes, char *name, Matrix (*connectionFunction)(int layer, int plane, int x, int y), double inhibitor);
Layer createComplexLayer(int numPlanes, char *name, Matrix (*connectionFunction)(int layer, int plane, int x, int y));

void addLayerToNetwork(Network network, Layer layer);
void addPlaneToLayer(Layer layer, Plane plane);
void addPatternToPlane(Plane plane, char *patternPath);
Link addPlaneToLink(Link link, Plane plane)

Matrix simpleConnectionFunction(int layer, int plane, int x, int y);
Matrix complexConnectionFunction(int layer, int plane, int x, int y);


Layer getLayer(Network network);
Plane getPlaneFromNetwork(Network network, int layerIndex, int planeIndex);
Plane getPlaneFromLayer(Layer layer, int planeIndex);

Matrix getConnections(int layerIndex, int planeIndex, int x, int y);


void printPlane(Plane plane);
void printLayer(Layer layer, int printPlanes);
void printNetwork(Network network, int printLayers, int printPlanes);