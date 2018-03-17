#ifndef NEURONS_CONNECTION_H
#define NEURONS_CONNECTION_H


#include <vector>
#include <iostream>
#include "Level.h"

using std::vector;

//порог по умолчанию
const ld DEFAULT_T = 0;


class Connection {

    friend class NeuralNetwork;

    //веса между двумя уровнями
    vector<vector<ld>> w;

    //порог
    vector<ld> T;

    //предыдущий уровень
    Level* before;

    //следующий уровень
    Level* after;

    //шаг обучения
    ld alpha;

    //функция уровня
    ld (*function)(const ld sum);

    //производная функции
    ld (*derivativeFunction)(const ld sum);

    vector<ld> gamma;

public:

    Connection () = delete;

    //конструктор, рандомно задающий веса между двумя уровнями
    Connection (Level* before, Level* after, ld alpha,
                ld (*function)(const ld) = linearFunction,
                ld (*derivativeFunction)(const ld) = derivativeLinearFunction)
            : before(before), after(after),  alpha(alpha),
              function(function), derivativeFunction(derivativeFunction){
        for (ull j = 0; j < before->neurons.size(); j++) {
            vector<ld> vec1;

            for (ull k = 0; k < after->neurons.size(); k++) {
                vec1.push_back(randomCplusplus11());
            }

            w.push_back(vec1);
        }

        for (ull k = 0; k < after->neurons.size(); k++) {
            T.push_back(randomCplusplus11());
        }
    }

    void x_to_y() {
        for (ull i = 0; i < before->neurons.size(); i++) {
            for (ull j = 0; j < after->neurons.size(); j++) {
                after->neurons.at(j)->x += before->neurons.at(i)->x * w.at(i).at(j);
            }
        }

        for (ull i = 0; i < after->neurons.size(); i++) {
            after->neurons.at(i)->x -= T.at(i);
            after->neurons.at(i)->x = function(after->neurons.at(i)->x);
        }
    }

    ld backpropogationForLast(const vector<ld> &etalon) {
        ld sum = 0;
        for (ull i = 0; i < after->neurons.size(); i++) {
            before->gamma.push_back(after->neurons.at(i)->x - etalon.at(i));
            sum += pow(after->neurons.at(i)->x - etalon.at(i), 2);
        }

        return sum;
    }

    void backpropogationForHidden(const Connection *nextConnection) {
        for (ull i = 0; i < before->neurons.size(); i++) {
            ld sum = 0;
            for (ull j = 0; j < nextConnection->after->neurons.size(); j++) {
                sum += after->gamma.at(j)
                       * derivativeFunction(nextConnection->after->neurons.at(j)->x)
                       * w.at(i).at(j);
            }
            before->gamma.push_back(sum);
        }
    }

    void changeWAndT() {
        for (ull i = 0; i < before->neurons.size(); i++) {
            for (ull j = 0; j < after->neurons.size(); j++) {
                w.at(i).at(j) -= alpha
                                 * before->gamma.at(j)
                                 * derivativeFunction(after->neurons.at(j)->x)
                                 * before->neurons.at(i)->x;
            }
        }

        for (ull i = 0; i < after->neurons.size(); i++) {
            T.at(i) += alpha * before->gamma.at(i)
                       * derivativeFunction(after->neurons.at(i)->x);
        }
    }

    //показывает веса
    void show() const  {
        for (const auto &j : w) {
            for (const auto &k : j) {
                std::cout << std::setw(12) << std::left << k << ' ';
            }
            std::cout << std::endl;
        }
    }

};


#endif //NEURONS_CONNECTION_H
