#ifndef NEURONS_NEURALNETWORK_H
#define NEURONS_NEURALNETWORK_H

#include <vector>
#include <iomanip>
#include "Connection.h"
#include "ParametersForLevel.h"

const ld ALPHA_STEP = 0.01;

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
    void learning(vector<ld> learn) {
        if (learn.size() < levels.at(0)->neurons.size()) {
            throw 1;
        }
        ull time = 0;

        ld E = 0.;

        do {
            E = 0.;

            for (ull i = 0; i < learn.size() - levels.at(0)->neurons.size() - levels.at(levels.size() - 1)->neurons.size() + 1; i++) {
                for (ull j = 0; j < levels.at(0)->neurons.size(); j++) {
                    levels.at(0)->neurons.at(j)->x =
                            learn.at(i + j);
                }

                vector<ld> etalon;
                for (ull j = 0; j < levels.at(levels.size() - 1)->neurons.size(); j++) {
                    etalon.push_back(learn.at(i + levels.at(0)->neurons.size() + j));
                }
                for (const auto &con : connection) {
                    con->x_to_y();
                }

                E += connection.at(connection.size() - 1)->backpropogationForLast(etalon);
                for (ll j = connection.size() - 2; j >= 0; j--) {
                    connection.at(j)->
                            backpropogationForHidden(
                            connection.at(j + 1));
                }

                for (ll ii = connection.size()-1; ii>=0; ii--) {
                    if (ii==connection.size()-1) {
                        connection[ii]->alpha = ALPHA_STEP;
                    }
                    else {
                        ld sum1 = 0.;
                        ld sum2 = 0.;
                        ld sum3 = 0.;
                        for (ull j=0; j<connection[ii]->gamma.size(); j++) {
                            sum1 += pow(connection[ii]->gamma[j],2.)
                                    *(connection[ii]->after->neurons[j]->x)
                                    *(1.-connection[ii]->after->neurons[j]->x);
                            sum2 += pow(
                                    connection[ii]->gamma[j]
                                        *(connection[ii]->after->neurons[j]->x)
                                        *(1.-connection[ii]->after->neurons[j]->x),
                                    2.);
                        }
                        for (ull j=0; j<connection[ii+1]->after->neurons.size(); j++) {
                            sum3+= pow(connection[ii+1]->after->neurons[j]->x,2.);
                        }
                        connection[ii]->alpha = 4.*sum1/((1.+sum3)*sum2)>0.5?0.5:4.*sum1/((1.+sum3)*sum2);
                        cout<<"ALPHA = "<<connection[ii]->alpha<<endl;
                    }
                }

                for (ll j = connection.size() - 1; j >= 0; j--) {
                    connection.at(j)->changeWAndT();
                }

            }
            E /= 2.0;
            cout << E << endl;
            //cout << E << ' ' << Em << endl;
        } while (E > Em && ++time < 10000);
        cout << "////////////////////////////////// " << time << endl;
    }

    vector<ld> predicting(vector<ld> vectorStartLearn, ull etalonSize) {
        vector<ld> vectPredicted;
        for (ull i=0; i<etalonSize;) {
            for (ull j=0; j<vectorStartLearn.size(); j++) {
                levels.at(0)->neurons.at(j)->x = vectorStartLearn.at(j);
            }
            for (const auto &con : connection) {
                con->x_to_y();
            }
            for (ull j=0; j<levels.at(levels.size()-1)->neurons.size(); j++) {
                vectPredicted.push_back(levels.at(levels.size()-1)->neurons.at(j)->x);
                vectorStartLearn.push_back(levels.at(levels.size()-1)->neurons.at(j)->x);
                vectorStartLearn.erase(vectorStartLearn.begin()+1);
                i++;
            }
        }
        vectPredicted.resize(etalonSize);
        return vectPredicted;
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