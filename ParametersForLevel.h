#ifndef NEURONS_PARAMETERSFORLEVEL_H
#define NEURONS_PARAMETERSFORLEVEL_H


#include "Functions.h"

//определение типа "указатель на функцию" для передачи функции и ее производной
typedef ld (*funct)(const ld);
typedef ld (*derivFunct)(const ld);

// класс "Параметры для уровня"
class ParametersForLevel {

	//число нейронов уровня
    unsigned long long numberOfNeurons;

	//функция соединения двух слоев
    ld (*function)(const ld);

	//производная функции соединения двух слоев
    ld (*derivativeFunction)(const ld);

public:

	//конструктор с заданием значений
	// для нейронной сети в качестве первой функции передается Null, т.к. функций на 1 меньше, чем уровней
    ParametersForLevel(unsigned long long int numberOfNeurons,
                       ld (*function)(const ld),
                       ld (*derivativeFunction)(const ld))
            : numberOfNeurons(numberOfNeurons),
              function(function),
              derivativeFunction(derivativeFunction) {}

	//геттеры
    unsigned long long getNumberOfNeurons() const {
        return numberOfNeurons;
    }

    funct getFunction() const {
        return function;
    }

    derivFunct getDerivativeFunction() const {
        return derivativeFunction;
    }
};

#endif //NEURONS_PARAMETERSFORLEVEL_H
