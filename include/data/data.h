/**
 * @file data.h   处理数据与文件的操作
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
#include <SFML/Graphics.hpp>

#pragma once

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

struct Dataset
{
      std::string name;
      int tour;
      Dataset(std::string n, int t):name(n),tour(t){};
};


struct Node {
    int id;
    double x;
    double y;
};

struct Point {
    float x, y;
    Point(float x, float y) : x(x), y(y) {};
};

//读取tsp文件，返回城市数量
int getCityNumber(std::string& filename);

//读取tsp文件，返回城市坐标
std::vector<Node> readTSPFile(const std::string &filename);

//绘制路径图，按照点的顺序画
void drawPath(sf::RenderWindow& window, const std::vector<Point>& points);
//绘制路径图，按照path给出的顺序画
void drawPath(sf::RenderWindow& window, const std::vector<Point>& points,const std::vector<int>& path);
//绘制散点图
void drawPoints(sf::RenderWindow& window, const std::vector<Point>& points) ;
//绘制散点图
void drawPoints(sf::RenderWindow& window, const std::vector<Point>& points, const std::vector<int>& path);
//存储迭代的路径距离数据
void saveDistData(std::vector<double>& data,const std::string& file_name);

//从本地读数据村到vector中，主要是用来作为预训练数据
std::vector<std::vector<int>> readVectorsFromFile(const std::string& filename);

//将迭代生成的种群数据村起来
void writeVectorsToFile(const std::vector<std::vector<int>>& data, const std::string& filename);


void main_draw();

void visionTSP(sf::RenderWindow& window,std::vector<Point>& points,std::vector<int>& newPopulation);

std::vector<Point> vector2point(std::vector<std::vector<double>>& vpoints);

Point vector2point(std::vector<double>& vpoints);

std::vector<double> node2vector(Node& node);
std::vector<std::vector<double>> node2vector(std::vector<Node>& nodes);

void visionTSP(sf::RenderWindow& window,std::vector<std::vector<double>>& vpoints,std::vector<int>& path);

//通过读取文件获取城市坐标图
std::vector<std::vector<double>> readTspFile2Vectors(std::string filePath);


void writeVectorsToFile(const std::vector<int>& data, const std::string& filename) ;
