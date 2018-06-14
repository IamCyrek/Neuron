typedef unsigned long long ull;
typedef long double ld;

using namespace std;

#include <ctime>
#include "NeuralNetwork.h"
#include <iomanip>
#include "OLS.h"
//#include "windows.h"

const ull LEVEL_1 = 7;
const ull LEVEL_2 = 5;
const ull LEVEL_3 = 1;
const ld ALPHA_STEP = 0.1; //0.1 <0.3
const ld EXPECTED_ERROR = 0.001; //0.005

const ull SIZE_OF_LEARNING_ARR = 100;
const ull SIZE_OF_ETALON_ARR = 420;
const ull SIZE_OF_WHOLE_ARR = SIZE_OF_LEARNING_ARR + SIZE_OF_ETALON_ARR;

const ld DEVIATION = 0.00000001;

ld (*const NULL_FUNCTION)(const ld) = nullptr;
ld (*const NULL_DERIVATIVE_FUNCTION)(const ld) = nullptr;


//заполнение обучающей выборки
void splitting(vector<ld> &vectLearn, vector<ld> &vectEtalon,
               vector<ld> &vectStartLearn, const vector<ld> &x, const ull indexOfFirst = 0) {
    vectLearn.clear();
    vectEtalon.clear();
    vectStartLearn.clear();

    for (ull i = indexOfFirst; i < SIZE_OF_WHOLE_ARR; i++) {
        if (i < indexOfFirst + SIZE_OF_LEARNING_ARR) {
            vectLearn.push_back(x.at(i));
            if (indexOfFirst + SIZE_OF_LEARNING_ARR - i <= LEVEL_1) {
                vectStartLearn.push_back(x.at(i));
            }
        } else {
            vectEtalon.push_back(x.at(i));
        }
    }
}

void showPredictedAndEtalon(vector<ld> vectPredicted, vector<ld> vectDefective, vector<ld> vectEtalon) {
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

vector<ld> creatingVectWithCos(const vector<ld> &vectLearn, const vector<ld> &vectEtalon) {
    vector<ld> partOfCos = functionOfCos(SIZE_OF_WHOLE_ARR);
    vector<ld> vectWithCos = vectLearn;
    vectWithCos.insert(vectWithCos.end(),
                       vectEtalon.begin(),
                       vectEtalon.end());

    ull s1 = 120, s2 = s1 + SIZE_OF_LEARNING_ARR + 25;
    for (ull i = s1; i < s2; i++) {
        vectWithCos[i] = partOfCos[i];
    }
    ull s3 = s2 + SIZE_OF_LEARNING_ARR + 20, s4 = s3 + SIZE_OF_LEARNING_ARR + 25;
    for (ull i = s3; i < s4; i++) {
        vectWithCos[i] = partOfCos[i];
    }

    return vectWithCos;
}

NeuralNetwork* learningOfNetwork(const vector<ld> &vectLearn) {
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

    return networkPointer;
}

//главная функция
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    const vector<ld> x = functionOfEnon(SIZE_OF_WHOLE_ARR);
    vector<ld> vectLearn; //первая часть
    vector<ld> vectEtalon; //конец первой части
    vector<ld> vectStartLearn; //последняя часть
    vector<ld> vectWithCos; //последняя часть со вставками косинуса
    ull index = SIZE_OF_LEARNING_ARR;

    do {
        if (index >= SIZE_OF_WHOLE_ARR) {
            break;
        }

        if (index == SIZE_OF_LEARNING_ARR) {
            splitting(vectLearn, vectEtalon, vectStartLearn, x, 0);

            vectWithCos = creatingVectWithCos(vectLearn, vectEtalon);

        } else {
            splitting(vectLearn, vectEtalon, vectStartLearn, vectWithCos, index - SIZE_OF_LEARNING_ARR);
        }

        NeuralNetwork *networkPointer = learningOfNetwork(vectLearn);
        vector<ld> vectPredictedtest = networkPointer->predicting(vectStartLearn, vectEtalon.size());

        for (ull i = 0; i < 30; i++) {
            cout << i + index << ' ';
            cout << fabs(vectWithCos[i + index] - vectPredictedtest[i])
                 << ' ' << vectWithCos[i + index] << ' '
                 << vectPredictedtest[i] << endl;
        }

        for (ull i = 0; i < vectPredictedtest.size(); i++, index++) {
            if (fabs(vectPredictedtest[i] - vectWithCos[index]) > 0.1) {
                vector<ld> newVectPredictedtest;
                do {
                    if (index < vectWithCos.size()) {
                        vector<ld> newVectStartLearn;
                        for (ull j = index - LEVEL_1; j < index; j++) {
                            newVectStartLearn.push_back(vectWithCos[j]);
                        }
                        newVectPredictedtest = networkPointer->predicting(newVectStartLearn, 1);
                    } else {
                        index++;
                        break;
                    }
                } while(fabs(newVectPredictedtest[0] - vectWithCos[index++]) <= 0.1);


                cout << index - 1 << endl;
                break;
            }
        }

        index += SIZE_OF_LEARNING_ARR;
    } while(true);



    /*vector<ld> vectPredicted = networkPointer->predicting(vectStartLearn, vectEtalon.size());

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
    cout << "lambda = " << pointSet.getLambda() << endl;*/
//    Beep(523,5000);
    return 0;
}
