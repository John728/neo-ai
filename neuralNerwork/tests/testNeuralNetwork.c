#include "../../test_framework/src/test_framework.h"
#include "../src/neuralNetwork.h"

TEST(testCreateNetwork) {

    Network network = createNetwork(3, "testNetwork");

    ASSERT(network->numberOfLayers == 3);
    ASSERT(strcmp(network->name, "testNetwork") == 0);

    networkFree(network);
}

// needed for test framework
int main() {
    run_tests();
    return 0;
}