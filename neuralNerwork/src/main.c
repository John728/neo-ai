#include <stdio.h>
#include <stdlib.h>

#include "neuralNetwork.h"

int main(int argc, char **argv) {

	Image image = imageImport("./images/6/1.bmp");
	Layer imputLayer = createInputPlane(image);

	return EXIT_SUCCESS;

}