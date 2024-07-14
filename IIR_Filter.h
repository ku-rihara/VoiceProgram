#pragma once
#include<vector>

/// <summary>/// 
/// 
/// </summary>/// 
/// <param name="遮断周波数"></param>/// 
/// <param name="Q(クオリティファクタ)"></param>/// 
/// <param name="a"></param>///
/// <param name="b"></param>///
/// <returns></returns>
void IIR_LPF(const double& fc, const double& Q,  std::vector<double>& a,  std::vector<double>& b);

//// <summary>/// 
/// 
/// </summary>/// 
/// <param name="遮断周波数"></param>/// 
/// <param name="Q(クオリティファクタ)"></param>/// 
/// <param name="a"></param>///
/// <param name="b"></param>///
/// <returns></returns>
void IIR_HPF(const double& fc, const double& Q, std::vector<double>& a, std::vector<double>& b);


//// <summary>/// 
/// 
/// </summary>/// 
/// <param name="遮断周波数(低い)"></param>/// 
/// <param name="遮断周波数(高い)"></param>/// 
/// <param name="a"></param>///
/// <param name="b"></param>///
/// <returns></returns>
void IIR_BPF(const double& fcLow, const double& fcHight, std::vector<double>& a, std::vector<double>& b);

/// <summary>
/// 
/// </summary>
/// <param name="fc"></param>
/// <param name="doubleQ"></param>
/// <param name="a"></param>
/// <param name="b"></param>
void IIR_resonator(const double&fc,const double& Q, std::vector<double>& a, std::vector<double>& b);

//// <summary>/// 
/// 
/// </summary>/// 
/// <param name="元の音データ"></param>/// 
/// <param name="フィルタリングする音データ"></param>/// 
/// <param name=""></param>///
/// <param name=""></param>///
///  <param name="音データの長さ"></param>///
///  <param name="遅延器の数I"></param>///
///   <param name="遅延器の数J"></param>///
/// <returns></returns>
void IIR_Filtering(const std::vector <double>& originalS, std::vector <double>& filterS, const int& Lenght, const std::vector <double>& a, const std::vector <double>& b, const int& I, const int& J);
