#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "platform.hpp"

#include "debug.hpp"

std::vector<platform> loadLevel(std::string path) {
    std::vector<platform> level;
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            platform p;
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