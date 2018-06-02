#ifndef NEURONS_NEURON_H
#define NEURONS_NEURON_H

#include "Functions.h"

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