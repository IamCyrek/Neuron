#ifndef OLS_H
#define OLS_H

//число пи
#define PI 3.14159265;

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

///////////////////////////////////////////////////
// класс Point - точка на координатной плоскости //
///////////////////////////////////////////////////

class Point {
	//x,y - координаты
	long double x;
	long double y;
public:

	//считывание точки
	void read() {
		cin >> x >> y;
	}

	//геттеры на координаты точки
	long double getX() {
		return x;
	}
	long double getY() {
		return y;
	}

	//конструктор точки
	Point(long double x=0., long double y=0.) {
		this->x = x;
		this->y = y;
	}
};

////////////////////////////////////////////////////////////
// класс PointSet - набор точек на координатной плоскости //
////////////////////////////////////////////////////////////

class PointSet {

	//points - набор точек
	vector<Point> points;

	//X - сумма x-ов точек
	//Y - сумма y-ов точек
	//X2 - сумма квадратов x-ов точек
	//XY - сумма произведений x*y точек
	//A,B - коэффициенты получившейся прямой y=Ax+B
	//lambda - угол поворота прямой в радианах
	long double X, Y, X2, XY, A, B, lambda;

	//вычисляет все поля
	void calcEverything() {
		calcKoeff();
		calcA();
		calcB();
		calcLambda();
	}

	//вычисление коэффициентов X, Y, X2, XY
	void calcKoeff() {
		X = 0., Y = 0., X2 = 0., XY = 0.;
		for (auto point : points) {
			X += point.getX();
			Y += point.getY();
			X2 += pow(point.getX(), 2.);
			XY += point.getX()*point.getY();
		}
		long double n = (long double)points.size();
		X /= n, Y /= n, X2 /= n, XY /= n;
	}

	//вычисление коэффициентов прямой A и B по формулам МНК
	void calcA() {
		A = (XY - X*Y) / (X2 - X*X);
	}
	void calcB() {
		B = Y - A*X;
	}

	//вычиление угла поворота прямой lambda в радианах
	void calcLambda() {
		lambda = atan(A);
	}

public:
	//конструктор набора точек
	//n - количество точек в наборе
	PointSet(int n) {
		points.clear();
		for (int i = 0; i < n; i++) {
			Point point;
			point.read();
			points.push_back(point);
		}
		calcEverything();
	}

	PointSet(vector<Point> points) {
		this->points = points;
		calcEverything();
	}

	//геттеры
	long double getA() {
		return A;
	}
	long double getB() {
		return B;
	}
	long double getLambda() {
		return lambda;
	}

};

#endif //OLS_H
