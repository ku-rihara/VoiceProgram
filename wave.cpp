#include <iostream>
#include <fstream>
#include"wave.h"
using namespace std;

void wave_read_8bit_mono(MONO_PCM* pcm, const char* file_name)
{

	FILE* file;
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char file_format_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short wave_format_type;
	short channel;
	long samples_per_sec;
	long bytes_per_sec;
	short block_size;
	short bits_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	unsigned char data;
	int n;
	if (fopen_s(&file, file_name, "rb") != 0) {
		return;
	}
	// WAVファイルのヘッダ情報を読み込む
	fread(riff_chunk_ID, 1, 4, file);
	fread(&riff_chunk_size, 4, 1, file);
	fread(file_format_type, 1, 4, file);
	fread(fmt_chunk_ID, 1, 4, file);
	fread(&fmt_chunk_size, 4, 1, file);
	fread(&wave_format_type, 2, 1, file);
	fread(&channel, 2, 1, file);
	fread(&samples_per_sec, 4, 1, file);
	fread(&bytes_per_sec, 4, 1, file);
	fread(&block_size, 2, 1, file);
	fread(&bits_per_sample, 2, 1, file);
	fread(data_chunk_ID, 1, 4, file);
	fread(&data_chunk_size, 4, 1, file);

	pcm->fs = samples_per_sec; /* 標本化周波数 */
	pcm->bits = bits_per_sample; /* 量子化精度 */
	pcm->length = data_chunk_size; /* 音データの長さ */
	pcm->s.resize(pcm->length); /* メモリの確保 */

	// 音データを読み込む
	for (n = 0; n < pcm->length; n++)
	{
		fread(&data, 2, 1, file); /* 音データの読み取り */
		pcm->s[n] = ((double)data - 128.0) / 128.0; /* 音データを-1以上1未満の範囲に正規化する */
	}

	fclose(file);
}

void wave_write_8bit_mono(MONO_PCM* pcm, const char* file_name)
{
	FILE* file;

	char riff_chunk_ID[4] = { 'R', 'I', 'F', 'F' };
	long riff_chunk_size = 36 + pcm->length;
	char file_format_type[4] = { 'W', 'A', 'V', 'E' };

	char fmt_chunk_ID[4] = { 'f', 'm', 't', ' ' };
	long fmt_chunk_size = 16;
	short wave_format_type = 1;
	short channel = 1;
	long samples_per_sec = pcm->fs; /* 標本化周波数 */
	long bytes_per_sec = pcm->fs * pcm->bits / 8;
	short block_size = short(pcm->bits / 8);
	short bits_per_sample = short(pcm->bits); /* 量子化精度 */

	char data_chunk_ID[4] = { 'd', 'a', 't', 'a' };
	long data_chunk_size = pcm->length;

	if (fopen_s(&file, file_name, "wb") != 0) {
		return;
	}

	// WAVファイルのヘッダ情報を書き込む
	fwrite(riff_chunk_ID, 1, 4, file);
	fwrite(&riff_chunk_size, 4, 1, file);
	fwrite(file_format_type, 1, 4, file);
	fwrite(fmt_chunk_ID, 1, 4, file);
	fwrite(&fmt_chunk_size, 4, 1, file);
	fwrite(&wave_format_type, 2, 1, file);
	fwrite(&channel, 2, 1, file);
	fwrite(&samples_per_sec, 4, 1, file);
	fwrite(&bytes_per_sec, 4, 1, file);
	fwrite(&block_size, 2, 1, file);
	fwrite(&bits_per_sample, 2, 1, file);
	fwrite(data_chunk_ID, 1, 4, file);
	fwrite(&data_chunk_size, 4, 1, file);


	// 音データを書き込む
	for (int n = 0; n < pcm->length; n++)
	{
		double s = (pcm->s[n] + 1.0) / 2.0 * 256.0;

		if (s > 255.0)
		{
			s = 255.0; /* クリッピング */
		}
		else if (s < 0.0)
		{
			s = 0.0; /* クリッピング */
		}

		unsigned char data = static_cast<unsigned char>(round(s)); /* 四捨五入 */
		fwrite(&data, 2, 1, file); /* 音データの書き出し */
	}

	if ((pcm->length % 2) == 1) /* 音データの長さが奇数のとき */
	{
		unsigned char data = 0;
		fwrite(&data, 2, 1, file); /* 0パディング */
	}
	fclose(file);
}


void wave_read_8bit_stereo(STEREO_PCM* pcm, const char* file_name)
{
	FILE* file;
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char file_format_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short wave_format_type;
	short channel;
	long samples_per_sec;
	long bytes_per_sec;
	short block_size;
	short bits_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	unsigned char data;
	int n;
	if (fopen_s(&file, file_name, "rb") != 0) {
		return;
	}

	// WAVファイルのヘッダ情報を読み込む
	fread(riff_chunk_ID, 1, 4, file);
	fread(&riff_chunk_size, 4, 1, file);
	fread(file_format_type, 1, 4, file);
	fread(fmt_chunk_ID, 1, 4, file);
	fread(&fmt_chunk_size, 4, 1, file);
	fread(&wave_format_type, 2, 1, file);
	fread(&channel, 2, 1, file);
	fread(&samples_per_sec, 4, 1, file);
	fread(&bytes_per_sec, 4, 1, file);
	fread(&block_size, 2, 1, file);
	fread(&bits_per_sample, 2, 1, file);
	fread(data_chunk_ID, 1, 4, file);
	fread(&data_chunk_size, 4, 1, file);


	pcm->fs = samples_per_sec; /* 標本化周波数 */
	pcm->bits = bits_per_sample; /* 量子化精度 */
	pcm->length = data_chunk_size / 2; /* 音データの長さ */
	pcm->sL.resize(pcm->length); /* メモリの確保 */
	pcm->sR.resize(pcm->length); /* メモリの確保 */

	// 音データを読み込む
	for (n = 0; n < pcm->length; n++)
	{
		fread(&data, 2, 1, file); /* 音データ（Lチャンネル）の読み取り */
		pcm->sL[n] = ((double)data - 128.0) / 128.0; /* 音データを-1以上1未満の範囲に正規化する */

		fread(&data, 2, 1, file); /* 音データ（Rチャンネル）の読み取り */
		pcm->sR[n] = ((double)data - 128.0) / 128.0; /* 音データを-1以上1未満の範囲に正規化する */
	}

	fclose(file);
}

void wave_write_8bit_stereo(STEREO_PCM* pcm, const char* file_name)
{
	FILE* file;
	char riff_chunk_ID[4] = { 'R', 'I', 'F', 'F' };
	long riff_chunk_size = 36 + pcm->length * 2;
	char file_format_type[4] = { 'W', 'A', 'V', 'E' };

	char fmt_chunk_ID[4] = { 'f', 'm', 't', ' ' };
	long fmt_chunk_size = 16;
	short wave_format_type = 1;
	short channel = 2;
	long samples_per_sec = pcm->fs; /* 標本化周波数 */
	long bytes_per_sec = pcm->fs * pcm->bits / 8 * 2;
	short block_size = short(pcm->bits / 8 * 2);
	short bits_per_sample = short(pcm->bits); /* 量子化精度 */

	char data_chunk_ID[4] = { 'd', 'a', 't', 'a' };
	long data_chunk_size = pcm->length * 2;

	if (fopen_s(&file, file_name, "wb") != 0) {
		return;
	}
	// WAVファイルのヘッダ情報を書き込む
	fwrite(riff_chunk_ID, 1, 4, file);
	fwrite(&riff_chunk_size, 4, 1, file);
	fwrite(file_format_type, 1, 4, file);
	fwrite(fmt_chunk_ID, 1, 4, file);
	fwrite(&fmt_chunk_size, 4, 1, file);
	fwrite(&wave_format_type, 2, 1, file);
	fwrite(&channel, 2, 1, file);
	fwrite(&samples_per_sec, 4, 1, file);
	fwrite(&bytes_per_sec, 4, 1, file);
	fwrite(&block_size, 2, 1, file);
	fwrite(&bits_per_sample, 2, 1, file);
	fwrite(data_chunk_ID, 1, 4, file);
	fwrite(&data_chunk_size, 4, 1, file);

	// 音データを書き込む
	for (int n = 0; n < pcm->length; n++)
	{
		double sL = (pcm->sL[n] + 1.0) / 2.0 * 256.0;

		if (sL > 255.0)
		{
			sL = 255.0; /* クリッピング */
		}
		else if (sL < 0.0)
		{
			sL = 0.0; /* クリッピング */
		}

		unsigned char data = static_cast<unsigned char>(round(sL)); /* 四捨五入 */
		fwrite(&data, 2, 1, file); /* 音データ（Lチャンネル）の書き出し */

		double sR = (pcm->sR[n] + 1.0) / 2.0 * 256.0;

		if (sR > 255.0)
		{
			sR = 255.0; /* クリッピング */
		}
		else if (sR < 0.0)
		{
			sR = 0.0; /* クリッピング */
		}

		data = static_cast<unsigned char>(round(sR)); /* 四捨五入 */
		fwrite(&data, 2, 1, file); /* 音データ（Rチャンネル）の書き出し */
	}

	fclose(file);
}

void wave_read_16bit_mono(MONO_PCM* pcm, const char* file_name)
{
	FILE* file;
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char file_format_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short wave_format_type;
	short channel;
	long samples_per_sec;
	long bytes_per_sec;
	short block_size;
	short bits_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	short data;
	int n;

	if (fopen_s(&file, file_name, "rb") != 0) {
		return;
	}

	fread(riff_chunk_ID, 1, 4, file);
	fread(&riff_chunk_size, 4, 1, file);
	fread(file_format_type, 1, 4, file);
	fread(fmt_chunk_ID, 1, 4, file);
	fread(&fmt_chunk_size, 4, 1, file);
	fread(&wave_format_type, 2, 1, file);
	fread(&channel, 2, 1, file);
	fread(&samples_per_sec, 4, 1, file);
	fread(&bytes_per_sec, 4, 1, file);
	fread(&block_size, 2, 1, file);
	fread(&bits_per_sample, 2, 1, file);
	fread(data_chunk_ID, 1, 4, file);
	fread(&data_chunk_size, 4, 1, file);

	pcm->fs = samples_per_sec; /* 標本化周波数 */
	pcm->bits = bits_per_sample; /* 量子化精度 */
	pcm->length = data_chunk_size / 2; /* 音データの長さ */
	pcm->s.resize(pcm->length); /* メモリの確保 */

	for (n = 0; n < pcm->length; n++)
	{
		fread(&data, 2, 1, file); /* 音データの読み取り */
		pcm->s[n] = (double)data / 32768.0; /* 音データを-1以上1未満の範囲に正規化する */
	}

	fclose(file);
}

void wave_write_16bit_mono(MONO_PCM* pcm, const char* file_name)
{
	FILE* file;
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char file_format_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short wave_format_type;
	short channel;
	long samples_per_sec;
	long bytes_per_sec;
	short block_size;
	short bits_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	double s;
	short data;
	int n;

	riff_chunk_ID[0] = 'R';
	riff_chunk_ID[1] = 'I';
	riff_chunk_ID[2] = 'F';
	riff_chunk_ID[3] = 'F';
	riff_chunk_size = 36 + pcm->length * 2;
	file_format_type[0] = 'W';
	file_format_type[1] = 'A';
	file_format_type[2] = 'V';
	file_format_type[3] = 'E';

	fmt_chunk_ID[0] = 'f';
	fmt_chunk_ID[1] = 'm';
	fmt_chunk_ID[2] = 't';
	fmt_chunk_ID[3] = ' ';
	fmt_chunk_size = 16;
	wave_format_type = 1;
	channel = 1;
	samples_per_sec = pcm->fs; /* 標本化周波数 */
	bytes_per_sec = pcm->fs * pcm->bits / 8;
	block_size = short(pcm->bits / 8);
	bits_per_sample = short(pcm->bits); /* 量子化精度 */

	data_chunk_ID[0] = 'd';
	data_chunk_ID[1] = 'a';
	data_chunk_ID[2] = 't';
	data_chunk_ID[3] = 'a';
	data_chunk_size = pcm->length * 2;

	if (fopen_s(&file, file_name, "wb") != 0) {
		return;
	}

	fwrite(riff_chunk_ID, 1, 4, file);
	fwrite(&riff_chunk_size, 4, 1, file);
	fwrite(file_format_type, 1, 4, file);
	fwrite(fmt_chunk_ID, 1, 4, file);
	fwrite(&fmt_chunk_size, 4, 1, file);
	fwrite(&wave_format_type, 2, 1, file);
	fwrite(&channel, 2, 1, file);
	fwrite(&samples_per_sec, 4, 1, file);
	fwrite(&bytes_per_sec, 4, 1, file);
	fwrite(&block_size, 2, 1, file);
	fwrite(&bits_per_sample, 2, 1, file);
	fwrite(data_chunk_ID, 1, 4, file);
	fwrite(&data_chunk_size, 4, 1, file);

	for (n = 0; n < pcm->length; n++)
	{
		s = (pcm->s[n] + 1.0) / 2.0 * 65536.0;

		if (s > 65535.0)
		{
			s = 65535.0; /* クリッピング */
		}
		else if (s < 0.0)
		{
			s = 0.0; /* クリッピング */
		}

		data = (short)((int)(s + 0.5) - 32768); /* 四捨五入とオフセットの調節 */
		fwrite(&data, 2, 1, file); /* 音データの書き出し */
	}

	fclose(file);
}


void wave_read_16bit_stereo(STEREO_PCM* pcm, const char* file_name)
{
	FILE* file;
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char file_format_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short wave_format_type;
	short channel;
	long samples_per_sec;
	long bytes_per_sec;
	short block_size;
	short bits_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	short data;
	int n;
	if (fopen_s(&file, file_name, "rb") != 0) {
		return;
	}
	fread(riff_chunk_ID, 1, 4, file);
	fread(&riff_chunk_size, 4, 1, file);
	fread(file_format_type, 1, 4, file);
	fread(fmt_chunk_ID, 1, 4, file);
	fread(&fmt_chunk_size, 4, 1, file);
	fread(&wave_format_type, 2, 1, file);
	fread(&channel, 2, 1, file);
	fread(&samples_per_sec, 4, 1, file);
	fread(&bytes_per_sec, 4, 1, file);
	fread(&block_size, 2, 1, file);
	fread(&bits_per_sample, 2, 1, file);
	fread(data_chunk_ID, 1, 4, file);
	fread(&data_chunk_size, 4, 1, file);

	pcm->fs = samples_per_sec; /* 標本化周波数 */
	pcm->bits = bits_per_sample; /* 量子化精度 */
	pcm->length = data_chunk_size / 4; /* 音データの長さ */
	pcm->sL.resize(pcm->length);
	pcm->sR.resize(pcm->length);

	for (n = 0; n < pcm->length; n++)
	{
		fread(&data, 2, 1, file);/* 音データ（Lチャンネル）の読み取り */
		pcm->sL[n] = (double)data / 32768.0; /* 音データを-1以上1未満の範囲に正規化する */

		fread(&data, 2, 1, file);/* 音データ（Rチャンネル）の読み取り */
		pcm->sR[n] = (double)data / 32768.0; /* 音データを-1以上1未満の範囲に正規化する */
	}

	fclose(file);
}

void wave_write_16bit_stereo(STEREO_PCM* pcm, const char* file_name)
{
	FILE* file;
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char file_format_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short wave_format_type;
	short channel;
	long samples_per_sec;
	long bytes_per_sec;
	short block_size;
	short bits_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	double sL;
	double sR;
	short data;
	int n;
	if (fopen_s(&file, file_name, "wb") != 0) {
		return;
	}

	riff_chunk_ID[0] = 'R';
	riff_chunk_ID[1] = 'I';
	riff_chunk_ID[2] = 'F';
	riff_chunk_ID[3] = 'F';
	riff_chunk_size = 36 + pcm->length * 4;
	file_format_type[0] = 'W';
	file_format_type[1] = 'A';
	file_format_type[2] = 'V';
	file_format_type[3] = 'E';

	fmt_chunk_ID[0] = 'f';
	fmt_chunk_ID[1] = 'm';
	fmt_chunk_ID[2] = 't';
	fmt_chunk_ID[3] = ' ';
	fmt_chunk_size = 16;
	wave_format_type = 1;
	channel = 2;
	samples_per_sec = pcm->fs; /* 標本化周波数 */
	bytes_per_sec = pcm->fs * pcm->bits / 8 * 2;
	block_size = short(pcm->bits / 8 * 2);
	bits_per_sample = short(pcm->bits); /* 量子化精度 */

	data_chunk_ID[0] = 'd';
	data_chunk_ID[1] = 'a';
	data_chunk_ID[2] = 't';
	data_chunk_ID[3] = 'a';
	data_chunk_size = pcm->length * 4;

	fwrite(riff_chunk_ID, 1, 4, file);
	fwrite(&riff_chunk_size, 4, 1, file);
	fwrite(file_format_type, 1, 4, file);
	fwrite(fmt_chunk_ID, 1, 4, file);
	fwrite(&fmt_chunk_size, 4, 1, file);
	fwrite(&wave_format_type, 2, 1, file);
	fwrite(&channel, 2, 1, file);
	fwrite(&samples_per_sec, 4, 1, file);
	fwrite(&bytes_per_sec, 4, 1, file);
	fwrite(&block_size, 2, 1, file);
	fwrite(&bits_per_sample, 2, 1, file);
	fwrite(data_chunk_ID, 1, 4, file);
	fwrite(&data_chunk_size, 4, 1, file);

	for (n = 0; n < pcm->length; n++)
	{
		sL = (pcm->sL[n] + 1.0) / 2.0 * 65536.0;

		if (sL > 65535.0)
		{
			sL = 65535.0; /* クリッピング */
		}
		else if (sL < 0.0)
		{
			sL = 0.0; /* クリッピング */
		}

		data = (short)((int)(sL + 0.5) - 32768); /* 四捨五入とオフセットの調節 */
		fwrite(&data, 2, 1, file); /* 音データ（Lチャンネル）の書き出し */

		sR = (pcm->sR[n] + 1.0) / 2.0 * 65536.0;

		if (sR > 65535.0)
		{
			sR = 65535.0; /* クリッピング */
		}
		else if (sR < 0.0)
		{
			sR = 0.0; /* クリッピング */
		}

		data = (short)((int)(sR + 0.5) - 32768); /* 四捨五入とオフセットの調節 */
		fwrite(&data, 2, 1, file); /* 音データ（Rチャンネル）の書き出し */
	}

	fclose(file);
}

void SineWave_Mono(MONO_PCM* pcm, double f0, double a, int ofset, int duration) {
	int n;//時間
	double* s;//音データ

	s = new double[duration];
	//サイン波
	for (n = 0; n < duration; n++) {
		s[n] = a * sin(2.0f * M_PI * f0 * n / pcm->fs);
	}
	//フェード処理
	for (n = 0; n < pcm->fs * 0.01; n++) {
		s[n] *= (double)n / (pcm->fs * 0.01);
		s[duration - n - 1] *= (double)n / (pcm->fs * 0.01);
	}
	for (n = 0; n < duration; n++) {
		pcm->s[ofset + n] += s[n];
	}
	free(s);
}

