#include "data/data.h"

int getCityNumber(std::string& filename) {    
    // 从文件名中提取数字
    std::string numberStr;
    for (char c : filename) {
        if (std::isdigit(c)) {
            numberStr += c;
        }
    }
    // 将提取的字符串转换为整数    
    return std::stoi(numberStr);
}

std::vector<Node> readTSPFile(const std::string &filename) {
    std::ifstream infile(filename);
    std::string line;
    std::vector<Node> nodes;
    
    if (!infile.is_open()) {
        std::cout<<"文件："<< filename <<" 打开失败！"<<std::endl;
        return nodes;
    }

    bool node_section = false;

    while (std::getline(infile, line)) {
        if (line == "NODE_COORD_SECTION") {
            node_section = true;
            continue;
        }
        if (node_section) {
            if (line == "EOF") {
                break;
            }
            std::istringstream iss(line);
            int id;
            double x, y;
            if (!(iss >> id >> x >> y)) {
                break; // error
            }
            nodes.push_back({id, x, y});
        }
    }

    infile.close();
    return nodes;
}

std::vector<std::vector<double>> readTspFile2Vectors(std::string filePath) {
	std::vector<Node> nodes = readTSPFile(filePath);
    std::vector<std::vector<double>> cityXY;
	int numCity = nodes.size();
	cityXY = std::vector<std::vector<double>>(numCity, std::vector<double>(2));
	for (int i = 0; i < numCity; i++) {
		cityXY[i][0] = nodes[i].x;
		cityXY[i][1] = nodes[i].y;
	}
	return cityXY;
}

void drawPath(sf::RenderWindow& window, const std::vector<Point>& points) {
    sf::VertexArray lines(sf::LinesStrip, points.size());

    for (size_t i = 0; i < points.size(); ++i) {
        lines[i].position = sf::Vector2f(points[i].x, points[i].y);
        lines[i].color = sf::Color::Red;
    }

    window.draw(lines);
}

void drawPath(sf::RenderWindow& window, const std::vector<Point>& points,const std::vector<int>& path) {
    sf::VertexArray lines(sf::LinesStrip, path.size());
    for (size_t i = 0; i < path.size(); ++i) {
        lines[i].position = sf::Vector2f(points[path[i]].x, points[path[i]].y);
        lines[i].color = sf::Color::Red;
    }
    window.draw(lines);
}


void drawPoints(sf::RenderWindow& window, const std::vector<Point>& points) {
    for (const auto& point : points) {
        sf::CircleShape shape(5);
        shape.setPosition(point.x - shape.getRadius(), point.y - shape.getRadius());
        shape.setFillColor(sf::Color::Blue);
        window.draw(shape);
    }
}

void drawPoints(sf::RenderWindow& window, const std::vector<Point>& points, const std::vector<int>& path) {
    for (int i=0;i<path.size();i++) {
        sf::CircleShape shape(5);
        shape.setPosition(points[path[i]].x - shape.getRadius(), points[path[i]].y - shape.getRadius());
        shape.setFillColor(sf::Color::Blue);
        window.draw(shape);
    }
}

void saveDistData(std::vector<double>& data,const std::string& file_name) {
    std::ofstream outputFile(file_name); // 打开文件

    if (outputFile.is_open()) {
        for (size_t i = 0; i < data.size(); ++i) {
            outputFile << data[i] << "\n"; // 写入每个数据点，每行一个数据
        }
        outputFile.close(); // 关闭文件
        std::cout <<"\033[32m"<< "Dist Data has been written to "+file_name<<"\033[0m"<<std::endl;
    } else {
        std::cout<<file_name<<std::endl;
        std::cerr <<"\033[31m"<< "Unable to open file!"<<"\033[0m"<<std::endl;
    }
}

std::vector<std::vector<int>> readVectorsFromFile(const std::string& filename) {
    std::vector<std::vector<int>> data;
    std::ifstream inFile(filename);

    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::vector<int> vec;
            std::istringstream iss(line);
            int num;
            while (iss >> num) {
                vec.push_back(num);
            }
            data.push_back(vec);
        }
        inFile.close();
        std::cout << "使用预训练数据： " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return data;
}

void writeVectorsToFile(const std::vector<std::vector<int>>& data, const std::string& filename) {
    std::ofstream outFile(filename);

    if (outFile.is_open()) {
        for (const auto& vec : data) {
            for (size_t i = 0; i < vec.size(); ++i) {
                outFile << vec[i];
                if (i != vec.size() - 1) {
                    outFile << " ";
                }
            }
            outFile << "\n";
        }
        outFile.close();
        std::cout << GREEN <<"Path Data has been written to " << filename<<RESET << std::endl;
    } else {
        std::cerr << RED <<"Unable to open file: " << filename <<RESET << std::endl;
    }
}

void writeVectorsToFile(const std::vector<int>& data, const std::string& filename) {
    std::ofstream outFile(filename);

    if (outFile.is_open()) {
        
        for (size_t i = 0; i < data.size(); ++i) {
            outFile << data[i];
            if (i != data.size() - 1) {
                outFile << " ";
            }
        }
        outFile << "\n";
        
        outFile.close();
        std::cout << GREEN <<"Path Data has been written to " << filename<<RESET << std::endl;
    } else {
        std::cerr << RED <<"Unable to open file: " << filename <<RESET << std::endl;
    }
}


void main_draw() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "TSP Visualization");

    std::vector<Point> points = {
        {100, 100}, {200, 300}, {400, 200}, {300, 100}, {500, 400}
    };    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        drawPoints(window, points);
        drawPath(window, points);


        window.display();
    }
std::cout<<"runing..."<<std::endl;
  
}

//将数据均匀映射到画布
void mapData2Window(sf::RenderWindow& window,std::vector<Point>& points){
    double max_points_x,min_points_x,max_points_y,min_points_y;
    max_points_x = points[0].x;
    min_points_x = points[0].x;
    max_points_y = points[0].y;
    min_points_y = points[0].y;
    for(int i=1;i<points.size();i++){
        if(points[i].x>max_points_x){
            max_points_x = points[i].x;
        }
        if(points[i].x<min_points_x){
            min_points_x = points[i].x;
        }
        if(points[i].y>max_points_y){
            max_points_y = points[i].y;
        }
        if(points[i].y<min_points_y){
            min_points_y = points[i].y;
        }
    }
    for(int i=0;i<points.size();i++){
        points[i].x = (points[i].x-min_points_x)/(max_points_x-min_points_x)*(window.getSize().x-100)+50;
        points[i].y = (points[i].y-min_points_y)/(max_points_y-min_points_y)*(window.getSize().y-100)+50;
    }
}


void visionTSP(sf::RenderWindow& window,std::vector<Point>& points,std::vector<int>& path){
    mapData2Window(window,points);
    sf::Event event;
    while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear(sf::Color::White);
    drawPoints(window, points);
    drawPath(window, points,path);  
    window.display();
}

void visionTSP(sf::RenderWindow& window,std::vector<std::vector<double>>& vpoints,std::vector<int>& path){
    sf::Event event;
    std::vector<Point> points;
    points = vector2point(vpoints);
    mapData2Window(window,points);

    while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear(sf::Color::White);
    drawPoints(window, points);
    drawPath(window, points,path);  
    window.display();
}


sf::RenderWindow& getWindowInstance(int width, int height, std::string title) {
    static sf::RenderWindow window(sf::VideoMode(width, height), title);
    return window;
}

std::vector<Point> vector2point(std::vector<std::vector<double>>& vpoints){
    std::vector<Point> points;
    for (int i=0;i<vpoints.size();i++){
        points.push_back(vector2point(vpoints[i]));
    }
    return points;
}

Point vector2point(std::vector<double>& vpoints){
    Point point(vpoints[0],vpoints[1]);
    return point;
}

// void mapData2Window(sf::RenderWindow& window,std::vector<Point>& points);

std::vector<double> node2vector(Node& node)
{
    std::vector<double> vpoint;
    vpoint.push_back(node.x);
    vpoint.push_back(node.y);
    return vpoint;
}

std::vector<std::vector<double>> node2vector(std::vector<Node>& nodes)
{
    std::vector<std::vector<double>> vpoints;
    for(int i=0;i<nodes.size();i++){
        vpoints.push_back(node2vector(nodes[i]));
    }
    return vpoints;
}





