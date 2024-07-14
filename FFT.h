#pragma once
#include<vector>
#include<ccomplex>

std::vector<std::complex<double>> DFT(const int& DFTsize, const std::vector <double>& data);

void FFT(std::vector<std::complex<double>>& x, const int& DFTsize, bool isReverse);