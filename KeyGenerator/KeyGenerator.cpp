#include "ModEllipticCurve.h"
#include "ECDHStarter.h"
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	__int64 a0;
	__int64 a1;
	__int64 a2;
	__int64 a3;
	__int64 a4;
	cout << "Enter the coefficients of an elliptic curve in the order Y^2+a_0XY+a_1Y=X^3+a_2X^2+a_3X+a_4" << endl;
	cin >> a0;
	cin >> a1;
	cin >> a2;
	cin >> a3;
	cin >> a4;

	__int64 Coefficients[5] = { a0, a1, a2, a3, a4 };

	__int64 prime;
	cout << "Enter a prime (large): " << flush;
	cin >> prime;
	clock_t time_req;
	time_req = clock();

	ECDHStarter F(Coefficients, prime);

	std::pair <int, int> startingPoint = F.FindPoint();

	srand(time(0));
	__int64 privateKey = rand();
	std::pair <__int64, __int64> publicPoint = F.getPublicKey(startingPoint, privateKey);


	ofstream keys;

	keys.open("publicKey.txt");
	for (int i = 0; i < 4; i++) {
		keys << Coefficients[i] << " ";
	}
	keys << Coefficients[4] << endl;
	keys << prime << endl;
	keys << startingPoint.first << " " << startingPoint.second << endl;
	keys << publicPoint.first << " " << publicPoint.second << endl;
	keys.close();
	keys.clear();


	keys.open("privateKey.txt");
	for (int i = 0; i < 4; i++) {
		keys << Coefficients[i] << " ";
	}
	keys << Coefficients[4] << endl;
	keys << prime << endl;
	keys << startingPoint.first << " " << startingPoint.second << endl;
	keys << publicPoint.first << " " << publicPoint.second << endl;
	keys << privateKey;
	keys.close();
	keys.clear();

	F.createDictionary(startingPoint);
	


	return 0;
}

