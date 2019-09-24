#include "ECDHStarter.h"
#include "ModEllipticCurve.h"

#include <fstream>

ECDHStarter::ECDHStarter(__int64 Coefficients[5], __int64 prime)  {
	ModEllipticCurve F(Coefficients, prime);
	E = F;
};

std::pair<__int64, __int64> ECDHStarter::FindPoint() {
	return E.FindPoint();
}

std::pair<__int64, __int64> ECDHStarter::getPublicKey(std::pair <__int64, __int64> Point, __int64 privateKey) {
	std::pair<__int64, __int64> v = E.MultipliedPoint(Point, privateKey);
	return v;
}

void ECDHStarter::createDictionary(std::pair<__int64, __int64> point) {
	std::ofstream dictionary;
	dictionary.open("Dictionary.txt");
	for (int i = 33; i < 127; i++) {
		dictionary << char(i) << ' ' << E.MultipliedPoint(point, i).first << ' ' << E.MultipliedPoint(point, i).second << std::endl ; 
	}
}