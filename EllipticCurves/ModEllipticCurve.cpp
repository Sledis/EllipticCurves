#include "ModEllipticCurve.h"
#include <iostream>
#include <vector>

int modulo(int a, int b) {
	int m = a % b;
	if (m < 0) {
		// m += (b < 0) ? -b : b; // avoid this form: it is UB when b == INT_MIN
		m = (b < 0) ? m - b : m + b;
	}
	return m;
}

int isPSquare(int elt, int prime) {
	bool state = false;
	int i = 0;
	while (!state && i < prime) {

		int trial = modulo(elt - i * i , prime);
		if (trial == 0) {
			state = true;
			return i;
		}
		i++;

	}
	return -1;
}

std::vector<int> twoAdicBreakDown(int i) {
	std::vector<int> result;
	while (i > 0) {
		if (modulo(i, 2) == 1) {
			result.push_back(1);
			i = (i - 1) / 2;
		}
		else {
			result.push_back(0);
			i = i / 2;
		}
	}
	return result;
}

ModEllipticCurve::ModEllipticCurve(int Coefficients_[5], int prime_) :prime(prime_) {
	for (int i = 0; i < 5; i++) {
		Coefficients[i] = Coefficients_[i];
	}
};

int ModEllipticCurve::PointEvaluation(std::pair<int, int> Point) {
	int y = Point.second;
	int x = Point.first;

	int value = y * y + Coefficients[0] * x * y + Coefficients[1] * y - (x * x * x + Coefficients[2] * x * x + Coefficients[3] * x + Coefficients[4]);
	return modulo(value , prime);
}

int ModEllipticCurve::xSearch(int xCoord) {
	int A = 1;
	int B = modulo(Coefficients[0] * xCoord + Coefficients[1] , prime);
	int C = modulo( -(xCoord * xCoord * xCoord + Coefficients[2] * xCoord * xCoord + Coefficients[3] * xCoord + Coefficients[4]) , prime);
	int Delta = modulo( B * B - 4 * A * C , prime);
	int rootDelta = isPSquare(Delta, prime);
	if (rootDelta < 0) {
		return -1;
	}
	return modulo((-B + rootDelta) * (prime + 1) / 2 , prime);
}


std::pair<int, int> ModEllipticCurve::FindPoint() {
	bool state = false;
	int xTrial = 0;
	while (!state) {
		int yTrial = xSearch(xTrial);
		if (yTrial >= 0) {
			return std::pair<int, int>(xTrial, yTrial);
		}


		xTrial++;
	}

}


int ModEllipticCurve::GetGradient(std::pair<int, int > point)  {
	int x = point.first;
	int y = point.second;

	int Numerator = modulo(3 * x * x + 2 * Coefficients[2] * x + Coefficients[3] - Coefficients[0] * y , prime);
	int Denominator = modulo(2 * y + Coefficients[0] * x + Coefficients[1] , prime);

	if (Denominator != 0) {
		int i = 1;
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
		throw "Point of order 2.";
	}
};


std::pair<int, int> ModEllipticCurve::DoublePoint(std::pair<int, int> Point) {
	int x = Point.first;
	int y = Point.second;
	int grad = GetGradient(Point);
	int xNew = modulo(-(-grad * grad - Coefficients[0] * grad + 2 * x+Coefficients[2]) , prime);
	int yNew1 = (-(y + grad * (xNew - x)));
	int yNew = modulo(yNew1 , prime);
	std::cout << yNew << std::endl;
	return std::pair<int, int> (xNew, yNew) ;
}

std::pair<int, int> ModEllipticCurve::AddedPoint(std::pair<int, int> Point1, std::pair<int, int> Point2) {
	int x1 = Point1.first;
	int x2 = Point2.first;
	int y1 = Point1.second;
	int xNew;
	int yNew;
	if (Point1 == Point2) {
		return DoublePoint(Point1);
	}
	else {
		int Numerator = Point2.second - Point1.second;
		int Denominator = Point2.first - Point1.first;
		bool state = false;
		int i = 1;
		while (!state) {
			if (modulo(i * Denominator, prime) == 1) {
				state = true;
			}
			else {
				i++;
			}
		}
		int grad = modulo(Numerator * i, prime);
		xNew = modulo(-(-grad * grad - Coefficients[0] * grad + x1+x2 + Coefficients[2]), prime);
		int yNew1 = (-(y1 + grad * (xNew - x1)));
		yNew = modulo(yNew1, prime);
	}
	return std::pair<int, int>(xNew, yNew);
}

std::pair<int, int> ModEllipticCurve::MultipliedPoint(std::pair<int, int> Point, int mult) {
	std::pair<int, int> PartialSumPoint;
	std::pair<int, int> IndexPoint = Point;
	while (mult > 0) {

	}
}