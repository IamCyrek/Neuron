#ifndef NEURONS_NEURALNETWORK_H
#define NEURONS_NEURALNETWORK_H

#include "Connection.h"
#include "ParametersForLevel.h"

static const ull ITERATIONS = 100000;
static const ull HOW_OFTEN_SHOW_ERROR = 500;

class NeuralNetwork {

    //вектор слоев нейронной сети
    vector<Level*> levels;

    //вектор весов между уровнями
    vector<Connection*> connection;

    //шаг обучения
    ld alpha;

    //желаемая среднеквадратичная ошибка нейронной сети
    ld Em;

public:

    NeuralNetwork() = delete;

    //конструктор, с вектором пары(количество нейронов слоя и функции слоя)
    explicit NeuralNetwork(const vector<ParametersForLevel> &NeuronsAndFunctions, ld alpha, ld Em)
            : alpha(alpha), Em(Em) {
        bool check = false;

        /*cout << "Alpha = " << alpha << "; Em = " << Em << ";" << endl;
        cout << "Do you want to change it? (Yes - 1 / No - 0)" << endl;
        cin >> check;

        if (check) {
            cout << "Alpha = ";
            cin >> this->alpha;
            cout << "Em = ";
            cin >> this->Em;
        }*/

        for (const auto& i : NeuronsAndFunctions) {
            levels.push_back(new Level(i.getNumberOfNeurons()));
        }

        for (ull i = 0; i < NeuronsAndFunctions.size() - 1; i++) {
            connection.push_back(new Connection(levels.at(i),
                levels.at(i + 1), alpha, NeuronsAndFunctions.at(i + 1).getFunction(),
                NeuronsAndFunctions.at(i + 1).getDerivativeFunction()));
        }
    }

    //обучение сети
    bool learning(vector<ld> learn) {
        if (learn.size() < levels.at(0)->neurons.size()) {
            throw 1;
        }
        ull time = 0;

        ld E, pred = 0;

        do {
            E = 0.;

            for (ull i = 0; i < learn.size() - levels.at(0)->neurons.size() - levels.at(levels.size() - 1)->neurons.size() + 1; i++) {
                for (ull j = 0; j < levels.at(0)->neurons.size(); j++) {
                    levels.at(0)->neurons.at(j)->x = learn.at(i + j);
                }

                vector<ld> etalon;
                for (ull j = 0; j < levels.at(levels.size() - 1)->neurons.size(); j++) {
                    etalon.push_back(learn.at(i + levels.at(0)->neurons.size() + j));
                }
                for (const auto &con : connection) {
                    con->x_to_y();
                }



                E += connection.at(connection.size() - 1)->backpropogationForLast(etalon);
                for (ull j = connection.size() - 2; j >= 0; j--) {
                    connection.at(j)->
                            backpropogationForHidden(
                            connection.at(j + 1));
                    if (j == 0) {
                        break;
                    }
                }

                for (ull j = connection.size() - 1; j >= 0; j--) {
                    connection.at(j)->changeWAndT();
                    if (j == 0) {
                        break;
                    }
                }
            }

            E /= 2.0;
            if (time % HOW_OFTEN_SHOW_ERROR == 0) {
                if (time > 0) {
                    ull prognoseIterations = (ull)round((E-Em)/(pred-E));
                    /*cout << time / HOW_OFTEN_SHOW_ERROR << ": " << E << endl
                         << "Next is in: " << prognoseIterations << " iterations." << endl;*/
                    if (time / HOW_OFTEN_SHOW_ERROR + prognoseIterations > ITERATIONS / HOW_OFTEN_SHOW_ERROR) {
                        //cout << "IN VAIN!" << endl;
                        return false;
                    }
                }
                pred = E;
            }
        } while (E > Em && ++time < ITERATIONS);
        cout << "////////////////////////////////// " << time << endl;
        return true;
    }

    vector<ld> predicting(vector<ld> vectorStartLearn, ull etalonSize) {
        vector<ld> vectPredicted;
        for (ull i = 0; i < etalonSize; ) {
            for (ull j = 0; j < vectorStartLearn.size(); j++) {
                levels.at(0)->neurons.at(j)->x =
                        vectorStartLearn.at(j);
            }
            for (const auto &con : connection) {
                con->x_to_y();
            }
            for (auto &neuron : levels.at(levels.size() - 1)->neurons) {
                vectPredicted.push_back(neuron->x);
                vectorStartLearn.push_back(neuron->x);
                vectorStartLearn.erase(vectorStartLearn.begin(),
                                       vectorStartLearn.begin() + levels.at(levels.size() - 1)->neurons.size());
                i++;
            }
        }
        return vectPredicted;
    }

};


#endif //NEURONS_NEURALNETWORK_H