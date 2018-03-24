#include "OLS.h"

//перевод угла rad из радиан в градусы
long double radToDeg(long double rad) {
	return 180.*rad / PI;
}

int main()
{
	int n;
	cin >> n;
	PointSet pointSet(n);
	//создали набор точек и вычислили коэффициенты прямой
	cout << "A=" << pointSet.getA() << endl;
	cout << "B=" << pointSet.getB() << endl;
	long double lambda = pointSet.getLambda();
	cout << "lambda=" << radToDeg(lambda) << endl;
	return 0;
}