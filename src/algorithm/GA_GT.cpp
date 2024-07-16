// 解决TSP问题的重构算法（主要是tsp0的代码风格太丑陋了，修改成C++风格）
#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<string>
#include<cmath>
// #include "include/algorithm.h"
#include "../../include/common/common.h"
#include "../../include/data/data.h"
#include "algorithm/GA_GT.h"
#include "algorithm/Greedy.h"

#include <thread>   // 包含 std::this_thread::sleep_for
#include <chrono>   // 包含 std::chrono::seconds
using namespace std;

// 计算种群中每个个体的适应度
void GA_GT::calculateAdaptability() {
	// 计算每个个体的适应度
	for (int i = 0; i < numColony; i++) {
		double sum = 0;
		for (int j = 0; j < numCity; j++) {
			sum += cityDis[colony[i][j]][colony[i][(j + 1) % numCity]];
		}
		individualAdaptability[i] = sum;
	}
}

// 初始化
void GA_GT::init(string filePath) {
	readTspFile(filePath);
	
	// 根据tsp数据，初始化相关数据
	calculateData();
}

// 进行迭代计算
void GA_GT::evolution() {

	std::vector<double> bestAdaptability_list;
	for (int curGen = 0; curGen < maxGen; curGen++) { // 迭代maxGen次
		for (int i = 0; i < numColony; i++) { // 遍历种群中所有个体
			vector<int> path = colony[i]; // 用于存放变异后的路径

			int posC1 = rand() % numCity; // 随机生成变异点1（在path中的位置）
			int posC2 = rand() % numCity; // 随机生成变异点2（在path中的位置）

			int C1, C2; // 变异点1和变异点2对应的城市编号
			C1 = path[posC1]; // 获取变异点1对应的城市

			int j = rand() % numColony;   // 用于外变异的另一个 与 i个体 不同的个体

			int pos_flag = 0; // 用于标记变异过的点的数量

			double distanceChange = 0; // 用于记录距离变化

			while (true)
			{
				// 以 probabilityMutation (default = 0.02)的概率进行内变异
				if (rand() / 32768.0 < probabilityMutation) {
					posC2 = rand() % numCity;
					while (posC1 == posC2) { // 如果两个变异点相同，则重新生成
						posC2 = rand() % numCity;
					}
					C2 = colony[i][posC2]; // 获取变异点1对应的城市
				}
				else { // 进行外变异（交叉）
					j = rand() % numColony;
					while (i == j) { // 如果两个个体相同，则重新生成
						j = rand() % numColony;
					}
					// 获取个体 j 中 变异点1 对应城市的位置
					int pos = position(colony[j], path[posC1]);
					C2 = colony[j][(pos + 1) % numCity]; // 获取变异点2对应的城市
					posC2 = position(path, C2); // 获取变异点2在个体 i 中的位置(即变异点2对应的城市在个体 i 中的位置
				}

				// 如果两个变异点相邻，continue
				if ((posC1 + 1) % numCity == posC2 || (posC1 - 1 + numCity) % numCity == posC2)break;
				//if (abs(posC1 - posC2) == 1 || abs(posC1 - posC2) == numCity - 1) {
				//	continue;
				//}

				// 否则进行倒位操作
				int C1_left = path[posC1]; // 变异点1左边的城市
				int C1_right = path[(posC1 + 1) % numCity]; // 变异点1右边的城市

				int C2_left = path[posC2]; // 变异点2左边的城市
				int C2_right = path[(posC2 + 1) % numCity]; // 变异点2右边的城市

				// 计算倒位后的路径长度
				distanceChange += cityDis[C1_left][C2_left] + cityDis[C1_right][C2_right]
					- cityDis[C1_left][C1_right] - cityDis[C2_left][C2_right];
				
				invert(path, posC1, posC2); // 倒位操作

				pos_flag++; // 变异点数量加一
				if (pos_flag >= numCity)break;

				posC1++; // 变异点1的位置加一
				if (posC1 >= numCity) posC1 = 0; // 如果变异点1的位置超过了numCity，则变异点1的位置为0
			}

			// 更新子个体的适应度
			individualAdaptability[numColony + i] = individualAdaptability[i] + distanceChange;
			distanceChange = 0;
			// 记录 产生的 子个体
			for (int j = 0; j < numCity; j++) {
				colony[numColony + i][j] = path[j];
			}
		}

		// 一轮迭代之后进行选择
		selection();

		bestIndividual = colony[0]; // 更新最优个体
		bestAdaptability = individualAdaptability[0]; // 更新最优个体的适应度
		bestAdaptability_list.push_back(bestAdaptability);
		for (int i = 1; i < numColony; i++) {
			if (individualAdaptability[i] < bestAdaptability) {
				bestIndividual = colony[i];
				bestAdaptability = individualAdaptability[i];
			}
		}

		cout << "第" << curGen << "代的最优个体适应度为：" << bestAdaptability << endl;
		// cout << curGen << ":" << bestAdaptability << endl;

		if(is_vision){
			// std::vector<std::vector<double>> cityXY = getCityXY();
			static sf::RenderWindow window(sf::VideoMode(1500, 1500), "TSP-GT");
			visionTSP(window,cityXY,bestIndividual );
		}

		// 创建 outfile.txt 文件
		ofstream outfile("outfile.txt", ios::app);

		// 每 2000 代将最优个体的适应度写入文件
		if ((curGen + 1) % 2000 == 0) {
			outfile << curGen << ":" << bestAdaptability << endl;
		}

		// 关闭文件
		outfile.close();
	}
	if(save_data_path == "/home/"){
		std::cout<<RED<<"未设置保存路径"<<RESET<<std::endl;
	}else{
		save_data_path += (is_using_greedy)?
			"-ga-gt-greedy.txt":
			"-ga-gt.txt";
		saveDistData(bestAdaptability_list, save_data_path);
	}
}

// 获取城市在路径中的位置
int GA_GT::position(vector<int>& path, int city) {
	for (int i = 0; i < numCity; i++) {
		if (path[i] == city) {
			return i;
		}
	}
	return -1;
}

void GA_GT::invert(vector<int>& path, int pos1, int pos2) {
	// 如果pos1在pos2的左边，为一段
	if (pos1 < pos2) {
		for (int i = pos1 + 1, j = pos2; i < j; i++, j--) {
			swap(path[i], path[j]);
		}
	}
	// 如果pos1在pos2的右边，为两段
	else {
		// 右边的段 <= 左边的段
		if (numCity - 1 - pos1 <= pos2 + 1) {
			int i, j;
			for (i = pos2 + 1, j = pos1; i <= numCity - 1; i++, j--) {
				swap(path[i], path[j]);
			}
			for (i = 0; i < j; i++, j--) {
				swap(path[i], path[j]);
			}
		}
		// 右边的段 > 左边的段
		else {
			int i, j;
			for (i = pos2 + 1, j = pos1; j >= 0; i++, j--) {
				swap(path[i], path[j]);
			}
			for (j = numCity - 1; i < j; i++, j--) {
				swap(path[i], path[j]);
			}
		}
	}
}

// 在父代和子代中进行一个锦标赛选择
void GA_GT::selection() {
	for (int i = 0; i < numColony; i++) {
		if (individualAdaptability[i] > individualAdaptability[numColony + i]) {
			individualAdaptability[i] = individualAdaptability[numColony + i];
			for (int j = 0; j < numCity; j++) {
				colony[i][j] = colony[numColony + i][j];
			}
		}
	}
}

bool GA_GT::readTspFile(string filePath) {
	std::vector<Node> nodes = readTSPFile(filePath);
	numCity = nodes.size();
	cityXY = vector<vector<double>>(numCity, vector<double>(2));
	for (int i = 0; i < numCity; i++) {
		cityXY[i][0] = nodes[i].x;
		cityXY[i][1] = nodes[i].y;
	}
	return true;
}

// 根据tsp数据计算城市之间的距离、并随机初始化种群、同时计算适应度
void GA_GT::calculateData() {
	// 初始化cityDis
	cityDis = vector<vector<double>>(numCity, vector<double>(numCity));
	// 计算城市间距离
	for (int i = 0; i < numCity; i++) {
		for (int j = 0; j < numCity; j++) {
			cityDis[i][j] = sqrt(pow(cityXY[i][0] - cityXY[j][0], 2) + pow(cityXY[i][1] - cityXY[j][1], 2));
		}
	}

	// 初始化colony （包括父代和子代）
	colony = vector<vector<int>>(2 * numColony, vector<int>(numCity));
	// 以时间为种子，随机生成种群
	srand((unsigned)time(NULL));

	// 建立一个用于随机生成种群的数组
	vector<int> tmp(numCity);
	for (int i = 0; i < numCity; i++) {
		tmp[i] = i;
	}
	// 随机初始化种群
	for (int i = 0; i < numColony; i++) {
		int numNeedToRand = numCity;	// 当前需要随机的次数
		for (int j = 0; j < numCity; j++) {
			int randIndex = rand() % numNeedToRand; // 随机生成下标
			colony[i][j] = tmp[randIndex]; // 将随机生成的下标对应的值赋给种群
			swap(tmp[randIndex], tmp[numNeedToRand - 1]); // 将已经随机过的下标与最后一个下标交换
			numNeedToRand--; // 需要随机的次数减一
		}
	}


	//自己改进部分
	if(is_using_greedy){
		std::cout<<GREEN<<"使用贪心算法初始化种群"<<RESET<<std::endl;
		std::vector<int> first_pupolation = TSPGreedyAlgorithm(cityDis);
		std::cout<<"first_pupolation.size: "<<first_pupolation.size()<<std::endl;
		for (int i = 0; i < numColony/2; i++) {
			for (int j = 0; j < numCity; j++) {
				colony[i][j] = first_pupolation[j];;
			}
		}
	}else{
		std::cout<<RED<<"未使用贪心算法初始化种群"<<RESET<<std::endl;
	}

	// static sf::RenderWindow window1(sf::VideoMode(1500, 1500), "TSP-GT+greedy");
	// visionTSP(window1,cityXY,first_pupolation );
	// while(1);
	//end


	// 初始化individualAdaptability
	individualAdaptability = vector<double>(2 * numColony); // 后面的numColony个是用于存放子个体的适应度的
	// 计算种群中每个个体的适应度
	calculateAdaptability();
			

}

// 获取最优个体
vector<int> GA_GT::getBestIndividual() {
	int bestIndex = 0;
	for (int i = 1; i < numColony; i++) {
		if (individualAdaptability[i] < individualAdaptability[bestIndex]) {
			bestIndex = i;
		}
	}
	return colony[bestIndex];
}
