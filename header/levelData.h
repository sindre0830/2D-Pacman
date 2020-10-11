#ifndef __LEVELDATA_H
#define __LEVELDATA_H
/* library */
#include <vector>
#include <map>
#include <string>

struct LevelData {
    /* data */
    int arrWidth, arrHeight, wallSize, pelletSize, score, pacmanCol, pacmanRow;
    double elementWidth, elementHeight;
    std::map<std::pair<int, int>, std::vector<std::vector<float>>> gridElement;
    std::vector<std::vector<int>> arr;
    std::string filePath = "level/";
    /* functionality */
    LevelData();
};

#endif
