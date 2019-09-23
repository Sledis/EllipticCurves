

#include <iostream>
#include <vector>
#include "BasicMathsFunctions.h"
#include "EllipticCurveClass.h"
#include "ModEllipticCurve.h"
using namespace std;





int main()
{
	/*
	double Coefficients[5] = { 0, 0, 0, -25, 0 };
	EllipticCurve E(Coefficients);
	E.Display();
	E.FindIntegerPoints(100);
	std::pair <double, double> Point(-4, 6);
	double gradient = E.GetGradient(Point);
	cout << gradient << endl;

	std::pair <double, double> newPoint = E.PointDouble(Point);

	cout << newPoint.first << ", " << newPoint.second << endl;

	*/
	__int64 Coefficients2[5] = { 0, 0, 0, 1, 3 };
	ModEllipticCurve F(Coefficients2, 524287);
	//cout << F.xSearch(0) << endl;
	//cout << F.FindPoint().first <<" " <<  F.FindPoint().second << endl;

	std::pair <int, int> Point3 = F.FindPoint();
	cout << "Point found." << endl;
	F.printPoint(Point3);
	//int order = F.GetOrder(Point3);
	//cout << "Order found." << endl;
	//for (int i = 1; i < 524287 +1; i++) {
		//std::pair <int, int> Point4 = F.MultipliedPoint(Point3, i);
		//F.printPoint(Point4);
	//}
	/*
	__int64 privateKey;
	cout << "Enter a random number, bigger is probably better: " << flush;
	cin >> privateKey;

	std::pair <int, int> Point4 = F.getPublicKey(Point3, privateKey);
	F.printPoint(Point4);
	
	*/
	__int64 value1;
	__int64 value2;
	cout << "Enter the public Key: " << endl;
	cin >> value1;
	cin >> value2;

	std::pair<__int64, __int64> publicKey = std::pair<__int64, __int64>(value1, value2);

	std::pair<std::pair<__int64, __int64>, std::pair<__int64, __int64>> v = F.GetCipherText(Point3,publicKey);

	cout << (v.first).first << ", " << v.first.second << endl;
	cout << (v.second).first << ", " << v.second.second << endl;


	std::pair<__int64, __int64> M = F.Decrypt(v.first, v.second, 154624);
	cout << M.first << ", " << M.second << endl;

	return 0;
}


