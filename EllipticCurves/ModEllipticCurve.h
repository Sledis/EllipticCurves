#pragma once
#include <string>
class ModEllipticCurve
{
public:
	ModEllipticCurve(int Coefficients[5],int prime);
	int PointEvaluation(std::pair<int, int> Point);
	std::pair<int, int> FindPoint();
	int xSearch(int xCoord);
	int GetGradient(std::pair<int, int> Point);
	std::pair<int, int> DoublePoint(std::pair<int, int> Point);
	std::pair<int, int> AddedPoint(std::pair<int, int> Point1, std::pair<int, int> Point2);
	std::pair<int, int> MultipliedPoint(std::pair<int, int> Point, int mult);

private:
	int Coefficients[5];
	int prime;

};

