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
    const Level* before;

    //следующий уровень
    Level* after;

public:

    Connection () = delete;

    //конструктор, рандомно задающий веса между двумя уровнями
    Connection (const Level* before, Level* after)
            : before(before), after(after) {
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
