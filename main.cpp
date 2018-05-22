#include <iostream>
#include <random>
#include "NeuralNetwork.h"
#include "OLS.h"

const ull LEVEL_1 = 7;
const ull LEVEL_2 = 5;
const ull LEVEL_3 = 1;
//const ld FUNC_STEP = 0.1;
const ld ALPHA_STEP = 0.1; //0.1 <0.3
const ld EXPECTED_ERROR = 0.005; //0.005
const ull SIZE_OF_WHOLE_ARR = 500; //500
const ld PERCENT_OF_ETALON_ARR = 0.1;
const ull SIZE_OF_ETALON_ARR = (ull) round ((ld)SIZE_OF_WHOLE_ARR * PERCENT_OF_ETALON_ARR);
const ull SIZE_OF_LEARNING_ARR = SIZE_OF_WHOLE_ARR - SIZE_OF_ETALON_ARR;

const ld LEARNING[LEVEL_1]={};
ld (*const NULL_FUNCTION)(const ld) = NULL;
ld (*const NULL_DERIVATIVE_FUNCTION)(const ld) = NULL;

void showPredictedAndEtalon(vector<ld> vectPredicted, vector<ld> vectEtalon) {
//    cout<<"#Predicted and Etalon:#\n";
//    for (int i=0; i<vectPredicted.size(); i++) {
//        cout<<vectPredicted[i]<<"; "<<vectEtalon[i]<<";\n";
//    }
    cout<<"#Predicted:\n";
    for (int i=0; i<vectPredicted.size(); i++) {
        cout<<vectPredicted[i]<<"\n";
    }
    cout<<"#Etalon:\n";
    for (int i=0; i<vectEtalon.size(); i++) {
        cout<<vectEtalon[i]<<"\n";
    }
}

vector<ld> getWholeVector (ld begin, ld end, ull sizeOfWholeArr, ld (*func) (const ld)) {
    ld step = (end-begin)/((ld)sizeOfWholeArr-1);
    vector<ld> x;
    for (ull i=0; i<sizeOfWholeArr-1; i++) {
        x.push_back(func(i*step+begin));
    }
    x.push_back(func(end));
    return x;
}

//главная функция
int main() {

    /*vector<ld> x, y;
    functionOfEnon(100, x, y);

    for (ull i = 0; i < 100; i++) {
        cout << x.at(i) << " ";
    } cout << endl;

    for (ull i = 0; i < 100; i++) {
        cout << y.at(i) << " ";
    } cout << endl;

    return 0;*/
    srand(time(NULL));

    NeuralNetwork network({
          {LEVEL_1, NULL_FUNCTION, NULL_DERIVATIVE_FUNCTION},
          {LEVEL_2, sygmoidFunction, derivativeSygmoidFunction},
          {LEVEL_3, linearFunction, derivativeLinearFunction}
                          }, ALPHA_STEP, EXPECTED_ERROR);

    /*vector<ld> vectLearn;
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
    }*/

    vector<ld> vectLearn;
    vector<ld> vectEtalon;
    vector<ld> vectStartLearn;
//    vector<ld> x = getWholeVector(-0.5,10,SIZE_OF_WHOLE_ARR, cosinusFunction);
    vector<ld> x = functionOfEnon(SIZE_OF_WHOLE_ARR);

//    for (auto n: x) {
//        cout<<n<<endl;
//    }
//    return 0;

    //заполнение обучающей выборки
    for (ull i = 0; i < SIZE_OF_WHOLE_ARR; i++) {
        if (i<SIZE_OF_LEARNING_ARR) {
            vectLearn.push_back(x.at(i));
            if (SIZE_OF_LEARNING_ARR-i<=LEVEL_1) {
                vectStartLearn.push_back(x.at(i));
            }
        }
        else {
            vectEtalon.push_back(x.at(i));
        }
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

//    return 0;
    vector<ld> vectPredicted = network.predicting(vectStartLearn, vectEtalon.size());
    showPredictedAndEtalon(vectPredicted, vectEtalon);
    //network.show();

    cout<<"-------------------------------------"<<endl;
    vector<Point> vectErrs;
    for (int i=0; i<vectPredicted.size(); i++) {
        vectErrs.push_back(Point((ld)i, vectEtalon[i]-vectPredicted[i]));
    }
    PointSet pointSet(vectErrs);
    cout<<"lambda"<<pointSet.getLambda()<<endl;
    return 0;
}
