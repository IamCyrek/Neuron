#ifndef OLS_H
#define OLS_H

#define PI 3.14159265;

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class Point {
	long double x;
	long double y;
public:

	void read() {
		cin >> x >> y;
	}

	long double getX() {
		return x;
	}
	long double getY() {
		return y;
	}

	Point(long double x=0., long double y=0.) {
		this->x = x;
		this->y = y;
	}
};

class PointSet {

	vector<Point> points;

	long double X, Y, X2, XY, A, B, lambda;

	void calcEverything() {
		calcKoeff();
		calcA();
		calcB();
		calcLambda();
	}

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

	void calcA() {
		A = (XY - X*Y) / (X2 - X*X);
	}
	void calcB() {
		B = Y - A*X;
	}

	void calcLambda() {
		lambda = atan(A);
	}

public:
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
