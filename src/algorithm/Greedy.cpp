#include "algorithm/Greedy.h"
#include <iostream>
#include "data/data.h"
#include "common/common.h"
#include <exception>
#include <assert.h>


std::vector<int> TSPGreedyAlgorithm(std::vector<std::vector<double>>& distance)
{
      std::vector<int> path;
	//总路程
	int totalDistance = 0;		
	//默认从 0 开始遍历
	int current = 0;	
      path.push_back(current);
      int N = distance.size();
	//标识城市是否被访问,访问过置为 1
      std::vector<bool> visit(N, false);
	// bool visit[N] = { false };
	visit[0] = 1;
	// printf("TSP 路径为：%d ->", 1);

	//遍历 N - 1 次
	for (int i = 1; i < N; i++)
	{
		//设置较大的距离初始值用来选取最近邻
		int min_distance = 0x7fffffff;
		//保存当前最近邻城市
		int temp;
		//循环选取城市
		for (int j = 1; j < N; j++)
		{
			if (!visit[j] && distance[current][j] < min_distance)
			{
				min_distance = distance[current][j];
				temp = j;
			}
		}
		visit[temp] = 1;
		current = temp;
		totalDistance += min_distance;
            path.push_back(temp);
		// printf(" %d ->", temp + 1);
	}
	totalDistance += distance[current][0];
	// printf(" %d\n", 1);
	// printf("TSP 总距离为：%d\n", totalDistance);

      assert(path.size()==distance[0].size());

      return path;
}


std::vector<int> TSPGreedyAlgorithm(std::string& filename){
	std::vector<int> path;

	int N = getCityNumber(filename);
	std::vector<std::vector<double>> distance(N, std::vector<double>(N));
	std::vector<Node> nodes;
	//读取tsp文件，返回城市坐标
	nodes = readTSPFile(filename);
	assert(N==nodes.size());
	//计算城市之间的距离
	distance = calculateDistanceMatrix(nodes);
	//执行算法
	path = TSPGreedyAlgorithm(distance);
	// std::cout << "贪心算法1得到的路径: ";
	// for (int city : path) {
	// 	std::cout << city << " ";
	// }
	// std::cout << std::endl;

	return path;
}
