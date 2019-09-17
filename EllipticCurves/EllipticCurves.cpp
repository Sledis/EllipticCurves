

#include <iostream>
#include "EllipticCurveClass.h"
#include "ModEllipticCurve.h"
using namespace std;




int main()
{
	double Coefficients[5] = { 0, 0, 0, -25, 0 };
	EllipticCurve E(Coefficients);
	E.Display();
	E.FindIntegerPoints(100);
	std::pair <double, double> Point(-4, 6);
	double gradient = E.GetGradient(Point);
	cout << gradient << endl;

	std::pair <double, double> newPoint = E.PointDouble(Point);

	cout << newPoint.first << ", " << newPoint.second << endl;


	int Coefficients2[5] = { 0, 0, 0, 1, 3 };
	ModEllipticCurve F(Coefficients2,11);
	cout << F.xSearch(0) << endl;
	cout << F.FindPoint().first <<" " <<  F.FindPoint().second << endl;

	std::pair <int, int> Point3 = F.FindPoint();
	int grad = F.GetGradient(Point3);

	cout << grad << endl;
	
	std::pair <int, int> Point4 = F.DoublePoint(Point3);
	cout << Point4.first << " " << Point4.second << endl;



	

}


