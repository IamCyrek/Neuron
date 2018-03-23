#ifndef NEURONS_FUNCTIONS_H
#define NEURONS_FUNCTIONS_H
//здесь функции для уровней

#include <cmath>
#include <cstdlib>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

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

//ld (*const DEFAULT_FUNCTION)(const ld)  = linearFunction;


#endif //NEURONS_FUNCTIONS_H
