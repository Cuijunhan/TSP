#include "common/common.h"

template<typename T>
void printVector(const std::vector<std::vector<T>>& p) {
    for (auto chromo : p) {
        printVector(chromo);
        std::cout << std::endl;
    }
}
template void printVector(const std::vector<std::vector<int>>& p);
template void printVector(const std::vector<std::vector<double>>& p);

template<typename T>
void printVector(const std::vector<T>& p) {
    for (auto city : p) {std::cout << city << " ";}
    std::cout << std::endl;
}
template void printVector(const std::vector<int>& p) ;
template void printVector(const std::vector<double>& p) ;


template<typename T>
void printList(const std::list<T>& p) {
    for (auto city : p) {std::cout << city << " ";}
    std::cout << std::endl;
}
template void printList(const std::list<int>& p) ;
template void printList(const std::list<double>& p) ;

double calculatePathDistance(const std::vector<std::vector<double>>& dislist, const std::vector<int>& route) {
    double distance = 0.0;
    for (size_t i = 0; i < route.size() - 1; ++i) {
        distance += dislist[route[i]][route[i + 1]];
    }
    distance += dislist[route.back()][route[0]];
    return distance;
}

double calculateDistance(const Node &a, const Node &b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

double calculateDistance(const std::vector<double> &a, const std::vector<double> &b) {
    return std::sqrt(std::pow(a[0] - b[0], 2) + std::pow(a[1] - b[1], 2));
}

std::vector<std::vector<double>> calculateDistanceMatrix(const std::vector<Node> &nodes) {
    size_t n = nodes.size();
    std::vector<std::vector<double>> distanceMatrix(n, std::vector<double>(n));
    
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                distanceMatrix[i][j] = calculateDistance(nodes[i], nodes[j]);
            } else {
                distanceMatrix[i][j] = 0.0;
            }
        }
    }
    return distanceMatrix;
}

std::vector<std::vector<double>> calculateDistanceMatrix(const std::vector<std::vector<double>>& coordinates) {
    int numCities = coordinates.size();
    std::vector<std::vector<double>> dislist(numCities, std::vector<double>(numCities, 0.0));
    for (int i = 0; i < numCities; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            double distance = calculateDistance(coordinates[i], coordinates[j]);
            dislist[i][j] = distance;
            dislist[j][i] = distance;
        }
    }
    return dislist;
}

std::vector<int> randPerm(int n) {
    std::vector<int> perm(n);
    //获得一个随机数生成器
    iota(perm.begin(), perm.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(perm.begin(), perm.end(), g);
    return perm;
}


void centeralSort(std::vector<int> &route, const std::vector<std::vector<double>>& city_pos){
    double max_points_x,min_points_x,max_points_y,min_points_y,center_x,center_y;
    max_points_x = city_pos[0][0];
    min_points_x = city_pos[0][0];
    max_points_y = city_pos[0][1];
    min_points_y = city_pos[0][1];
    for(int i=1;i<city_pos.size();i++){
        if(city_pos[i][0]>max_points_x){
            max_points_x = city_pos[i][0];
        }
        if(city_pos[i][0]<min_points_x){
            min_points_x = city_pos[i][0];
        }
        if(city_pos[i][1]>max_points_y){
            max_points_y = city_pos[i][1];
        }
        if(city_pos[i][1]<min_points_y){
            min_points_y = city_pos[i][1];
        }
    }

    center_x = (max_points_x+min_points_x)/2;
    center_y = (max_points_y+min_points_y)/2;

    std::vector<double> center_pos = {center_x,center_y};

    std::vector<double> dist_list;
    for(int i=0;i<city_pos.size();i++){
        double dist = calculateDistance(center_pos,city_pos[i]);
        dist_list.push_back(dist);
    }
    route = getSortedIndices(dist_list);    

}

std::vector<int> getSortedIndices(const std::vector<double>& dist_list) {
    // 创建一个索引向量，初始值为 0 到 dist_list.size()-1
    std::vector<int> indices(dist_list.size());
    for (size_t i = 0; i < indices.size(); ++i) {
        indices[i] = i;
    }

    // 使用自定义比较函数对索引进行排序
    std::sort(indices.begin(), indices.end(), [&dist_list](int i1, int i2) {
        return dist_list[i1] < dist_list[i2];
    });

    return indices;
}

std::vector<int> readTourSection(const std::string& filename) {
    std::vector<int> tour;
    std::ifstream file(filename);
    std::string line;
    bool inTourSection = false;

    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return tour;
    }

    while (getline(file, line)) {
        if (line == "TOUR_SECTION") {
            inTourSection = true;
            continue;
        }
        if (inTourSection) {
            std::istringstream iss(line);
            int node;
            while (iss >> node) {
                if (node == -1) { // End of the tour section
                    tour.push_back(0);
                    return tour;
                }
                tour.push_back(node-1);
            }
        }
    }
    file.close();
    return tour;
}


