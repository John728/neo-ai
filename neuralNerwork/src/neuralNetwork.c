#include "./neuralNetwork.h"

typedef struct pattern *Pattern;
struct pattern {
    Matrix data;
    Pattern next;
};

struct link {
    Plane plane;
    Link next;
    Link last;
};

struct network {
    char *name;
    int numberOfLayers;
    Layer layers;
};

struct layer {
    char *name;
    int index;
    int numberOfPlanesInLayer;
    double inhibitor;
    Layer next;
    Plane first;
    Plane last;
};

struct plane {
    char *name;
    int index;
    int numPatterns;
    int height;
    int width;
    double inhibitor;
    Link links;
    Matrix output;
    Plane next;
    Pattern first;
    Pattern last;
};

Network createNetwork(char *name) {
    Network network = malloc(sizeof(struct network));
    network->name = name;
    network->numberOfLayers = 0;
    network->layers = NULL;
    return network;
}

void addLayerToNetwork(Network network, Layer layer) {
    if (network->numberOfLayers == 0) {
        network->layers = layer;
    } else {
        Layer lastLayer = network->layers;
        while (lastLayer->next != NULL) {
            lastLayer = lastLayer->next;
        }
        lastLayer->next = layer;
    }
    layer->index = network->numberOfLayers;
    network->numberOfLayers++;
}

Plane createPlane(int x, int y, char *name, Link links) {
    Plane plane = malloc(sizeof(struct plane));
    plane->name = name;
    plane->index = 0;
    plane->height = y;
    plane->width = x;
    plane->numPatterns = 0;
    plane->first = NULL;
    plane->last = NULL;
    plane->connectedTo = connectedTo;
    plane->links = links;
    plane->output = matrixCreateZeros(x, y);
    return plane;
}

Matrix simplePlaneOutput(Plane plane) {
    Link linkedPlane = plane->links;

    while(linkedPlane != NULL) {

        Plane plane = linkedPlane->plane;
        Matrix output = plane->output;


        linkedPlane = linkedPlane->next;
    }
}

Layer createLayer(char *name, double inhibitor, ) {
    Layer layer = malloc(sizeof(struct layer));
    layer->name = name;
    layer->index = 0;
    layer->numberOfPlanesInLayer = 0;
    layer->first = NULL;
    layer->last = NULL;
    layer->inhibitor = inhibitor;
    return layer;
}

void addPlaneToLayer(Layer layer, Plane plane) {
    if (layer->numberOfPlanesInLayer == 0) {
        layer->first = plane;
        layer->last = plane;
    } else {
        layer->last->next = plane;
        layer->last = plane;
    }
    plane->inhibitor = layer->inhibitor;
    plane->index = layer->numberOfPlanesInLayer;
    layer->numberOfPlanesInLayer++;
}

void addPatternToPlane(Plane plane, char *patternPath) {
    Matrix pattern = imageGetDataFromPath(patternPath);
    Pattern newPattern = malloc(sizeof(struct pattern));
    newPattern->data = pattern;
    newPattern->next = NULL;
    if (plane->numPatterns == 0) {
        plane->first = newPattern;
        plane->last = newPattern;
    } else {
        plane->last->next = newPattern;
        plane->last = newPattern;
    }
    plane->numPatterns++;
}

// Plane createInputPlane(Image image) {
//     int width = imageGetWidth(image);
//     int height = imageGetHeight(image);
//     int channels = imageGetChannels(image);
//     Matrix data = imageGetData(image);
//     Plane plane = malloc(sizeof(struct plane));
//     plane->name = "Input plane";
//     plane->index = 0;
//     plane->height = height;
//     plane->width = width;
//     plane->numPatterns = 1;
//     plane->first = NULL;
//     plane->last = NULL;
//     plane->output = data;
//     return plane;
// }

Link createLink(Plane plane) {
    Link link = malloc(sizeof(struct link));
    link->plane = plane;
    link->next = NULL;
    link->last = NULL;
    return link;
}

Link addPlaneToLink(Link link, Plane plane) {
    Link newLink = createLink(plane);
    if (link == NULL) {
        return newLink;
    } else {
        link->last->next = newLink;
        link->last = newLink;
        return link;
    }    
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

void printLayer(Layer layer, int printPlanes) {
    printf("-------------------------\n");
    printf("Layer: %s\n", layer->name);
    printf("-------------------------\n");
    printf("Index: %d\n", layer->index);
    printf("Number of planes: %d\n", layer->numberOfPlanesInLayer);
    printf("-------------------------\n");
    if (printPlanes) {
        Plane plane = layer->first;
        while (plane != NULL) {
            printPlane(plane);
            plane = plane->next;
        }
    }
}

void printNetwork(Network network, int printLayers, int printPlanes) {
    printf("-------------------------\n");
    printf("Network: %s\n", network->name);
    printf("-------------------------\n");
    printf("Number of layers: %d\n", network->numberOfLayers);
    printf("-------------------------\n");
    if (printLayers) {
        Layer layer = network->layers;
        while (layer != NULL) {
            printLayer(layer, printPlanes);
            layer = layer->next;
        }
    }
}