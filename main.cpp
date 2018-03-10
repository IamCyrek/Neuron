#include <iostream>
#include <random>
#include "NeuralNetwork.h"

using std::make_pair;

const unsigned long long LEVEL_1 = 10;
const unsigned long long LEVEL_2 = 7;
const unsigned long long LEVEL_3 = 1;

int main() {
    NeuralNetwork network({
          {make_pair(LEVEL_1, defaulFunction)},
          {make_pair(LEVEL_2, defaulFunction)},
          {make_pair(LEVEL_3, defaulFunction)}
                          }, 0.1, 0.1);

    network.learning({1, 2, 3, 4, 5, 5, 4, 3, 2, 1});

    network.show();

    return 0;
}
