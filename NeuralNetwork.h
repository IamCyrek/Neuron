#ifndef NEURONS_NEURALNETWORK_H
#define NEURONS_NEURALNETWORK_H


#include <vector>
#include <iomanip>
#include "Connection.h"
#include "ParametersForLevel.h"

using std::vector;
using std::cin;
using std::cout;
using std::endl;


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

    //обучение сети(в разработке)
    void learning(vector<ld> learn) {
        ull time = 0;
        ld E = 0.;

        do {
            for (ull i = 0; i < learn.size() - levels.at(0)->neurons.size() - levels.at(levels.size() - 1)->neurons.size() + 1; i++) {
                for (ull j = 0; j < levels.at(0)->neurons.size(); j++) {
                    levels.at(0)->neurons.at(j)->x = learn.at(i + j);
                }

                vector<ld> etalon;
                for (ull j = 0; j < levels.at(levels.size() - 1)->neurons.size(); j++) {
                    etalon.push_back(i + levels.at(0)->neurons.size() + j);
                }
                for (const auto &con : connection) {
                    con->x_to_y();
                }

                connection.at(connection.size() - 1)->backpropogationForLast(etalon);
                for (ll j = connection.size() - 2; j >= 0; j--) {
                    connection.at(j)->
                            backpropogationForHidden(
                            connection.at(j + 1));
                }



                show();
                cout << endl;
            }
        } while (E > Em && ++time < 1);
    }

    //демонстрация весов
    void show() const {
        for (const auto &i : levels) {
            i->get();
        }
//        std::cout << "///////////////////////////" << std::endl;
//        for (const auto &i : connection) {
//            i->show();
//            std::cout << "///////////////////////////" << std::endl;
//        }
    }

};


#endif //NEURONS_NEURALNETWORK_H