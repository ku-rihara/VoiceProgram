#pragma once
#include<Novice.h>
#include"wave.h"
#include "Vector2C.h"
#include<vector>
#include<complex>

struct Sound {
	int handle;
	int voiceHandle;
	bool isStart;
};

class SoundWave {
public:
	STEREO_PCM originalpcm_;
	STEREO_PCM voicePcm_;
	STEREO_PCM synthePcm_;
	STEREO_PCM pcm2_;
	int totalLength_;
	double pronunciationTime_ = 0.3;//発音時間
	float playbackPos_;
	float playbackTime_;
	Sound voice_;
	bool isPlayBack_;
	

public:
	void Init();
	void Update();
	void Draw();

	void CreateWave();
	//void Bogoda();
	void WaveVisualize(const STEREO_PCM& stereopcm, const int& cut);
	bool isConsonant(char c);
	bool isVowel(char c);

	void Vocoder();

	void CreateOriginalWave(double f0);
	void WaveFilter(STEREO_PCM& monoPcm_, const std::vector <double>& frequency, const double& bandwidth,const bool &isClear);
	void CreateSpeechVoice(STEREO_PCM& mosnoPcm, const std::string& text);
	void CreateSynthSound(STEREO_PCM& output, double frequency);

	std::vector<double>generateNoise(int length, double amplitude);
	void addConsonant(STEREO_PCM& pcm, const std::string& consonant, int start, int length, double amplitude);

};