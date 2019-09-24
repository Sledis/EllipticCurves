#pragma once
#include "ModEllipticCurve.h"
class ECDHStarter 
{
public:
	ECDHStarter(__int64 Coefficients[5], __int64 prime);
	std::pair<__int64, __int64> FindPoint();
	std::pair<__int64, __int64> getPublicKey(std::pair <__int64, __int64> Point, __int64 privateKey);
	void createDictionary(std::pair<__int64, __int64>);
	

private:
	ModEllipticCurve E;
};

