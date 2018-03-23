#include <iostream>
#include <string>
#include <random>
#include "NeuralNetwork.h"

const unsigned long long LEVEL_1 = 7;
const unsigned long long LEVEL_2 = 4;
const unsigned long long LEVEL_3 = 1;
const ld LEARNING[LEVEL_1]={};
ld (*const NULL_FUNCTION)(const ld) = NULL;
ld (*const NULL_DERIVATIVE_FUNCTION)(const ld) = NULL;

//главная функция
int main() {
    srand(time(NULL));

    NeuralNetwork network({
          {LEVEL_1, NULL_FUNCTION, NULL_DERIVATIVE_FUNCTION},
          {LEVEL_2, sygmoidFunction, derivativeSygmoidFunction},
          {LEVEL_3, linearFunction, derivativeLinearFunction}
                          }, 0.07, 0.001);

    vector<ld> vect;
    ld last = 0.1;

	//заполнение обучающей выборки
    for (int i = 0; i < 30; i++) {
        vect.push_back(function(last));
        last += 0.1;
    }

    try {
        network.learning(vect);
    } catch (int e) {
        if (e == 1) {
            cout << "Incorrent size of learning selection!" << endl;
        } else {
            cout << e << endl;
        }
    }

    network.show();

    return 0;
}
