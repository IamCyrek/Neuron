#ifndef NEURONS_FUNCTIONS_H
#define NEURONS_FUNCTIONS_H
//здесь функции для уровней

#include <cmath>
#include <vector>

using namespace std;

//для ряда Энона
const ld A = 1.4;
const ld B = 0.3;
const ld X0 = 0.2;
const ld X1 = -0.5;


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


vector<ld> functionOfEnon(ull numberOfX) {
    vector<ld> x;
    if (numberOfX == 0)
        return x;
    else {
        x.push_back(X0);
        if (numberOfX == 1)
            return x;
        else {
            x.push_back(X1);
            for (ull i = 2; i < numberOfX; i++) {
                ld newX = 1. - A*x[i-1]*x[i-1]+B*x[i-2];
                x.push_back(newX);
            }
        }
    }
    return x;
}

vector<ld> functionOfCos(ull numberOfX) {
    ld first = 0., step = 0.1;
    vector<ld> ans;
    for (ull i = 0; i < numberOfX; i++, first += step) {
        ans.push_back(cos(first));
    }
    return ans;
}


#endif //NEURONS_FUNCTIONS_H
