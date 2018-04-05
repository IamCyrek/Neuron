#ifndef NEURONS_FUNCTIONS_H
#define NEURONS_FUNCTIONS_H
//здесь функции для уровней

#include <cmath>
#include <cstdlib>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

//для ряда Энона
const ld A = 1.4;
const ld B = 0.3;
const ld X0 = 0.;
const ld Y0 = 0.;

//функция для получения рандомных чисел
ld randomCplusplus11 (const double mi = -0.5, const double ma = 1.5) {
    return ld(rand() * (ma - mi) / RAND_MAX + mi);
    /*std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(mi, ma);

    return dis(gen);*/
}

//функция для предсказания
ld function(const ld x) {
    return 0.3 * cos(0.3 * x) + 0.7 * sin(0.3 * x);
}

//линейная функция
ld linearFunction(const ld sum) {
    return sum;
}

//производная линейной функции
ld derivativeLinearFunction(const ld y) {
    return 1;
}

//сигмоидная функция
ld sygmoidFunction(const ld sum) {
    return 1. / (1. + exp(-sum));
}

//производная сигмоидной функции
ld derivativeSygmoidFunction(const ld y) {
    return y * (1 - y);
}


void functionOfEnon(ull numberOfX, vector<ld> &x, vector<ld> &y) {
    if (x.size() != 0 || y.size()) {
        cout << "ATTENTTION!!!" << endl;
        x.clear();
        y.clear();
    }

    x.push_back(X0);
    y.push_back(Y0);
    for (ull i = 1; i < numberOfX; i++) {
        x.push_back(1 - A * pow(x.at(i - 1), 2) + y.at(i - 1));
        y.push_back(B * x.at(i - 1));
    }
}

//ld (*const DEFAULT_FUNCTION)(const ld)  = linearFunction;


#endif //NEURONS_FUNCTIONS_H
