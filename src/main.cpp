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
#include <tuple>   // 包含 tuple 和 tie 函数
#include <thread>   // 包含 std::this_thread::sleep_for
#include <chrono>   // 包含 std::chrono::seconds
#include <cstdlib>

#include "common/common.h"
#include "algorithm/GA.h"
#include "algorithm/DP.h"
#include "algorithm/GA_GT.h"
#include "algorithm/Greedy.h"
#include "algorithm/Greedy2.h"

#include "data/data.h"
#include <map>

#include <ctime> 

void   Delay(int   time)//time*1000为秒数 
{ 
clock_t   now   =   clock(); 

while(   clock()   -   now   <   time   ); 
} 




map<string,int> temp_map = {{"xqf131.tsp", 564},
{"xqg237.tsp", 1019},
{"pma343.tsp", 1368},
{"pka379.tsp", 1332},
{"bcl380.tsp", 1621},
{"pbl395.tsp", 1281},
{"pbk411.tsp", 1343},
{"pbn423.tsp", 1365},
{"pbm436.tsp", 1443},
{"xql662.tsp", 2513},
{"rbx711.tsp", 3115},
{"rbu737.tsp", 3314},
{"dkg813.tsp", 3199},
{"lim963.tsp", 2789},
{"pbd984.tsp", 2797},
{"xit1083.tsp", 3558},
{"dka1376.tsp", 4666},
{"dca1389.tsp", 5085},
{"dja1436.tsp", 5257},
{"icw1483.tsp", 4416},
{"fra1488.tsp", 4264},
{"rbv1583.tsp", 5387},
{"rby1599.tsp", 5533},
{"fnb1615.tsp", 4956},
{"djc1785.tsp", 6115},
{"dcc1911.tsp", 6396},
{"dkd1973.tsp", 6421},
{"djb2036.tsp", 6197},
{"dcb2086.tsp", 6600},
{"bva2144.tsp", 6304},
{"xqc2175.tsp", 6830},
{"bck2217.tsp", 6764},
{"xpr2308.tsp", 7219},
{"ley2323.tsp", 8352},
{"dea2382.tsp", 8017},
{"rbw2481.tsp", 7724},
{"pds2566.tsp", 7643},
{"mlt2597.tsp", 8071},
{"bch2762.tsp", 8234},
{"irw2802.tsp", 8423},
{"lsm2854.tsp", 8014},
{"dbj2924.tsp", 10128},
{"xva2993.tsp", 8492},
{"pia3056.tsp", 8258},
{"dke3097.tsp", 10539},
{"lsn3119.tsp", 9114},
{"lta3140.tsp", 9517},
{"fdp3256.tsp", 10008},
{"beg3293.tsp", 9772},
{"dhb3386.tsp", 11137},
{"fjs3649.tsp", 9272},
{"fjr3672.tsp", 9601},
{"dlb3694.tsp", 10959},
{"ltb3729.tsp", 11821},
{"xqe3891.tsp", 11995},
{"xua3937.tsp", 11239},
{"dkc3938.tsp", 12503},
{"dkf3954.tsp", 12538},
{"bgb4355.tsp", 12723},
{"bgd4396.tsp", 13009},
{"frv4410.tsp", 10711},
{"bgf4475.tsp", 13221},
{"xqd4966.tsp", 15316},
{"fqm5087.tsp", 13029},
{"fea5557.tsp", 15445},
// {"xsc6880.tsp", 21535},
// {"bnd7168.tsp", 21834},
// {"lap7454.tsp", 19535},
// {"ida8197.tsp", 22338},
// {"dga9698.tsp", 27724},
// {"xmc10150.tsp", 28387},
// {"xvb13584.tsp", 37083},
};
map<int,std::string> dataset_list = 
                {{ 564, "xqf131.tsp"},
{ 1019, "xqg237.tsp"},
{ 1368, "pma343.tsp"},
{ 1332, "pka379.tsp"},
{ 1621, "bcl380.tsp"},
{ 1281, "pbl395.tsp"},
{ 1343, "pbk411.tsp"},
{ 1365, "pbn423.tsp"},
{ 1443, "pbm436.tsp"},
{ 2513, "xql662.tsp"},
{ 3115, "rbx711.tsp"},
{ 3314, "rbu737.tsp"},
{ 3199, "dkg813.tsp"},
{ 2789, "lim963.tsp"},
{ 2797, "pbd984.tsp"},
{ 3558, "xit1083.tsp"},
{ 4666, "dka1376.tsp"},
{ 5085, "dca1389.tsp"},
{ 5257, "dja1436.tsp"},
{ 4416, "icw1483.tsp"},
{ 4264, "fra1488.tsp"},
{ 5387, "rbv1583.tsp"},
{ 5533, "rby1599.tsp"},
{ 4956, "fnb1615.tsp"},
{ 6115, "djc1785.tsp"},
{ 6396, "dcc1911.tsp"},
{ 6421, "dkd1973.tsp"},
{ 6197, "djb2036.tsp"},
{ 6600, "dcb2086.tsp"},
{ 6304, "bva2144.tsp"},
{ 6830, "xqc2175.tsp"},
{ 6764, "bck2217.tsp"},
{ 7219, "xpr2308.tsp"},
{ 8352, "ley2323.tsp"},
{ 8017, "dea2382.tsp"},
{ 7724, "rbw2481.tsp"},
{ 7643, "pds2566.tsp"},
{ 8071, "mlt2597.tsp"},
{ 8234, "bch2762.tsp"},
{ 8423, "irw2802.tsp"},
{ 8014, "lsm2854.tsp"},
{ 10128, "dbj2924.tsp"},
{ 8492, "xva2993.tsp"},
{ 8258, "pia3056.tsp"},
{ 10539, "dke3097.tsp"},
{ 9114, "lsn3119.tsp"},
{ 9517, "lta3140.tsp"},
{ 10008, "fdp3256.tsp"},
{ 9772, "beg3293.tsp"},
{ 11137, "dhb3386.tsp"},
{ 9272, "fjs3649.tsp"},
{ 9601, "fjr3672.tsp"},
{ 10959, "dlb3694.tsp"},
{ 11821, "ltb3729.tsp"},
{ 11995, "xqe3891.tsp"},
{ 11239, "xua3937.tsp"},
{ 12503, "dkc3938.tsp"},
{ 12538, "dkf3954.tsp"},
{ 12723, "bgb4355.tsp"},
{ 13009, "bgd4396.tsp"},
{ 10711, "frv4410.tsp"},
{ 13221, "bgf4475.tsp"},
{ 15316, "xqd4966.tsp"},
{ 13029, "fqm5087.tsp"},
{ 15445, "fea5557.tsp"},
// { 21535, "xsc6880.tsp"},
// { 21834, "bnd7168.tsp"},
// { 19535, "lap7454.tsp"},
// { 22338, "ida8197.tsp"},
// { 27724, "dga9698.tsp"},
// { 28387, "xmc10150.tsp"},
// { 37083, "xvb13584.tsp"}, 
};

std::string filename;
std::string pathname;
std::string init_filepath;
std::string out_filepath;
int tour;
std::string command;
std::string LKH_path;

void setParmams(std::string fn_filename){
    filename = fn_filename;
    pathname = "/home/ae/project-tsp/dataset/vlsi_tsp/vlsi/"+filename;
    init_filepath = "/home/ae/project-tsp/dataset/initdata/"+filename;
    out_filepath = "/home/ae/project-tsp/dataset/out_data/"+filename;
    tour = temp_map[filename];
    command = "python3 /home/ae/project-tsp/src/plot.py "+filename+" "+ to_string(tour);
    LKH_path = "/home/ae/LKH-2.0.10/";
}

void test_ga() {
    GAConfig GA_config;
    GA_config.numCities = getCityNumber(filename);
    GA_config.inn = 100; // 初始种群大小
    GA_config.gnMax = 100000; // 最大代数
    GA_config.crossRate = 0.8; // 交叉概率
    GA_config.muteRate = 0.015; // 变异概率

    GA mGA(filename,pathname);
    mGA.setGAConfig(GA_config);
    // mGA.usePreData(init_filepath);
    mGA.setSavePathLengthFilePath(out_filepath);
    
    mGA.is_vision = true;//是否可视化
    mGA.is_save = true;//是否保存结果
    mGA.is_print = true;//是否打印
    mGA.is_save_best = true;//是否保存最优解

    mGA.run();
    std::cout<<RED<<filename<<"----官方给出的最优路径距离："<<tour<<RESET<<std::endl;
    while (1);    
}
void test_ga_gt(bool is_using_greedy) {
	GA_GT ga_gt;
	// tsp.readTspFile("./pcb442.tsp");

    ga_gt.setSaveDataPath(out_filepath);
    ga_gt.is_using_greedy = is_using_greedy;
    ga_gt.setIsVision(true);
	ga_gt.init(pathname);

	ga_gt.evolution();

	vector<int> bestIndividual = ga_gt.getBestIndividual();
	// 输出最优个体到文件
    std::string save_path_path = (is_using_greedy)?init_filepath+"_ga_gt_greedy.txt":init_filepath+"_ga_gt.txt";
	fstream output(save_path_path, ios::out);
	for (int i = 0; i < bestIndividual.size(); i++) {
		output << bestIndividual[i] << " ";
	}

    if(!ga_gt.getIsVision()){
        static sf::RenderWindow window_ans(sf::VideoMode(1500, 1500), "TSP-GA-GT");
        std::vector<std::vector<double>> cityXY = ga_gt.getCityXY();
        visionTSP(std::ref(window_ans), cityXY, bestIndividual);
    }
    std::cout<<RED<<filename<<"----官方给出的最优路径距离："<<tour<<RESET<<std::endl<<std::endl;
    
    // while (1);
}

void test_greedy() {
    std::vector<int> path = TSPGreedyAlgorithm(pathname);

    std::vector<std::pair<int,int>> cities= Greedy2::readTspFile2Vectors(pathname);
    
    static sf::RenderWindow window_ans(sf::VideoMode(1500, 1500), "TSP-greedy-"+filename);
    std::vector<std::vector<double>> cityXY = readTspFile2Vectors(pathname);
    visionTSP(std::ref(window_ans), cityXY, path);
    std::cout<<RED<<filename<<"----官方给出的最优路径距离："<<tour<<", greedy给出最短路径为:"<<Greedy2::calculatePathCost(path, cities)<<RESET<<std::endl;
    // while (1);
}

void test_greedy2() {
    std::vector<std::vector<double>> cityXY = readTspFile2Vectors(pathname);
    std::pair<std::vector<int>, double> result = Greedy2::Greedy2(pathname);
    result.first.pop_back();
    static sf::RenderWindow window(sf::VideoMode(1500, 1500), "test_greedy2");
    visionTSP(window,cityXY,result.first );
    std::cout<<RED<<filename<<"----官方给出的最优路径距离："<<tour<<", greed2给出最短路径为:"<<result.second<<RESET<<std::endl;
    // while(1);
    // return result;

}
void test_LKH() {
    std::vector<std::vector<double>> cityXY = readTspFile2Vectors(pathname);
    // std::string LKH_path = "/home/ae/LKH-2.0.10/pbn423.opt.tour";
    std::string LKH_path = "/home/ae/LKH-2.0.10/xqe3891.opt.tour";
    std::vector<int> result = readTourSection(LKH_path);
    static sf::RenderWindow window(sf::VideoMode(1500, 1500), "LKH");
    visionTSP(window,cityXY,result);


}



int main() {
    std::map<int,std::string>::iterator iter;
    std::string command_LKH = "cd /home/ae/LKH-2.0.10/ && ./LKH xqe3891.par ";
    system(command_LKH.c_str());
    // setParmams("bgb4355.tsp");
    setParmams("xqe3891.tsp");

        
       std::vector<std::vector<double>> cityXY = readTspFile2Vectors(pathname);
    while (1)
    {
         
         std::vector<std::vector<int>> result = readVectorsFromFile(init_filepath+"_ga_gt_greedy.txt");
        static sf::RenderWindow window(sf::VideoMode(1500, 1500), "LKH");
        visionTSP(window,cityXY,result[0]);
        test_LKH();
    }
    
    
    // while(1);
    // for(iter = dataset_list.begin();iter != dataset_list.end();++iter){
    //     // if (iter->second == "xqg237.tsp") continue;
    //     // iter++;
    //     // iter++;
    //     // iter++;
    //     // iter++;
    //     // iter++;
        
    //     setParmams(iter->second);
    //     std::cout<<iter->second<<std::endl;
    //     test_ga();
    //     // test_greedy2();
    //     // test_ga_gt(1);
    //     // std::cout<<RED<<"filename:"<<iter->second<<RESET;
    //     // std::cout<<RED<<", tour:"<<tour<<RESET<<std::endl;
    //     // test_ga_gt(0);
    //     // setParmams(iter->second);
    //     // test_ga_gt(1);
    //     // system(command.c_str());
    //     // std::cout<<command.c_str()<<std::endl;
    //     // while(1);
    //     // Delay(50*1000);   //延时5秒         
    // }
    // setParmams("xqg237.tsp");
    // // setParmams("xqf131.tsp");

    // setParmams("pma343.tsp");
    // test_greedy2();
    
    // test_greedy();
    return 0;
}


