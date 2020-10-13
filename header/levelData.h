#ifndef __LEVELDATA_H
#define __LEVELDATA_H
/* library */
#include <vector>
#include <map>
#include <string>

struct LevelData {
    /* data */
    int gridWidth, gridHeight, pelletSize, score, pacmanCol, pacmanRow;
    float gridElementWidth, gridElementHeight;
    bool magicEffect = false, scoreChanged = false, gameover = false;
    std::map<std::pair<int, int>, std::vector<std::vector<float>>> gridElement;
    std::vector<std::vector<int>> grid;
    std::string filePath = "level/";
    /* functionality */
    LevelData();
    int getScore(const int index);
    bool inputData();
};

#endif
