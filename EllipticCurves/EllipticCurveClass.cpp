#include "EllipticCurveClass.h"
#include <iostream>
EllipticCurve::EllipticCurve(double Coefficients_[5])  {
	for (int i = 0; i < 5; i++) {
		Coefficients[i] = Coefficients_[i];
	
	}
};

void EllipticCurve::Display() const {
	std::cout << "Y*2+" << Coefficients[0] << "XY+" << Coefficients[1] << "Y=X*3+" << Coefficients[2] << "X*2+" << Coefficients[3] << "X+" << Coefficients[4] << "." << std::endl;
}

void EllipticCurve::FindIntegerPoints(int Limit) const {
	int i = -Limit;
	while ( i < Limit+1) {
		double b = Coefficients[0] * i + Coefficients[1];
		double c =-( i * i * i + Coefficients[2] * i * i + Coefficients[3] * i + Coefficients[4]);
		double delta = b * b - 4 * c;
		double rootDelta = sqrt(delta);
		double yLong = (-b + rootDelta) / 2;
		if (yLong - floor(yLong) == 0) {
			std::cout << i << ", " << floor(yLong) << std::endl;
			
		}
		i++;
	}
}

double EllipticCurve::GetGradient(std::pair<double, double > point) const {
	double x = point.first;
	double y = point.second;

	double Numerator = 3 * x * x + 2 * Coefficients[2] * x + Coefficients[3] - Coefficients[0] * y;
	double Denominator = 2 * y + Coefficients[0] * x + Coefficients[1];

	if (Denominator != 0) {
		return Numerator / Denominator;
	}
	else {
		throw "Point of order 2.";
	}
};

std::pair<double, double> EllipticCurve::PointDouble(std::pair<double, double> point) const {
	double g = GetGradient(point);
	double xNew = -Coefficients[2] + g * g + Coefficients[0] * g - 2 * point.first;
	double yNew = g * (xNew - point.first) + point.second;
	std::pair <double, double> doubledPoint(xNew, -yNew);

	return doubledPoint;
};