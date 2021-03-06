#ifndef NEURONS_CONNECTION_H
#define NEURONS_CONNECTION_H

#include "Level.h"
#include "Functions.h"

//класс "Соединение"
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

	//ошибки для выходного и скрытых слоев (backpropogation)
    vector<ld> gamma;

    //шаг обучения
    ld alpha;

    //функция уровня
    ld (*function)(const ld sum);

    //производная функции
    ld (*derivativeFunction)(const ld sum);

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
                vec1.push_back(randomCplusplus());
            }

            w.push_back(vec1);
        }

        gamma.resize(after->neurons.size());

        for (ull k = 0; k < after->neurons.size(); k++) {
            T.push_back(randomCplusplus());
        }
    }

	//преобразует значения из предыдущего слоя в следующий
    void x_to_y() {
        for (ull j = 0; j < after->neurons.size(); j++) {
			after->neurons.at(j)->x = 0;
            for (ull i = 0; i < before->neurons.size(); i++) {
                after->neurons.at(j)->x += before->neurons.at(i)->x * w.at(i).at(j);
            }
        }

        for (ull i = 0; i < after->neurons.size(); i++) {
            after->neurons.at(i)->x -= T.at(i);
            after->neurons.at(i)->x = function(after->neurons.at(i)->x);
        }
    }

	//находит гаммы для последнего слоя
    ld backpropogationForLast(const vector<ld> &etalon) {
        ld sum = 0;
        for (ull i = 0; i < after->neurons.size(); i++) {
            gamma.at(i) = after->neurons.at(i)->x - etalon.at(i);
            sum += pow(after->neurons.at(i)->x - etalon.at(i), 2);
        }
        ld xx = after->neurons.at(0)->x;

        return sum;
    }

	//находит гаммы для скрытых слоев
    void backpropogationForHidden(const Connection *nextConnection) {
        for (ull i = 0; i < nextConnection->before->neurons.size(); i++) {
            ld sum = 0;
            for (ull j = 0; j < nextConnection->after->neurons.size(); j++) {
                sum += nextConnection->gamma.at(j)
                       * nextConnection->derivativeFunction(nextConnection->after->neurons.at(j)->x)
                       * nextConnection->w.at(i).at(j);
            }
            gamma.at(i) = sum;
        }
    }

    void changeWAndT() {
        for (ull i = 0; i < before->neurons.size(); i++) {
            for (ull j = 0; j < after->neurons.size(); j++) {
                w.at(i).at(j) -= alpha
                                 * gamma.at(j)
                                 * derivativeFunction(after->neurons.at(j)->x)
                                 * before->neurons.at(i)->x;
            }
        }

        for (ull i = 0; i < after->neurons.size(); i++) {
            T.at(i) += alpha * gamma.at(i)
                       * derivativeFunction(after->neurons.at(i)->x);
        }
    }

};


#endif //NEURONS_CONNECTION_H
