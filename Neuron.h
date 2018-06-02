#ifndef NEURONS_NEURON_H
#define NEURONS_NEURON_H

#include <cstdlib> //for random

//функция для получения рандомных чисел
ld randomCplusplus11 (const double mi = -0.5, const double ma = 1.5) {
    return ld(rand() * (ma - mi) / RAND_MAX + mi);
    /*std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(mi, ma);

    return dis(gen);*/
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
    Neuron() : x(randomCplusplus11()) {}

};


#endif //NEURONS_NEURON_H