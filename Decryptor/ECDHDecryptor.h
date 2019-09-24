#pragma once
#include "ModEllipticCurve.h"
#include <map>
using namespace std;
class ECDHDecryptor
{
public:
	ECDHDecryptor(__int64 Coefficients[5], __int64 prime);
	std::pair<__int64, __int64> Decrypt(std::pair<__int64, __int64> B1, std::pair<__int64, __int64> B2, __int64 privateKey);
	std::string decryptMessage(map<pair<__int64, __int64>, char> dict, std::string, __int64 privateKey);

private:
	ModEllipticCurve E;
};

