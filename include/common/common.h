/**
 * @file common.h  工具库
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
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <list>
#include <random>
#include <numeric>
#include <ctime>
#include "../data/data.h"

#pragma once

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

template<typename T>
void printVector(const std::vector<std::vector<T>>& p) ;

template<typename T>
void printVector(const std::vector<T>& p) ;

template<typename T>
void printList(const std::list<T>& p) ;


/**
 * @brief 计算路径距离
 * 
 * @param dislist 
 * @param route 
 * @return double 
 */
double calculatePathDistance(const std::vector<std::vector<double>>& dislist, const std::vector<int>& route) ;
double calculateDistance(const Node &a, const Node &b) ;

double calculateDistance(const std::vector<double> &a, const std::vector<double> &b) ;

/**
 * @brief 计算距离矩阵 通过node计算
 * 
 * @param nodes 
 * @return std::vector<std::vector<double>> 
 */
std::vector<std::vector<double>> calculateDistanceMatrix(const std::vector<Node> &nodes) ;

/**
 * @brief 计算距离矩阵 
 *          通过 std::vector<std::vector<double>>& coordinates计算
 * @param coordinates 
 * @return vector<vector<double>> 
 */
std::vector<std::vector<double>> calculateDistanceMatrix(const std::vector<std::vector<double>>& coordinates);


//随机排列
std::vector<int> randPerm(int n);


//中心距离排序来生成初始种群
void centeralSort(std::vector<int> &route, const std::vector<std::vector<double>>& city_pos);

std::vector<int> getSortedIndices(const std::vector<double>& dist_list) ;


std::vector<int> readTourSection(const std::string& filename) ;