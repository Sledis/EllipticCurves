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
	bool state = false;
	__int64 i = 0;
	while (!state && i < prime) {

		__int64 trial = modulo(elt - i * i, prime);
		if (trial == 0) {
			state = true;
			return i;
		}
		i++;

	}
	return -1;
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