#include <iostream>
#include <vector>

#include "C:\Users\sam_e\source\repos\EllipticCurves\EllipticCurves\ModEllipticCurve.h"

using namespace std;

int main()
{
	__int64 Coefficients2[5] = { 0, 0, 0, 1, 3 };
	ModEllipticCurve F(Coefficients2, 524287);

	std::pair <int, int> Point3 = F.FindPoint();
	cout << "Point found." << endl;


	__int64 privateKey;
	cout << "Enter a random number, bigger is probably better: " << flush;
	cin >> privateKey;

	cout << "Your private key is: " << privateKey << ". Do not forget this." << endl;
	std::pair <int, int> Point4 = F.getPublicKey(Point3, privateKey);
	cout << "Your public key is: " << flush;
	F.printPoint(Point4);

	

	return 0;
}

