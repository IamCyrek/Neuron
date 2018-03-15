#include <iostream>
#include <random>
#include "NeuralNetwork.h"

using std::make_pair;

const unsigned long long LEVEL_1 = 10;
const unsigned long long LEVEL_2 = 4;
const unsigned long long LEVEL_3 = 1;
ld (*const NULL_FUNCTION)(const ld) = NULL;
ld (*const NULL_DERIVATIVE_FUNCTION)(const ld) = NULL;


int main() {
    NeuralNetwork network({
          {LEVEL_1, NULL_FUNCTION, NULL_DERIVATIVE_FUNCTION},
          {LEVEL_2, sygmoidFunction, derivativeSygmoidFunction},
          {LEVEL_3, linearFunction, derivativeLinearFunction}
                          }, 0.1, 0.1);

    network.learning({1, 2, 3, 2, 1, 10, 11, 12});

    //network.show();

    return 0;
}
