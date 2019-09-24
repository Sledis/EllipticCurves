#include "pch.h"
#include "framework.h"
#include <vector>
#include "BasicMathsFunctions.h"

__int64 modulo(__int64 a, __int64 b) {
	int m = a % b;
	if (m < 0) {
		// m += (b < 0) ? -b : b; // avoid this form: it is UB when b == INT_MIN
		m = (b < 0) ? m - b : m + b;
	}
	return m;
}

__int64 isPSquare(__int64 elt, __int64 prime) {
	 
	
	__int64 exponent = (prime - 1) / 2;
	__int64 poweredElt = pow(elt, exponent);
	__int64 js = modulo(poweredElt, prime);
	if (js == 1) {
		return 1;
	}
	else if (js == 0) {
		return 0;
	}
	else {
		return -1; 
	}
	
}

std::vector<__int64> twoAdicBreakDown(__int64 i) {
	std::vector<__int64> result;
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


__int64 modInverse(__int64 a, __int64 m)
{
	__int64 m0 = m;
	__int64 y = 0, x = 1;
	a = modulo(a, m);
	if (m == 1)
		return 0;

	while (a > 1)
	{
		// q is quotient 
		__int64 q = a / m;
		__int64 t = m;

		// m is remainder now, process same as 
		// Euclid's algo 
		m = a % m, a = t;
		t = y;

		// Update y and x 
		y = x - q * y;
		x = t;
	}

	// Make x positive 
	if (x < 0)
		x += m0;

	return x;
}