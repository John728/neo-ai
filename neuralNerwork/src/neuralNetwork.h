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
    void *firstLayer;
};

struct module {
    char *name;
};

struct layer {
    char *name;
    void *nextLayer;
    Plane *firstPlane;
};

struct plane {
    char *name;
    Plane *nextPlane;
    Matrix output;
};