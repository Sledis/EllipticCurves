
#include <iostream>
#include <string>
#include <fstream>
#include "ModEllipticCurve.h"
#include "ECDHEncryptor.h"
using namespace std;

int main()
{
	string publicKeyAddress;
	cout << "Enter the address of the public key: " << flush;
	getline(cin, publicKeyAddress);

	ifstream publicKey;
	publicKey.open(publicKeyAddress);

	__int64 a0;
	publicKey >> a0;
	
	__int64 a1;
	publicKey >> a1;
	
	__int64 a2;
	publicKey >> a2;
	
	__int64 a3;
	publicKey >> a3;
	
	__int64 a4;
	publicKey >> a4;


	__int64 prime;
	publicKey >> prime;
	


	__int64 Coefficients[5] = { a0, a1, a2, a3, a4 };
	ECDHEncryptor E(Coefficients, prime);

	__int64 startingxCoord;
	publicKey >> startingxCoord;

	__int64 startingyCoord;
	publicKey >> startingyCoord;

	std::pair<__int64, __int64> startingPoint(startingxCoord, startingyCoord);

	__int64 xCoord;
	publicKey >> xCoord;
	
	
	__int64 yCoord;
	publicKey >> yCoord;
	
	

	std::pair<__int64, __int64> publicPoint(xCoord, yCoord);
	
	string message;
	cout << "Enter a message: ";
	getline(cin, message);

	vector<pair<__int64, __int64>>v=E.messageTransformation(startingPoint, message);

	E.encrypt(v, publicPoint, startingPoint);
	
	return 0;
}


