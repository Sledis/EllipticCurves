#pragma once
#include "ModEllipticCurve.h"
#include <vector>
using namespace std;
class ECDHEncryptor
{
public:
	ECDHEncryptor(__int64 Coefficients[5], __int64 prime);
	std::pair<__int64, __int64> characterTransformation(std::pair<__int64, __int64>, char);
	vector<pair<__int64, __int64>> messageTransformation(std::pair<__int64, __int64>, std::string);
	std::pair< std::pair<__int64, __int64>, std::pair<__int64, __int64>> GetCipherText(std::pair<__int64, __int64> M, std::pair<__int64, __int64> publicKey, std::pair<__int64, __int64> startingPoint);
	void encrypt(vector<pair<__int64, __int64>> transormedMessage, std::pair<__int64, __int64> publicKey, std::pair<__int64, __int64> startingPoint);
	

private:
	ModEllipticCurve E;
};

