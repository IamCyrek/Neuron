#ifndef NEURONS_FUNCTIONS_H
#define NEURONS_FUNCTIONS_H
//здесь функции для уровней


typedef unsigned long long ull;
typedef long double ld;

//функция для получения рандомных чисел, внутри происходит какая-то магия
ld randomCplusplus11 (const double mi = 0.0, const double ma = 1.0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(mi, ma);

    return dis(gen);
}

long double defaulFunction(const ld sum) {
    return sum;
}


#endif //NEURONS_FUNCTIONS_H
