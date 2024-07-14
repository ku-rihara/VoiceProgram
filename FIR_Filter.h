#pragma once
#include<vector>

double sinc(const double& x);

/// <summary>/// 
/// 低域通過フィルター
/// </summary>/// 
/// <param name="fe">周波数</param>/// 
/// <param name="遅延器の数"></param>/// 
/// <param name="w"></param>///
/// <returns></returns>
std::vector<double>FIR_LPF(const double& fe, const int& J, const std::vector<double>& w);

/// <summary>/// 
/// 高域通過フィルター
/// </summary>/// 
/// <param name="fe">周波数</param>/// 
/// <param name="遅延器の数"></param>/// 
/// <param name="w"></param>///
/// <returns></returns>
std::vector<double>FIR_HPF(const double& fe, const int& J, const std::vector<double>& w);

/// <summary>/// 
/// 帯域通過フィルター
/// </summary>/// 
/// <param name="fe">1通過させ始める周波数</param>/// 
/// /// <param name="fe">止める周波数</param>/// 
/// <param name="遅延器の数"></param>/// 
/// <param name="w"></param>///
/// <returns></returns>
std::vector<double>FIR_BPF(const double& fe1, const double& fe2, const int& J, const std::vector<double>& w);

/// <summary>/// 
/// 帯域阻止フィルター
/// </summary>/// 
/// <param name="fe">周波数1</param>/// 
/// /// <param name="fe">周波数2</param>/// 
/// <param name="遅延器の数"></param>/// 
/// <param name="w"></param>///
/// <returns></returns>
std::vector<double>FIR_BEF(const double& fe1, const double& fe2, const int& J, const std::vector<double>& w);
