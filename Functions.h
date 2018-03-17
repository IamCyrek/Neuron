#ifndef NEURONS_FUNCTIONS_H
#define NEURONS_FUNCTIONS_H
//здесь функции для уровней


#include <math.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

//функция для получения рандомных чисел, внутри происходит какая-то магия
ld randomCplusplus11 (const double mi = 0.0, const double ma = 1.0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(mi, ma);

    return dis(gen);
}

ld function(const ld x) {
    return sin(x);
}

ld linearFunction(const ld sum) {
    return sum;
}

ld derivativeLinearFunction(const ld y) {
    return 1;
}

ld sygmoidFunction(const ld sum) {
    return 1. / (1. + exp(-sum));
}

ld derivativeSygmoidFunction(const ld y) {
    return y * (1 - y);
}

//ld (*const DEFAULT_FUNCTION)(const ld)  = linearFunction;


#endif //NEURONS_FUNCTIONS_H
