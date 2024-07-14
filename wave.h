#pragma once

#include <cmath>
#include<vector>


const double M_PI = 3.141592653589793;

struct MONO_PCM
{
	int fs; /* 標本化周波数 */
	int bits; /* 量子化精度 */
	int length; /* 音データの長さ */
	std::vector<double> s; /* 音データ */
};

struct STEREO_PCM
{
	int fs; /* 標本化周波数 */
	int bits; /* 量子化精度 */
	int length; /* 音データの長さ */
	std::vector<double> sL; /* 音データ（Lチャンネル） */
	std::vector<double> sR; /* 音データ（Rチャンネル） */
};

void wave_read_8bit_mono(MONO_PCM* pcm, const char* file_name);

void wave_write_8bit_mono(MONO_PCM* pcm, const char* file_name);

void wave_read_8bit_stereo(STEREO_PCM* pcm, const char* file_name);

void wave_write_8bit_stereo(STEREO_PCM* pcm, const char* file_name);

void wave_read_16bit_mono(MONO_PCM* pcm, const char* file_name);

void wave_write_16bit_mono(MONO_PCM* pcm, const char* file_name);

void wave_read_16bit_stereo(STEREO_PCM* pcm, const char* file_name);

void wave_write_16bit_stereo(STEREO_PCM* pcm, const char* file_name);

/// <summary>
/// サイン波
/// </summary>
/// <param name="モノラルPCM"></param>
/// <param name="周波数"></param>
/// <param name="振幅"></param>
/// <param name="音の開始位置"></param>
/// <param name="音を鳴らす時間"></param>
void SineWave_Mono(MONO_PCM* pcm, double f0, double a, int ofset, int duration);

