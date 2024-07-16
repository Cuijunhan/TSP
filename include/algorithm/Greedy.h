/**
 * @file Greedy.h  贪心算法
 * @author junhan.cui (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

#pragma once

std::vector<int> TSPGreedyAlgorithm(std::vector<std::vector<double>>& distance);

std::vector<int> TSPGreedyAlgorithm(std::string& filename);