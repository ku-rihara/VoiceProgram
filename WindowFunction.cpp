#include "WindowFunction.h"
#include"wave.h"

std::vector<double>  HanningWindow(const int& N) {
	std::vector<double>result(N);
	if (N % 2 == 0) {/*Nが偶数の時*/
		for (int n = 0; n < N; n++) {
			result[n] = 0.5 - (0.5 * cos((2 * M_PI * n) / N));
		}
	}
	else {//Nが奇数の時
		for (int n = 0; n < N; n++) {
			result[n] = 0.5 - (0.5 * cos((2 * M_PI * (n + 0.5)) / N));
		}
	}
	return result;
}