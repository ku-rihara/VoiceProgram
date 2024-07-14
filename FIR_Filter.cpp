#include "FIR_Filter.h"
#include"wave.h"

double sinc(const double& x) {

	double result;

	if (x == 0.0) {
		result = 1.0;
	}
	else {
		result = sin(x) / x;
	}


	return result;
}


std::vector<double>FIR_LPF(const double& fe, const int& J, const std::vector<double>& w) {
	std::vector<double>result(w.size());
	int ofset = J / 2;

	for (int m = -J / 2; m <= J / 2; m++) {//-J/2からJ/2まで均等に
		result[ofset + m] = 2.0 * fe * sinc(2.0 * M_PI * fe * m);
	}
	for (int m = 0; m < J + 1; m++) {
		result[m] *= w[m];
	}
	return result;
}

std::vector<double>FIR_HPF(const double& fe, const int& J, const std::vector<double>& w) {
	std::vector<double>result(w.size());
	int ofset = J / 2;

	for (int m = -J / 2; m <= J / 2; m++) {//-J/2からJ/2まで均等に
		result[ofset + m] = sinc(M_PI * m) - 2.0 * fe * sinc(2.0 * M_PI * fe * m);
	}
	for (int m = 0; m < J + 1; m++) {
		result[m] *= w[m];
	}
	return result;
}

std::vector<double>FIR_BPF(const double& fe1, const double& fe2, const int& J, const std::vector<double>& w) {
	std::vector<double>result(w.size());
	int ofset = J / 2;

	for (int m = -J / 2; m <= J / 2; m++) {//-J/2からJ/2まで均等に
		result[ofset + m] =  2.0 * fe2 * sinc(2.0 * M_PI * fe2 * m)
			               - 2.0 * fe1 * sinc(2.0 * M_PI * fe1 * m);
	}
	for (int m = 0; m < J + 1; m++) {
		result[m] *= w[m];
	}
	return result;
}

std::vector<double>FIR_BEF(const double& fe1, const double& fe2, const int& J, const std::vector<double>& w) {
	std::vector<double>result(w.size());
	int ofset = J / 2;

	for (int m = -J / 2; m <= J / 2; m++) {//-J/2からJ/2まで均等に
		result[ofset + m] = sinc(M_PI * m)
			- 2.0 * fe2 * sinc(2.0 * M_PI * fe2 * m)
			+ 2.0 * fe1 * sinc(2.0 * M_PI * fe1 * m);
	}
	for (int m = 0; m < J + 1; m++) {
		result[m] *= w[m];
	}
	return result;
}
