﻿#include "SoundWave.h"
#include"WindowFunction.h"
#include"IIR_Filter.h"
#include"FFT.h"
#include<map>
#include <string>
#include<random>
#include"InputManager.h"
const int SampleFs = 44100;
void SoundWave::Init() {
	voicePcm_.fs = SampleFs;
	voicePcm_.bits = 16;

	originalpcm_.fs = SampleFs;
	originalpcm_.bits = 16;
	originalpcm_.length = int(originalpcm_.fs);
	originalpcm_.sR.resize(originalpcm_.length);
	originalpcm_.sL.resize(originalpcm_.length);

	playbackPos_ = 0;
	isPlayBack_ = false;
	CreateOriginalWave(200);

	CreateWave();//波作成
	wave_write_16bit_stereo(&voicePcm_, "Wavename.wav");
	////書き出した音を読み込む
	voice_.handle = Novice::LoadAudio("./Wavename.wav");
}

void SoundWave::Update() {

	if (!voice_.isStart && InputManager::GetInstance()->GetIsTriggerKey(DIK_SPACE)) {
		playbackPos_ = 0;
		voice_.isStart = true;
		isPlayBack_ = true;
	}
	if (isPlayBack_) {
		playbackPos_ += (1280/ playbackTime_)/60;
	}
}

void SoundWave::Draw() {

	if (voice_.isStart) {
		Novice::PlayAudio(voice_.handle, false, 0.7f);
		voice_.isStart = false;
	}
	Novice::DrawBox(0, 0, 1280, 720, 0, BLACK, kFillModeSolid);
	WaveVisualize(voicePcm_, 200);
	Novice::DrawLine(int(playbackPos_), 0, int(playbackPos_), 720, RED);
}

void SoundWave::CreateWave() {

	std::string text = "aeiueoa"; // 発話させたいテキスト

	CreateSpeechVoice(voicePcm_, text);//音声作る

	synthePcm_.fs = SampleFs;
	synthePcm_.bits = 16;
	synthePcm_.length = int(voicePcm_.length);
	synthePcm_.sR.resize(synthePcm_.length);
	synthePcm_.sL.resize(synthePcm_.length);

	CreateSynthSound(synthePcm_, 440);

	Vocoder();
	wave_write_16bit_stereo(&pcm2_, "ex7_4kk.wav");

}

void SoundWave::WaveVisualize(const STEREO_PCM& stereopcm,const int& cut) {
	// 可視化のための座標取得
	int numPoint = stereopcm.length / cut; // 100分割
	std::vector <Vector2> waveR(numPoint);
	std::vector <Vector2> waveL(numPoint);
	int screenHeight = 720; // 画面の高さ（仮に720ピクセルとします）
	for (int i = 0; i < numPoint; i++) {
		waveR[i].x = float(i * 1280 / numPoint);
		waveR[i].y = float(screenHeight / 2 - stereopcm.sR[i * cut] * 200); // Y座標を中央にシフトし、スケーリングし、上下反転

		waveL[i].x = float(i * 1280 / numPoint);
		waveL[i].y = float(screenHeight / 2 - stereopcm.sL[i * cut] * 200); // Y座標を中央にシフトし、スケーリングし、上下反転

	}
	for (int i = 0; i < numPoint - 1; i++) {
		Novice::DrawLine((int)waveR[i].x, (int)waveR[i].y, (int)waveR[i + 1].x, (int)waveR[i + 1].y, WHITE);
		Novice::DrawLine((int)waveL[i].x, (int)waveL[i].y, (int)waveL[i + 1].x, (int)waveL[i + 1].y, WHITE);
	}
}

void SoundWave::CreateOriginalWave(double f0) {

	double t = 0.0;
	double tau = 0.4;  // 声門開大期
	double tan2 = 0.01;  // 声門閉大期
	double fs = originalpcm_.fs;
	double gain = 0.2; // ゲイン

	for (int n = 0; n < originalpcm_.length; ++n) {
		double phase = t * f0;
		double value;

		if (phase <= tau) {
			value = 0.5 * (1.0 - cos(2.0 * M_PI * phase / tau));
		}
		else if (phase <= 1.0) {
			value = 0.5 * (1.0 + cos(2.0 * M_PI * (phase - tau) / tan2));
		}
		else {
			value = 0.0;
		}
	 
		originalpcm_.sR[n] = gain * value;
		originalpcm_.sL[n] = gain * value;

		t += 1.0 / fs;
		if (t >= 1.0 / f0) {
			t -= 1.0 / f0;
		}
	}
	/*wave_read_16bit_stereo(&originalpcm_, "pulse_train.wav");*/
	f0;
}

void SoundWave::WaveFilter(STEREO_PCM& stereoPcm, const std::vector <double>& frequency, const double& bandwidth, const bool& isClear) {
	std::vector<double> aR(3), bR(3);
	std::vector<double> aL(3), bL(3);
	const int delayI = 2;
	const int delayJ = 2;
	std::vector<double> filterSR(stereoPcm.length, 0.0);
	std::vector<double> filterSL(stereoPcm.length, 0.0);
	if (isClear) {
		for (int n = 0; n < stereoPcm.length; ++n) {
			stereoPcm.sR[n] = 0;
			stereoPcm.sL[n] = 0;
			filterSR[n] = 0.0;
			filterSL[n] = 0.0;
		}
	}
	for (size_t i = 0; i < frequency.size(); ++i) {
		double fcLow = frequency[i] - bandwidth / 2.0;
		double fcHight = frequency[i] + bandwidth / 2.0;

		IIR_BPF(fcLow / originalpcm_.fs, fcHight / originalpcm_.fs, aR, bR); // IIRバンドパスフィルタ設計
		IIR_BPF(fcLow / originalpcm_.fs, fcHight / originalpcm_.fs, aL, bL); // IIRバンドパスフィルタ設計

		IIR_Filtering(originalpcm_.sR, filterSR, stereoPcm.length, aR, bR, delayI, delayJ); // フィルタリング
		IIR_Filtering(originalpcm_.sL, filterSL, stereoPcm.length, aL, bL, delayI, delayJ); // フィルタリング

		for (int n = 0; n < stereoPcm.length; ++n) {
			stereoPcm.sR[n] += filterSR[n];
			stereoPcm.sL[n] += filterSL[n];
			filterSR[n] = 0.0;
			filterSL[n] = 0.0;
		}
	}
}

void SoundWave::CreateSpeechVoice(STEREO_PCM& mosnoPcm, const std::string& text) {

	double fade_factor = 0.98; // ディエンファシスの減衰率

	std::string consonant = "";//子音
	std::string vowel = "";//母音

	// テキストから子音と母音の組み合わせをカウント
	int count = 0;
	for (char c : text) {
		if (isConsonant(c)) {
			consonant += c;
		}
		else if (isVowel(c)) {
			count++;
			consonant.clear();
		}
	}
	 totalLength_ = int(mosnoPcm.fs * pronunciationTime_ *count); // 合計の長さを計算
	 playbackTime_ = float(pronunciationTime_ * count);
	mosnoPcm.length = totalLength_;
	mosnoPcm.sR.resize(int(totalLength_), 0.0);
	mosnoPcm.sL.resize(int(totalLength_), 0.0);

	int current_position = 0; // 現在の位置を管理する変数

	int length = int(mosnoPcm.length / count);
	STEREO_PCM copyMonoPcm_;
	copyMonoPcm_.fs = mosnoPcm.fs;
	copyMonoPcm_.bits = mosnoPcm.bits;
	copyMonoPcm_.length = length;
	copyMonoPcm_.sR.resize(length);
	copyMonoPcm_.sL.resize(length);
	std::vector<double> vowelFreq(4);
	std::vector<double> consonantFreq(4);
	// 母音のフォルマントマップを初期化
	std::map<std::string, std::pair<std::vector<double>, double>> formantMap;
	formantMap["a"] = { {800, 1200, 2500, 3500}, 100.0 };  // あ
	formantMap["i"] = { {300, 2300, 2900, 3500}, 100.0 };    // い
	formantMap["u"] = { {300, 1200, 2500, 3500}, 100.0 };    // う
	formantMap["e"] = { {500, 1900, 2500, 3500}, 100.0 };    // え
	formantMap["o"] = { {500, 800, 2500, 3500}, 100.0 };     // お

	// 子音のフォルマントマップを初期化（仮の値）
	std::map<std::string, std::pair<std::vector<double>, double>> consonantMap;
	consonantMap["k"] = { {300, 1500, 2500, 3500}, 100.0 };  // か行
	consonantMap["s"] = { {500, 2000, 3000, 4000}, 100.0 };  // さ行
	consonantMap["t"] = { {600, 2200, 3200, 4200}, 100.0 };  // た行
	consonantMap["n"] = { {700, 2400, 3400, 4400}, 100.0 };  // な行

	// テキストを解析して音声を生成
	for (char c : text) {
		std::string current_char(1, c);

		// 子音と母音を区別して取得
		if (isConsonant(c)) {
			consonant += c;
		}
		else if (isVowel(c)) {
			vowel = current_char;

			if (consonant.empty() || consonantMap.find(consonant) != consonantMap.end()) {
			
				//フォルマントに声道の長さを反映
				for (int i = 0; i < vowelFreq.size(); i++) {
					vowelFreq[i] = formantMap[vowel].first[i] /(4*0.19);
				}
				double vowel_bandwidth = formantMap[vowel].second;

				std::vector<double> s(length, 0.0); // 仮のデータ。実際にはフォルマントを使用
				bool clearPCM = true;
				// 子音がある場合は、子音のフォルマントを適用
				if (!consonant.empty() && consonantMap.find(consonant) != consonantMap.end()) {
				
					//フォルマントに声道の長さを反映
					for (int i = 0; i < consonantFreq.size(); i++) {
						consonantFreq[i] = consonantMap[consonant].first[i] / (4 * 0.17);
					}
					double consonant_bandwidth = consonantMap[consonant].second;
					WaveFilter(copyMonoPcm_, consonantFreq, consonant_bandwidth,clearPCM);
					clearPCM = false;//子音の後の母音はクリアしない
				}

				// 母音のフォルマントを適用
				WaveFilter(copyMonoPcm_, vowelFreq, vowel_bandwidth, clearPCM);

				// ディエンファシス
				std::vector<double> sR(length, 0.0);
				std::vector<double> sL(length, 0.0);
				sR[0] = copyMonoPcm_.sR[0];
				sL[0] = copyMonoPcm_.sL[0];
				for (int n = 1; n < length; n++) {
					sR[n] = copyMonoPcm_.sR[n] + fade_factor * sR[n - 1];
					sL[n] = copyMonoPcm_.sL[n] + fade_factor * sL[n - 1];
				}
				//fade_factor;

				// フェード処理
				for (int n = 0; n < mosnoPcm.fs * 0.01; n++) {
					sR[n] *= (double)n / (mosnoPcm.fs * 0.01); // フェードイン
					sL[n] *= (double)n / (mosnoPcm.fs * 0.01); // フェードイン
					sR[length - n - 1] *= (double)n / (mosnoPcm.fs * 0.01); // フェードアウト
					sL[length - n - 1] *= (double)n / (mosnoPcm.fs * 0.01); // フェードアウト
				}

				// mosnoPcm の適切な位置に波形をコピー
				for (int n = 0; n < length; ++n) {
					mosnoPcm.sR[current_position + n] += sR[n];
					mosnoPcm.sL[current_position + n] += sL[n];
				}
				current_position += length; // 次の文字の位置を設定
			}

			consonant.clear(); // 子音をリセット
		}
	}

}
// 子音判定関数
bool SoundWave::isConsonant(char c) {
	std::string consonants = "kstnhmyrwgzdbp";
	return consonants.find(c) != std::string::npos;
}

// 母音判定関数
bool SoundWave::isVowel(char c) {
	std::string vowels = "aiueo";
	return vowels.find(c) != std::string::npos;
}

void SoundWave::Vocoder() {
	pcm2_.fs = SampleFs;
	pcm2_.bits = 16;
	pcm2_.length = int(voicePcm_.length);
	pcm2_.sR.resize(pcm2_.length);
	pcm2_.sL.resize(pcm2_.length);
	std::vector<double>ssR(voicePcm_.length);
	std::vector<double>ssL(voicePcm_.length);

	/* プリエンファシス処理 */

	int N = 1024; /* DFTのサイズ */

	std::vector<std::complex<double>>xR(N);
	std::vector<std::complex<double>>yR(N);
	std::vector<std::complex<double>>bR(N);

	std::vector<double>w(N);
	w = HanningWindow(N);//ハニング窓

	int numberOfFrame = (synthePcm_.length - N / 2) / (N / 2); /* フレームの数 */
	int bandWidth = 8;
	int numberOfBand = N / 2 / bandWidth;
	int offset;
	for (int frame = 0; frame < numberOfFrame; frame++) {
		offset = N / 2 * frame;//オフセット

		/* X(n) */
		for (int n = 0; n < N; n++)
		{
			xR[n].real(synthePcm_.sR[offset + n] * w[n]);
			xR[n].imag(0.0);

		}
		FFT(xR, N, false);


		/* B(k) */
		for (int n = 0; n < N; n++)
		{
			bR[n].real(voicePcm_.sR[offset + n] * w[n]);
			bR[n].imag(0.0);

		}
		FFT(bR, N, false);


		for (int k = 0; k < N; k++)
		{
			bR[k].real(sqrt(bR[k].real() * bR[k].real() + bR[k].imag() * bR[k].imag()));
			bR[k] = 0.0;
		}

		for (int band = 0; band < numberOfBand; band++)
		{
			offset = bandWidth * band;
			double	a = 0.0;

			for (int k = 0; k < bandWidth; k++)
			{
				a += bR[offset + k].real();

			}
			a /= bandWidth;

			for (int k = 0; k < bandWidth; k++)
			{
				bR[offset + k].real(a);

			}
		}
		bR[0].real(0.0);

		bR[N / 2].real(0.0);

		for (int k = 1; k < N / 2; k++)
		{
			bR[N - k].real(bR[k].real());

		}

		/* フィルタリング */
		for (int k = 0; k < N; k++)
		{
			yR[k] = xR[k] * bR[k];

		}
		FFT(yR, N, true);


		offset = N / 2 * frame;

		/* オーバーラップアド */
		for (int n = 0; n < N; n++)
		{
			pcm2_.sR[offset + n] += yR[n].real();
			pcm2_.sL[offset + n] += yR[n].real();
		}
	}
}

void SoundWave::CreateSynthSound(STEREO_PCM& output, double frequency) {
	
	double phase = 0.0;
	double deltaPhase = frequency / SampleFs;

	for (int i = 0; i < output.length; ++i) {
		double sineWave = sin(2.0 * M_PI * phase);
		double sawtoothWave = 2.0 * (phase - floor(phase + 0.5));

		output.sR[i] = static_cast<double>(0.5 * sineWave + 0.5 * sawtoothWave);
		output.sL[i] = static_cast<double>(0.5 * sineWave + 0.5 * sawtoothWave);

		phase += deltaPhase;
		if (phase > 1.0) {
			phase -= 1.0;
		}
	}
}