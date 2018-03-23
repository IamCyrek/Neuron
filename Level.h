#ifndef NEUTRONS_LEVEL_H
#define NEUTRONS_LEVEL_H


#include <vector>
#include "Neuron.h"

//класс "Уровень"
class Level {
    friend class NeuralNetwork;
    friend class Connection;

    //нейроны уровня
    vector<Neuron*> neurons;

public:

    Level() = delete;

    // конструктор с числом нейронов на уровне и функцией для уровня
    explicit Level(const ull &numberOfNeurons) {

        for (ull i = 0; i < numberOfNeurons; i++) {
            neurons.push_back(new Neuron());
        }

    }

//////////////////////////////////////////////////////////////////////
    //никто не знает для чего она
    /*void set() {
        for (unsigned long long i = 0; i < neurons.size(); i++) {
            neurons.at(i)->x_sum_y = i + 1;
        }
    }*/

    //вывод на экран суммы произведений весов на входные сигналы нейронов
    void get() const {
        for (ull i = 0; i < neurons.size(); i++) {
            cout << neurons.at(i)->x << ' ';
        }
        cout << endl;
    }

};


#endif //NEUTRONS_LEVEL_H