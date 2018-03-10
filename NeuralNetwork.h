#ifndef NEURONS_NEURALNETWORK_H
#define NEURONS_NEURALNETWORK_H


#include <vector>
#include <iomanip>
#include "Level.h"
#include "Connection.h"

using std::vector;
using std::cin;
using std::cout;
using std::endl;


class NeuralNetwork {

    //вектор слоев нейронной сети
    vector<Level*> levels;

    //вектор весов между уровнями
    vector<Connection*> w;

    //шаг обучения
    ld alpha;

    //желаемая среднеквадратичная ошибка нейронной сети
    ld Em;

public:

    NeuralNetwork() = delete;

    //конструктор, с вектором пары(количество нейронов слоя и функции слоя)
    explicit NeuralNetwork(const vector<std::pair<ull,
            ld (*)(const ld sum)>> &NeuronsAndFunctions, ld alpha, ld Em)
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
            levels.push_back(new Level(i.first, i.second));
        }

        for (ull i = 0; i < NeuronsAndFunctions.size() - 1; i++) {
            w.push_back(new Connection(levels.at(i),
                                       levels.at(i + 1)));
        }

    }

    //обучение сети(в разработке)
    void learning(vector<ld> learn) {
        for (ull i = 0; i < learn.size() - levels.at(0)->neurons.size() + 1; i++) {

            for (ull j = 0; j < levels.at(0)->neurons.size(); j++) {
                levels.at(0)->neurons.at(j)->x = learn.at(i + j);
            }

            for (const auto &j : w) {
                j->x_to_y();
            }

            show();
            cout << endl;

        }
        /*for (ull i = 0; i < levels.size(); i++) {

        }*/
    }

    //демонстрация весов
    void show() const {
        for (const auto &i : levels) {
            i->get();
        }
//        std::cout << "///////////////////////////" << std::endl;
//        for (const auto &i : w) {
//            i->show();
//            std::cout << "///////////////////////////" << std::endl;
//        }
    }

};


#endif //NEURONS_NEURALNETWORK_H