#ifndef NEUTRONS_LEVEL_H
#define NEUTRONS_LEVEL_H

#include "Neuron.h"
#include <vector>
#include <iostream>

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

};


#endif //NEUTRONS_LEVEL_H