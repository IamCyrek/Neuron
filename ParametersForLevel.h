#ifndef NEURONS_PARAMETERSFORLEVEL_H
#define NEURONS_PARAMETERSFORLEVEL_H


#include "Functions.h"

typedef ld (*funct)(const ld);
typedef ld (*derivFunct)(const ld);

class ParametersForLevel {
    unsigned long long numberOfNeurons;
    ld (*function)(const ld);
    ld (*derivativeFunction)(const ld);

public:

    ParametersForLevel(unsigned long long int numberOfNeurons,
                       ld (*function)(const ld),
                       ld (*derivativeFunction)(const ld))
            : numberOfNeurons(numberOfNeurons),
              function(function),
              derivativeFunction(derivativeFunction) {}

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
