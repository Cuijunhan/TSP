#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>


namespace Greedy2 {
std::vector<std::pair<int, int>> readTspFile2Vectors(std::string filePath);


// 计算两个城市之间的距离（假设为欧几里得距离）
double distance(const std::pair<int, int>& city1, const std::pair<int, int>& city2);

// 插入新的城市使得路径代价最小
void insertCity(std::vector<int>& path, int city, const std::vector<std::pair<int, int>>& cities);

std::vector<int> cheapestInsertionTSP(const std::vector<std::pair<int, int>>& cities);

std::pair<std::vector<int>, double> Greedy2(std::string filePath);

double calculatePathCost(const std::vector<int>& path, const std::vector<std::pair<int, int>>& cities);


}