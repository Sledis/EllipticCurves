#pragma once
#include <string>
class ModEllipticCurve
{
public:
	ModEllipticCurve(__int64 Coefficients[5],__int64 prime);
	int PointEvaluation(std::pair<__int64, __int64> Point);
	std::pair<__int64, __int64> FindPoint();
	int xSearch(__int64 xCoord);
	int GetGradient(std::pair<__int64, __int64> Point);
	std::pair<__int64, __int64> DoublePoint(std::pair<__int64, __int64> Point);
	std::pair<__int64, __int64> AddedPoint(std::pair<__int64, __int64> Point1, std::pair<__int64, __int64> Point2);
	std::pair<__int64, __int64> MultipliedPoint(std::pair<__int64, __int64> Point, __int64 mult);
	void printPoint(std::pair <__int64, __int64> Point);
	int GetOrder(std::pair <__int64, __int64> Point);
	std::pair<__int64, __int64> getPublicKey(std::pair <__int64, __int64> Point, __int64 privateKey);

private:
	__int64 Coefficients[5];
	__int64 prime;
	std::pair <__int64, __int64> infinity;

};

