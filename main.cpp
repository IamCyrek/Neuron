#include <iostream>
#include <random>
#include "NeuralNetwork.h"

const ull LEVEL_1 = 7;
const ull LEVEL_2 = 4;
const ull LEVEL_3 = 1;
const ld FUNC_STEP = 0.1;
const ld ALPHA_STEP = 0.1;
const ld EXPECTED_ERROR = 0.0001;
const ull SIZE_OF_WHOLE_ARR = 40;
const ld PERCENT_OF_ETALON_ARR = 0.2;
const ull SIZE_OF_ETALON_ARR = (ull) round ((ld)SIZE_OF_WHOLE_ARR * PERCENT_OF_ETALON_ARR);
const ull SIZE_OF_LEARNING_ARR = SIZE_OF_WHOLE_ARR - SIZE_OF_ETALON_ARR;

const ld LEARNING[LEVEL_1]={};
ld (*const NULL_FUNCTION)(const ld) = NULL;
ld (*const NULL_DERIVATIVE_FUNCTION)(const ld) = NULL;

void showPredictedAndEtalon(vector<ld> vectPredicted, vector<ld> vectEtalon) {
    cout<<"#Predicted and Etalon:#\n";
    for (int i=0; i<vectPredicted.size(); i++) {
        cout<<vectPredicted[i]<<"; "<<vectEtalon[i]<<";\n";
    }
}

//главная функция
int main() {
    srand(time(NULL));

    NeuralNetwork network({
          {LEVEL_1, NULL_FUNCTION, NULL_DERIVATIVE_FUNCTION},
          {LEVEL_2, sygmoidFunction, derivativeSygmoidFunction},
          {LEVEL_3, linearFunction, derivativeLinearFunction}
                          }, ALPHA_STEP, EXPECTED_ERROR);

    vector<ld> vectLearn;
    vector<ld> vectEtalon;
    vector<ld> vectStartLearn;
    ld last = 0;

	//заполнение обучающей выборки
    for (ull i = 0; i < SIZE_OF_WHOLE_ARR; i++) {
        if (i<SIZE_OF_LEARNING_ARR) {
            vectLearn.push_back(function(last));
            if (SIZE_OF_LEARNING_ARR-i<=LEVEL_1) {
                vectStartLearn.push_back(function(last));
            }
        }
        else {
            vectEtalon.push_back(function(last));
        }
        last += FUNC_STEP;
    }

    try {
        network.learning(vectLearn);
    } catch (int e) {
        if (e == 1) {
            cout << "Incorrect size of learning selection!" << endl;
        } else {
            cout << e << endl;
        }
    }

    vector<ld> vectPredicted = network.predicting(vectStartLearn, vectEtalon.size());
    showPredictedAndEtalon(vectPredicted, vectEtalon);
    //network.show();

    return 0;
}
