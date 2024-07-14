#include "IIR_Filter.h"
#include"wave.h"

void IIR_LPF(const double& fc, const double& Q, std::vector<double>& a, std::vector<double>& b) {
	
	const double cutoffFrequency = tan(M_PI * fc) / (2.0 * M_PI);//アナログ遮断周波数

	a[0] = 1.0 + 2.0 * M_PI * cutoffFrequency / Q + 4.0 * std::pow(M_PI, 2) * std::pow(cutoffFrequency, 2);
	a[1] = (8.0 * std::pow(M_PI, 2) * std::pow(cutoffFrequency, 2) - 2.0) / a[0];
	a[2] = (1.0 - 2.0 * M_PI * cutoffFrequency / Q + 4.0 * std::pow(M_PI, 2) * std::pow(cutoffFrequency, 2)) / a[0];
	b[0] = (4.0 * std::pow(M_PI, 2) * std::pow(cutoffFrequency, 2)) / a[0];
	b[1] = (8.0 * std::pow(M_PI, 2) * std::pow(cutoffFrequency, 2)) / a[0];
	b[2] = (4.0 * std::pow(M_PI, 2) * std::pow(cutoffFrequency, 2)) / a[0];

	a[0] = 1.0;
}

void IIR_HPF(const double& fc, const double& Q, std::vector<double>& a, std::vector<double>& b) {
	const double analogFrequency = tan(M_PI * fc) / (2.0 * M_PI);//アナログ遮断周波数
	a[0] = 1.0 + 2.0 * M_PI * analogFrequency / Q + 4.0 * std::pow(M_PI, 2) * std::pow(analogFrequency, 2);
	a[1] = (8.0 * std::pow(M_PI, 2) * std::pow(analogFrequency, 2) - 2.0) / a[0];
	a[2] = (1.0 - 2.0 * M_PI * analogFrequency / Q + 4.0 * std::pow(M_PI, 2) * std::pow(analogFrequency, 2)) / a[0];
	b[0] = 1.0 / a[0];
	b[1] = -2 / a[0];
	b[2] = 1.0 / a[0];

	a[0] = 1.0;
}

void IIR_BPF(const double& fcLow, const double& fcHight,std::vector<double>& a, std::vector<double>& b) {
	const double analogFrequencyLow = tan(M_PI * fcLow) / (2.0 * M_PI);//アナログ遮断周波数(低い)
	const double analogFrequencyHight = tan(M_PI * fcHight) / (2.0 * M_PI);//アナログ遮断周波数(高い)

	a[0] = 1.0 + 2.0 * M_PI * (analogFrequencyHight - analogFrequencyLow) + 4.0 * pow(M_PI, 2) * analogFrequencyLow * analogFrequencyHight;
	a[1] = (8.0 * pow(M_PI, 2) * analogFrequencyLow * analogFrequencyHight - 2) / a[0];
	a[2] = (1.0 - 2.0 * M_PI * (analogFrequencyHight - analogFrequencyLow) + 4.0 * pow(M_PI, 2) * analogFrequencyLow * analogFrequencyHight) / a[0];
	b[0] = (2.0 * M_PI * (analogFrequencyHight - analogFrequencyLow)) / a[0];
	b[1] = 0.0;
	b[2] = (-2.0 * M_PI * (analogFrequencyHight - analogFrequencyLow)) / a[0];

	a[0]=1.0;
}

void IIR_resonator(const double& fc, const double& Q, std::vector<double>& a, std::vector<double>& b) {
	const double analogFrequency = tan(M_PI * fc) / (2.0 * M_PI);//アナログ遮断周波数

	a[0] = 1.0 + 2.0 * M_PI * analogFrequency / Q + 4.0 * std::pow(M_PI, 2) * std::pow(analogFrequency, 2);
	a[1] = (8.0 * std::pow(M_PI, 2) * std::pow(analogFrequency, 2) - 2.0) / a[0];
	a[2] = (1.0 - 2.0 * M_PI * analogFrequency / Q + 4.0 * std::pow(M_PI, 2) * std::pow(analogFrequency, 2)) / a[0];
	b[0] = 2.0 * M_PI * analogFrequency / Q / a[0];
	b[1] = 0.0;
	b[2] = -2.0 * M_PI * analogFrequency / Q / a[0];

	a[0] = 0.0;
}

void IIR_Filtering(const std::vector <double>& originalS, std::vector <double>& filterS, const int& Lenght, const std::vector <double>& a, const std::vector <double>& b, const int& I, const int& J) {
	//フィルタリング
	for (int n = 0; n < Lenght; n++) {
		for (int m = 0; m <= J; m++) {
			if (n - m >= 0) {
				filterS[n] += b[m] * originalS[n - m];
			}
		}
		for (int m = 1; m <= I; m++) {
			if (n - m >= 0) {
				filterS[n] += -a[m] * filterS[n - m];
			}
		}
	}
}