// 解决TSP问题的重构算法（主要是tsp0的代码风格太丑陋了，修改成C++风格）
#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<string>
#include<cmath>
// #include "include/algorithm.h"
#include "../common/common.h"
#include "../data/data.h"

#include <thread>   // 包含 std::this_thread::sleep_for
#include <chrono>   // 包含 std::chrono::seconds
using namespace std;

class GA_GT {
private:
	int numCity;					 // 城市数量
	vector<vector<double>> cityXY;	 // 城市坐标
	vector<vector<double>> cityDis;  // 城市间距离的邻接矩阵
	
	int numColony = 100;			 // 种群数量
	vector<vector<int>> colony;		 // 种群
	vector<double> individualAdaptability; // 个体适应度

	int maxGen = 200000;			 // 最大演化代数
	// int maxGen = 10;
	double probabilityMutation = 0.02;	// 变异概率

	vector<int> bestIndividual;			// 当前最优个体
	double bestAdaptability;			// 当前最优个体的适应度

	bool is_vision = true;//是否可视化


public:
	std::string save_data_path = "/home/";
	std::string save_path_path;
	bool is_using_greedy = 1;//是否使用贪心算法

	GA_GT(){};
	GA_GT(string filePath) {
		init(filePath);
	}

	void setSaveDataPath(std::string path) {
		save_data_path = path;
	}

	void setSavePathPath(std::string path) {
		save_path_path = path;
	}

	std::string getSaveDataPath(){
		return save_data_path;
	}

	vector<vector<double>> getCityDis(){
		return cityDis;
	}


	void setIsVision(bool isVision) {
		is_vision = isVision;
		};

	vector<vector<double>> getCityXY(){
		return cityXY;
	};
	bool getIsVision() {
		return is_vision;
	}

	// 计算种群中每个个体的适应度
	void calculateAdaptability() ;

	// 初始化
	void init(string filePath);

	// 进行迭代计算
	void evolution(); 

	// 获取城市在路径中的位置
	int position(vector<int>& path, int city);

	void invert(vector<int>& path, int pos1, int pos2);

	// 在父代和子代中进行一个锦标赛选择
	void selection();

	bool readTspFile(string filePath) ;

	// 根据tsp数据计算城市之间的距离、并随机初始化种群、同时计算适应度
	void calculateData() ;

	// 获取最优个体
	vector<int> getBestIndividual() ;
};
