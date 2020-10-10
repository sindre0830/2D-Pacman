#ifndef __LEVELDATA_H
#define __LEVELDATA_H

#include <vector>

struct LevelData {
    /* data */
    int arrWidth, arrHeight, wallSize, pelletSize, score;
    double elementWidth, elementHeight;
    std::vector<std::vector<int>> arr;
    std::vector<std::vector<bool>> ghostPos;
    /* functionality */
    //levelData();
};

#endif
