#include "FFT.h"
#include"wave.h"

//フーリエ変換
std::vector<std::complex<double>> DFT(const int& DFTsize, const std::vector <double>& data) {

	std::vector<std::complex<double>>result(DFTsize, {});
	std::vector<std::complex<double>>x(DFTsize, {});
	std::complex<double>imag(0, 1);
	double	theta;

	//読み込んだ音データのコピー
	for (int n = 0; n < DFTsize; n++) {
		x[n].real(data[n]);//x(n)の実数部
		x[n].imag(0.0);//x(n)の虚数部	
	}

	for (int k = 0; k < DFTsize; k++) {
		for (int n = 0; n < DFTsize; n++) {
			theta = 2.0 * M_PI * k * n / DFTsize;//θ
			result[k] += x[n] * std::exp(-imag * theta);//フーリエ変換の公式
		}
	}
	return result;
}


void  FFT(std::vector<std::complex<double>>& x, const int& DFTsize, bool isReverse) {

	int FFTStage = int(std::log2(DFTsize));/*FFTの段階()*/

	std::complex<double>imag(0, 1);// 虚数単位
	//値の格納用
	std::complex<double>a{};
	std::complex<double>b{};
	std::complex<double>c{};
	std::complex<double>d{};
	////読み込んだデータのコピー

	//バタフライ演算
	for (int stage = 1; stage <= FFTStage; stage++) {//FFTの段階

		for (int i = 0; i < std::pow(2, stage - 1); i++) {

			for (int j = 0; j < std::pow(2, FFTStage - stage); j++) {

				// バタフライ演算のインデックス計算
				int n = int(std::pow(2, FFTStage - stage + 1) * i + j);
				int m = int(std::pow(2, FFTStage - stage) + n);
				int r = int(std::pow(2, stage - 1) * j);
				a = x[n];
				b = x[m];
				double theta = (2.0 * M_PI * r) / DFTsize;//θ
				//演算内容を書く
				if (stage < FFTStage) {
					x[n] = a + b;
					if (isReverse) {
						x[m] = (a - b) * std::exp(imag * theta);
					}
					else {
						x[m] = (a - b) * std::exp(-imag * theta);
					}
				}
				else {//最後の段階では足し算と引き算になる
					x[n] = a + b;
					x[m] = a - b;
				}
			}
		}
	}

	//インデックスの並び変え用のテーブル作成
	std::vector<int>index(DFTsize);
	for (int stage = 1; stage <= FFTStage; stage++) {

		for (int i = 0; i < std::pow(2, stage - 1); i++) {
			index[int(std::pow(2, stage - 1) + i)] =
				int(index[i] + std::pow(2, FFTStage - stage));
		}
	}
	//インデックス並び替え
	for (int k = 0; k < DFTsize; k++) {
		if (index[k] > k) {
			d = x[index[k]];
			x[index[k]] = x[k];
			x[k] = d;
		}
	}
	/* 計算結果をNで割る */
	for (int k = 0; k < DFTsize; k++) {
		if (isReverse) {
			x[k] /= DFTsize;
		}
	}
}

