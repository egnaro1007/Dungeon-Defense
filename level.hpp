#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "debug.hpp"

class plaform {
    public:
        int top;
        int bottom;
        int left;
        int right;
};

std::vector<plaform> loadLevel(std::string path) {
    std::vector<plaform> level;
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            plaform p;
            p.top = std::stoi(line.substr(0, line.find(" ")));
            line = line.substr(line.find(" ") + 1);
            p.bottom = std::stoi(line.substr(0, line.find(" ")));
            line = line.substr(line.find(" ") + 1);
            p.left = std::stoi(line.substr(0, line.find(" ")));
            line = line.substr(line.find(" ") + 1);
            p.right = std::stoi(line.substr(0, line.find(" ")));
            level.push_back(p);
        }
        file.close();
    }
    else {
        crash(std::cout, "File", true);
    }
    return level;
}