/**
 * @file DP.h
 * @brief 动态规划算法
 * @author junhan.cui (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<string>
#include<cmath>
#include <utility>
#include <algorithm>

// #include "include/algorithm.h"
#include "../common/common.h"
#include "../data/data.h"

#pragma once




std::pair<std::vector<int>, double> dpAlgorithm(std::vector<std::vector<double>> graph);