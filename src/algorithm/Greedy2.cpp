#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>
#include "data/data.h"
#include "algorithm/Greedy2.h"
#include "common/common.h"



namespace Greedy2 {
std::vector<std::pair<int, int>> readTspFile2Vectors(std::string filePath) {
	std::vector<Node> nodes = readTSPFile(filePath);
      std::vector<std::pair<int, int>> cityXY;
	int numCity = nodes.size();
	cityXY = std::vector<std::pair<int, int>>(numCity, std::pair<int, int>(0, 0));
	for (int i = 0; i < numCity; i++) {
		cityXY[i].first = nodes[i].x;
		cityXY[i].second = nodes[i].y;
	}
	return cityXY;
}

      
// 计算两个城市之间的距离（假设为欧几里得距离）
double distance(const std::pair<int, int>& city1, const std::pair<int, int>& city2) {
    return sqrt(pow(city1.first - city2.first, 2) + pow(city1.second - city2.second, 2));
}


// 插入新的城市使得路径代价最小
void insertCity(std::vector<int>& path, int city, const std::vector<std::pair<int, int>>& cities) {
    double minCost = INT_MAX;
    int bestPos = -1;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        double cost = distance(cities[path[i]], cities[city]) + distance(cities[city], cities[path[i+1]]) - distance(cities[path[i]], cities[path[i+1]]);
        if (cost < minCost) {
            minCost = cost;
            bestPos = i + 1;
        }
    }
    path.insert(path.begin() + bestPos, city);
}

std::vector<int> cheapestInsertionTSP(const std::vector<std::pair<int, int>>& cities) {
    int n = cities.size();
    std::vector<int> path = {0, 1, 0}; // 初始化路径

    std::vector<bool> visited(n, false);
    visited[0] = visited[1] = true;

    for (int i = 2; i < n; ++i) {
        double minDist = INT_MAX;
        int nextCity = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j]) {
                double dist = INT_MAX;
                for (int k = 0; k < path.size() - 1; ++k) {
                    double currentDist = distance(cities[path[k]], cities[j]) + distance(cities[j], cities[path[k+1]]) - distance(cities[path[k]], cities[path[k+1]]);
                    if (currentDist < dist) {
                        dist = currentDist;
                    }
                }
                if (dist < minDist) {
                    minDist = dist;
                    nextCity = j;
                }
            }
        }
        insertCity(path, nextCity, cities);
        visited[nextCity] = true;
    }
    return path;
}

double calculatePathCost(const std::vector<int>& path, const std::vector<std::pair<int, int>>& cities) {
    double cost = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        cost += distance(cities[path[i]], cities[path[i+1]]);
    }
    cost += distance(cities[path[path.size()-1]], cities[path[0]]);
    return cost;
}



std::pair<std::vector<int>, double> Greedy2(std::string filePath) {
      std::vector<std::pair<int,int>> cities= readTspFile2Vectors(filePath);
      std::vector<int> path = cheapestInsertionTSP(cities);
//       std::cout << "贪心算法2得到的路径: ";
//     for (int city : path) {
//         std::cout << city << " ";
//     }
//     std::cout << std::endl;
      std::pair<std::vector<int>, double> result(path, calculatePathCost(path, cities));

      return result;
}


}