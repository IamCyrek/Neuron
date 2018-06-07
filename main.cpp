typedef unsigned long long ull;
typedef long double ld;

using namespace std;

#include <ctime>
#include "NeuralNetwork.h"
#include "OLS.h"
//#include "windows.h"

const ull LEVEL_1 = 7;
const ull LEVEL_2 = 5;
const ull LEVEL_3 = 1;
//const ld FUNC_STEP = 0.1;
const ld ALPHA_STEP = 0.1; //0.1 <0.3
const ld EXPECTED_ERROR = 0.001; //0.005

//const ld PERCENT_OF_ETALON_ARR = 0.5;
//const ull SIZE_OF_ETALON_ARR = (ull) round ((ld)SIZE_OF_WHOLE_ARR * PERCENT_OF_ETALON_ARR);
//const ull SIZE_OF_LEARNING_ARR = SIZE_OF_WHOLE_ARR - SIZE_OF_ETALON_ARR;
const ull SIZE_OF_LEARNING_ARR = 100;
const ull SIZE_OF_ETALON_ARR = 100;
const ull SIZE_OF_WHOLE_ARR = SIZE_OF_ETALON_ARR + SIZE_OF_LEARNING_ARR; //500

const ld DEVIATION = 0.00000001;

//const ld LEARNING[LEVEL_1]={};
ld (*const NULL_FUNCTION)(const ld) = nullptr;
ld (*const NULL_DERIVATIVE_FUNCTION)(const ld) = nullptr;

void showPredictedAndEtalon(vector<ld> vectPredicted, vector<ld> vectDefective, vector<ld> vectEtalon) {
//    cout << "#Predicted and Etalon:#" << endl;
//    for (int i = 0; i < vectPredicted.size(); i++) {
//        cout << vectPredicted[i] << "; " << vectEtalon[i] << ";" << endl;
//    }
    cout.precision(14);
    cout << "#Predicted:" << endl;
    for (ld i : vectPredicted) {
        cout << i << endl;
    }
    cout << "#Defective:" << endl;
    for (ld i : vectDefective) {
        cout << i << endl;
    }
    cout << "#Etalon:" << endl;
    for (ld i : vectEtalon) {
        cout << i << endl;
    }
}

vector<ld> creatingVectOfEtalonsWithCos(vector<ld> &vectEtalon) {
    vector<ld> partOfCos = functionOfCos(SIZE_OF_ETALON_ARR);
    vector<ld> vectEtalonWithCos = vectEtalon;

    /*for (ull i = 2; i < 6; i++) {
        vectEtalonWithCos[i] = partOfCos[i];
    }*/
    /*for (ull i = 6; i < 15; i++) {
        vectEtalonWithCos[i] = partOfCos[i];
    }
    for (ull i = 17; i < 25; i++) {
        vectEtalonWithCos[i] = partOfCos[i];
    }
    for (ull i = 35; i < 40; i++) {
        vectEtalonWithCos[i] = partOfCos[i];
    }*/

    cout << endl << "Cos";
    for (const auto& i : partOfCos) {
        cout << i << ' ';
    } cout << endl;
    for (const auto& i : vectEtalon) {
        cout << i << ' ';
    } cout << endl;
    for (const auto& i : vectEtalonWithCos) {
        cout << i << ' ';
    } cout << endl << endl;

    return vectEtalonWithCos;
}

void segmentation(const vector<ld> &vectEtalon, const vector<ld> &vectEtalonWithCos) {
    bool checkOfStart = false;
    ull whereStart = -1;
    for (ull i = 0; i < vectEtalon.size(); i++) {
        if (fabs(vectEtalon[i] - vectEtalonWithCos[i]) > 0.1) {
            if (!checkOfStart) {
                checkOfStart = true;
                whereStart = i;
            }
        } else if (checkOfStart) {
            checkOfStart = false;
            cout << whereStart << ' ' << i << endl;
            whereStart = -1;
        }
    }
    if (checkOfStart) {
        cout << whereStart << ' ' << vectEtalon.size() << endl;
    }
}

//главная функция
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<ld> vectLearn;
    vector<ld> vectEtalon;
    vector<ld> vectStartLearn;
    vector<ld> x = functionOfEnon(SIZE_OF_WHOLE_ARR);

    //заполнение обучающей выборки
    for (ull i = 0; i < SIZE_OF_WHOLE_ARR; i++) {
        if (i < SIZE_OF_LEARNING_ARR) {
            vectLearn.push_back(x.at(i));
            if (SIZE_OF_LEARNING_ARR - i <= LEVEL_1) {
                vectStartLearn.push_back(x.at(i));
            }
        } else {
            vectEtalon.push_back(x.at(i));
        }
    }

    NeuralNetwork *networkPointer = nullptr;

    try {
        do {
            cout << "Trying..." << endl;
            delete networkPointer;
            networkPointer = new NeuralNetwork({
                                                       {LEVEL_1, NULL_FUNCTION,   NULL_DERIVATIVE_FUNCTION},
                                                       {LEVEL_2, sygmoidFunction, derivativeSygmoidFunction},
                                                       {LEVEL_3, linearFunction,  derivativeLinearFunction}
                                               }, ALPHA_STEP, EXPECTED_ERROR);
        } while (!(networkPointer->learning(vectLearn)));
    } catch (int e) {
        if (e == 1) {
            cout << "Incorrect size of learning selection!" << endl;
        } else {
            cout << e << endl;
        }
    }




    vector<ld> vectEtalonWithCos = creatingVectOfEtalonsWithCos(vectEtalon);
    vector<ld> vectPredictedtest = networkPointer->predicting(vectStartLearn, vectEtalon.size());
    segmentation(vectPredictedtest, vectEtalonWithCos);




    vector<ld> vectPredicted = networkPointer->predicting(vectStartLearn, vectEtalon.size());

    cout << "-------------------------------------" << endl;

    vectStartLearn[vectStartLearn.size() - 1] += DEVIATION;

    vector<ld> vectDefective = networkPointer->predicting(vectStartLearn, vectEtalon.size());
    showPredictedAndEtalon(vectPredicted, vectDefective, vectEtalon);

    vector<Point> vectErrs;
    for (int i = 0; abs(vectDefective[i] - vectPredicted[i]) < 1. && i < vectPredicted.size(); i++) {
        vectErrs.emplace_back((ld)i, log(abs(vectDefective[i] - vectPredicted[i])));
    }
    PointSet pointSet(vectErrs);
    cout << "vector size = " << pointSet.getSize() << endl;
    cout << "lambda = " << pointSet.getLambda() << endl;
//    Beep(523,5000);
    return 0;
}
