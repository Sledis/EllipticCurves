#include "ModEllipticCurve.h"
#include <iostream>
#include <vector>
#include "BasicMathsFunctions.h"



ModEllipticCurve::ModEllipticCurve(__int64 Coefficients_[5], __int64 prime_) :prime(prime_) {
	for (int i = 0; i < 5; i++) {
		Coefficients[i] = Coefficients_[i];
	}
	infinity = std::pair <__int64, __int64>(INT_MIN, INT_MIN);
};

int ModEllipticCurve::PointEvaluation(std::pair<__int64, __int64> Point) {
	__int64 y = Point.second;
	__int64 x = Point.first;

	__int64 value = y * y + Coefficients[0] * x * y + Coefficients[1] * y - (x * x * x + Coefficients[2] * x * x + Coefficients[3] * x + Coefficients[4]);
	return modulo(value , prime);
}

int ModEllipticCurve::xSearch(__int64 xCoord) {
	__int64 A = 1;
	__int64 B = modulo(Coefficients[0] * xCoord + Coefficients[1] , prime);
	__int64 C = modulo( -(xCoord * xCoord * xCoord + Coefficients[2] * xCoord * xCoord + Coefficients[3] * xCoord + Coefficients[4]) , prime);
	__int64 Delta = modulo( B * B - 4 * A * C , prime);
	__int64 rootDelta = isPSquare(Delta, prime);
	if (rootDelta < 0) {
		return -1;
	}
	return modulo((-B + rootDelta) * (prime + 1) / 2 , prime);
}


std::pair<__int64, __int64> ModEllipticCurve::FindPoint() {
	bool state = false;
	__int64 xTrial = 0;
	while (!state) {
		__int64 yTrial = xSearch(xTrial);
		if (yTrial >= 0) {
			return std::pair<int, int>(xTrial, yTrial);
		}


		xTrial++;
	}

}


int ModEllipticCurve::GetGradient(std::pair<__int64, __int64 > point)  {
	__int64 x = point.first;
	__int64 y = point.second;

	__int64 Numerator = modulo(3 * x * x + 2 * Coefficients[2] * x + Coefficients[3] - Coefficients[0] * y , prime);
	__int64 Denominator = modulo(2 * y + Coefficients[0] * x + Coefficients[1] , prime);

	if (Denominator != 0) {
		__int64 i = 1;
		bool state = false;
		while (!state) {
			if (modulo(i * Denominator , prime) == 1) {
				state = true;
			}
			else {
				i++;
			}
		}
		return modulo(Numerator * i , prime);
	}
	else {
		return INT_MIN;
	}
};


std::pair<__int64, __int64> ModEllipticCurve::DoublePoint(std::pair<__int64, __int64> Point) {
	__int64 x = Point.first;
	__int64 y = Point.second;
	__int64 grad = GetGradient(Point);
	if (grad != INT_MIN){
		__int64 xNew = modulo(-(-grad * grad - Coefficients[0] * grad + 2 * x + Coefficients[2]), prime);
		__int64 yNew1 = (-(y + grad * (xNew - x)));
		__int64 yNew = modulo(yNew1, prime);
		return std::pair<int, int>(xNew, yNew);
	}
	else {
		return std::pair<__int64, __int64>(INT_MIN, INT_MIN);
	}
	
}

std::pair<__int64, __int64> ModEllipticCurve::AddedPoint(std::pair<__int64, __int64> Point1, std::pair<__int64, __int64> Point2) {
	__int64 x1 = Point1.first;
	__int64 x2 = Point2.first;
	__int64 y1 = Point1.second;
	__int64 xNew;
	__int64 yNew;
	if (Point1 == Point2) {
		return DoublePoint(Point1);
	}
	else {
		__int64 Numerator = Point2.second - Point1.second;
		__int64 Denominator = Point2.first - Point1.first;
		if (modulo(Denominator, prime) == 0) {
			return std::pair<int, int>(INT_MIN, INT_MIN);
		}
		bool state = false;
		__int64 i = 1;
		while (!state) {
			if (modulo(i * Denominator, prime) == 1) {
				state = true;
			}
			else {
				i++;
			}
		}
		__int64 grad = modulo(Numerator * i, prime);
		xNew = modulo(-(-grad * grad - Coefficients[0] * grad + x1+x2 + Coefficients[2]), prime);
		__int64 yNew1 = (-(y1 + grad * (xNew - x1)));
		yNew = modulo(yNew1, prime);
	}
	return std::pair<int, int>(xNew, yNew);
}

std::pair<__int64, __int64> ModEllipticCurve::MultipliedPoint(std::pair<__int64, __int64> Point, __int64 mult) {
	std::vector<__int64> v = twoAdicBreakDown(mult);
	std::pair<__int64, __int64> runningSumPoint;
	bool state = false;
	for (std::vector<__int64>::iterator it = v.begin(); it != v.end(); it++) {

		if (*it == 1) {
			if (!state) {
				runningSumPoint = Point;
				state = true;
			}
			else {
				runningSumPoint = AddedPoint(Point, runningSumPoint);
			}
		}
		Point = DoublePoint(Point);
	}
	return runningSumPoint;
}

void ModEllipticCurve::printPoint(std::pair <__int64, __int64> Point) {
	std::cout << "(" << Point.first << "," << Point.second << ")" << std::endl;
}

int ModEllipticCurve::GetOrder(std::pair <__int64, __int64> Point) {
	std::pair <__int64, __int64> startingPoint = Point;
	int i = 1;
	while (Point != infinity) {
		Point = AddedPoint(Point, startingPoint);
		i++;
	}
	return i;
}

std::pair<__int64, __int64> ModEllipticCurve::getPublicKey(std::pair <__int64, __int64> Point, __int64 privateKey) {
	std::pair<__int64, __int64> v = MultipliedPoint(Point, privateKey);
	return v;
}