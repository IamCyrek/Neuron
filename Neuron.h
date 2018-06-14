#ifndef NEURONS_NEURON_H
#define NEURONS_NEURON_H

#include <cstdlib> //for random

//функция для получения рандомных чисел
ld randomCplusplus(const double mi = -0.5, const double ma = 1.5) {
    return ld(rand() * (ma - mi) / RAND_MAX + mi);
}

//класс "Нейрон"
class Neuron {

    friend class Level;
    friend class Connection;
    friend class NeuralNetwork;

    //сначала входной сигнал, потом сумма произведений входных на веса
    ld x;

public:

	//конструктор с заданием х
    Neuron() : x(randomCplusplus()) {}

};


#endif //NEURONS_NEURON_H