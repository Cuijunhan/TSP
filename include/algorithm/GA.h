/**
 * @file GA.h   用来实现遗传算法的一些函数库
 * @author junhan.cui (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include "../data/data.h"
#include "../common/common.h"

#include <optional>
#pragma once

struct GAConfig{
      int numCities; // 城市数量
      int inn = 100; // 初始种群大小
      int gnMax = 10; // 最大代数
      double crossRate = 1; // 交叉概率
      double muteRate = 0.15; // 变异概率
      GAConfig(std::string& filename, int inn, int gnMax, double crossRate, double muteRate):
      numCities(getCityNumber(filename)), inn(inn), gnMax(gnMax), crossRate(crossRate), muteRate(muteRate){};
      GAConfig(){};
      GAConfig(std::string& filename):numCities(getCityNumber(filename)){};
};

class GA{
      public:
      GA();
      GA(std::string& file_name, std::string& file_path):
            file_name_(file_name), file_path_(file_path){};
      GA(GAConfig& GA_config):GA_config_(GA_config){};
      ~GA()=default;
      
      void setGAConfig(GAConfig& GA_config){
            GA_config_ = GA_config;
      };
      void setFileName(std::string& file_name){
            file_name_ = file_name;
      };
      void setFilePath(std::string& file_path){
            file_path_ = file_path;
      };

      void setSavePathLengthFilePath(std::string& file_path){
            save_data_path_ = file_path;
      };


      void usePreData(std::string& pre_data_path){
            pre_data_path_ = pre_data_path;
            is_use_pre_data_ = true;
      };


      bool is_vision = true;//是否可视化
      bool is_save = true;//是否保存结果
      bool is_print = true;//是否打印
      bool is_save_best = true;//是否保存最优解

      void run();

      void infoGA();

      private:
      //生成初始种群,随机生成
      std::vector<std::vector<int>>  initPopulation_(int populationSize, int numCities);
      //生成初始种群,使用预训练数据
      std::vector<std::vector<int>> initPopulation_(int populationSize, int numCities,const std::string pre_data_path);
      //计算种群的适应度值和累积概率
      std::pair<std::vector<double>, std::vector<double>> calculatePopulationValue_(const std::vector<std::vector<int>>& population, 
                                                                        const std::vector<std::vector<double>>& dislist);
      //选择父母
      std::vector<int> selectChromosome_(const std::vector<double>& cumulativeProbs) ;
      //交叉
      std::vector<int> crossover_(const std::vector<int>& parent1, const std::vector<int>& parent2, double crossProb);
      //变异
      std::vector<int> mutate_(std::vector<int> chromosome, double muteProb);

      private:
      std::string file_name_; //数据集文件名
      std::string file_path_; //数据集地址
      std::string pre_data_path_;//预训练数据地址
      std::string save_data_path_;//保存路径长度数据地址

      bool is_use_pre_data_ = false;//是否使用预训练数据

      GAConfig GA_config_;
      int numCities_; // 城市数量
      int inn_ = 100; // 初始种群大小
      int gnMax_ = 10000; // 最大代数
      double crossRate_ = 1; // 交叉概率
      double muteRate_ = 0.15; // 变异概率
      std::vector<std::vector<int>> best_solution_; // 最佳解      
};






