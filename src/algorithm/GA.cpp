#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <cmath>
#include <ctime>
#include <limits>
#include <iomanip>
#include <list>
#include <SFML/Graphics.hpp>
#include <thread>

#include "common/common.h"
#include "algorithm/GA.h"

#pragma once

void GA::infoGA(){
    std::cout << "GA 遗传算法" << std::endl;
    std::cout << "数据集文件名:" <<file_name_<< std::endl;
    std::cout << "数据集地址:" << file_path_ << std::endl;
    std::cout << "保存路径长度数据地址:" << save_data_path_ << std::endl;
    std::cout << "预训练数据地址:" << pre_data_path_ << std::endl;
    std::cout << "保存路径长度数据地址：" << save_data_path_ << std::endl;
    std::cout << "是否使用预训练数据：" << is_use_pre_data_ << std::endl;

    std::cout<< "遗传算法参数设置" << std::endl;
    std::cout << "城市数量:" << numCities_ << std::endl;
    std::cout << "初始种群大小:" << inn_ << std::endl;
    std::cout << "最大代数:" << gnMax_ << std::endl;
    std::cout << "交叉概率:" << crossRate_ << std::endl;
    std::cout << "变异概率:" << muteRate_ << std::endl;

}


void GA::run(){
    //初始化参数
    numCities_ = GA_config_.numCities; // 城市数量
    inn_ = GA_config_.inn;; // 初始种群大小
    gnMax_ = GA_config_.gnMax;; // 最大代数
    crossRate_ = GA_config_.crossRate;; // 交叉概率
    muteRate_ = GA_config_.muteRate;; // 变异概率

    infoGA();//debug

    std::vector<Node> nodes = readTSPFile(file_path_);
    std::vector<Point> points;
    //设置绘图点的位置
    for (const auto& node : nodes) {
            points.push_back(Point(node.y*8+100, node.x*8+100));
    }
    
    // 计算距离矩阵
    std::vector<std::vector<double>> dislist = calculateDistanceMatrix(nodes);

    std::cout<<"is_use_pre_data_: "<<is_use_pre_data_<<std::endl;
    auto population = (is_use_pre_data_)?initPopulation_(inn_, numCities_,pre_data_path_):initPopulation_(inn_, numCities_);

    auto [chromoValues, cumulativeProbs] = calculatePopulationValue_(population, dislist);

    // 平均值和最大值
    std::vector<double> generationMeanValue(gnMax_);
    std::vector<double> generationMaxValue(gnMax_);
    std::vector<std::vector<int>> bestRoute(gnMax_, std::vector<int>(numCities_));
    //历史路径数值
    std::vector<double> dist_list;

    //迭代进化
    for (int generationNum = 0; generationNum < gnMax_; ++generationNum) {
        //新一代种群
        std::vector<std::vector<int>> newPopulation(inn_, std::vector<int>(numCities_));
        for (int j = 0; j < inn_; j += 2) {
        //选择父母
        auto selected = selectChromosome_(cumulativeProbs);
        //交叉
        auto crossed1 = crossover_(population[selected[0]], population[selected[1]], crossRate_);
        auto crossed2 = crossover_(population[selected[1]], population[selected[0]], crossRate_);
        //变异
        newPopulation[j] = mutate_(crossed1, muteRate_);
        newPopulation[j + 1] = mutate_(crossed2, muteRate_);
        }

        //计算新种群的适应度
        population = newPopulation;
        tie(chromoValues, cumulativeProbs) = calculatePopulationValue_(population, dislist);
        auto [maxValue, maxIndex] = minmax_element(chromoValues.begin(), chromoValues.end());
        generationMeanValue[generationNum] = 1.0 / accumulate(chromoValues.begin(), chromoValues.end(), 0.0) / chromoValues.size();
        generationMaxValue[generationNum] = 1.0 / *maxValue;
        bestRoute[generationNum] = population[distance(chromoValues.begin(), maxIndex)];
        
        if(is_print){
                std::cout << "第" << generationNum + 1 << "代: 平均值 = " << generationMeanValue[generationNum] <<
        ", 最大值 = " << generationMaxValue[generationNum] << std::endl;
        }

        dist_list.push_back(generationMaxValue[generationNum]);
            
        

        if(is_vision==true){
            static sf::RenderWindow window(sf::VideoMode(1500, 1500), "TSP-GA");
            visionTSP(std::ref(window), std::ref(points), std::ref(population[0]));
        }

        

        std::cout << "标准遗传算法得到的路径: ";
        for (int city : population[0]) {
            std::cout << city << " ";
        }
        std::cout << std::endl;

        if(static_cast<int>(((generationNum+1)*20)%(gnMax_))==0){
            if(is_save) saveDistData(dist_list, save_data_path_);
            if(is_use_pre_data_) writeVectorsToFile(population,pre_data_path_);
        }

    }
    auto [bestValue, bestIndex] = minmax_element(generationMaxValue.begin(), generationMaxValue.end());
    std::cout << "遗传算法得到的最短距离: " << *bestValue << std::endl;
    
    // while (true) {
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }

};

std::vector<std::vector<int>> GA::initPopulation_(int populationSize, int numCities) {
    std::vector<std::vector<int>> population(populationSize, std::vector<int>(numCities));
    for (int i = 0; i < populationSize; ++i) {
        population[i] = randPerm(numCities);
    }
    return population;
}

std::vector<std::vector<int>> GA::initPopulation_(int populationSize, int numCities,const std::string pre_data_path) {
      std::ifstream infile(pre_data_path);
      std::string line;
      std::vector<std::vector<int>> paths;
      if (!infile.is_open()) {
            std::cerr << "使用随机数据产生种群！！" << std::endl;
            return initPopulation_(populationSize, numCities);
      }
      return readVectorsFromFile(pre_data_path);
}

std::pair<std::vector<double>, std::vector<double>> GA::calculatePopulationValue_(const std::vector<std::vector<int>>& population, 
                                                                        const std::vector<std::vector<double>>& dislist){
    int populationSize = population.size();
    std::vector<double> chromoValues(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        chromoValues[i] = 1.0 / calculatePathDistance(dislist, population[i]);
    }

    std::vector<double> cumulativeProbs(populationSize);
    double fsum = 0;
    for (int i = 0; i < populationSize; ++i) {
        fsum += pow(chromoValues[i], 15);
    }
    for (int i = 0; i < populationSize; ++i) {
        cumulativeProbs[i] = pow(chromoValues[i], 15) / fsum;
    }
    partial_sum(cumulativeProbs.begin(), cumulativeProbs.end(), cumulativeProbs.begin());
    return { chromoValues, cumulativeProbs };
}

std::vector<int> GA::selectChromosome_(const std::vector<double>& cumulativeProbs) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    std::vector<int> selected(2);
    for (int i = 0; i < 2; ++i) {
        double r = dis(gen);
        auto it = lower_bound(cumulativeProbs.begin(), cumulativeProbs.end(), r);
        selected[i] = distance(cumulativeProbs.begin(), it);
        if (i == 1 && selected[i] == selected[i - 1]) {
            i--;
        }
    }
    return selected;
}

std::vector<int> GA::crossover_(const std::vector<int>& parent1, const std::vector<int>& parent2, double crossProb) {
    std::vector<int> child;// = parent1;
    std::random_device rd;
    std::mt19937 gen(rd());
    //通过随机数生成器生成一个[0,1]的随机数
    std::uniform_real_distribution<> dis(0, 1);

    std::list<int> lst1(parent1.begin(), parent1.end());
    std::list<int> lst2(parent2.begin(), parent2.end());

    if (dis(gen) < crossProb) {
        std::uniform_int_distribution<> disInt(1, parent1.size() - 2);
        int c1 = disInt(gen);
        int c2 = disInt(gen);
        int chb1 = std::min(c1, c2);
        int chb2 = std::max(c1, c2);

        // 获取起始和结束迭代器
        auto it_s = lst1.begin();
        auto it_e = lst1.end();
        auto it1 = lst1.begin();
        std::advance(it1, chb1); // 将 it1 前进到 chb1

        auto it2 = lst1.begin();
        std::advance(it2, chb2); // 将 it2 前进到 chb2

        // 使用范围构造新的 std::list
        std::list<int> lst_left(it_s, it1);
        std::list<int> lst_mid(it1, it2);
        std::list<int> lst_right(it2, it_e);

        //删除lst2种群中lst_mid的元素部分
        for(auto p:lst_mid){
            lst2.remove(p);
        }

        for(int i=0;i<parent1.size();i++){
            if(i>=chb1 && i<chb2){
                child.push_back(lst_mid.front());
                lst_mid.pop_front();
            }else{
                child.push_back(lst2.front());
                lst2.pop_front();
            }
        }

    }
    else child = parent1;

    return child;
}


std::vector<int> GA::mutate_(std::vector<int> chromosome, double muteProb) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    if (dis(gen) < muteProb) {
        std::uniform_int_distribution<> disInt(1, chromosome.size() - 2);
        int c1 = disInt(gen);
        int c2 = disInt(gen);
        int chb1 = std::min(c1, c2);
        int chb2 = std::max(c1, c2);
        int temp = chromosome[chb1];
        chromosome[chb1] = chromosome[chb2];
        chromosome[chb2] = temp;
        // reverse(chromosome.begin() + chb1 + 1, chromosome.begin() + chb2 + 1);
    }
    return chromosome;
}
