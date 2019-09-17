#pragma once
#include <string>
class EllipticCurve
{public:
	EllipticCurve(double Coefficients_[5]);
	void Display() const;
	void FindIntegerPoints(int limit) const;
	double GetGradient(std::pair<double, double>) const;
	std::pair<double, double> PointDouble(std::pair<double, double>) const;

private:
	double Coefficients[5];
	std::string Basis[5] = {"XY","Y","X*2","X","1"};
};

