/* library */
#include "header/levelData.h"
#include <iostream>

LevelData::LevelData() {
    int index = 0;
    bool flag = true;
    //array with all possible levels
    std::vector<std::string> filePathArr = {"level0"/*, "level1"*/};
    if(filePathArr.size() > 1) {
        std::cout << "Choose a level:\t";
        for(int i = 0; i < filePathArr.size(); i++) {
            std::cout << i << (i < filePathArr.size() - 1 ? ", " : "\n");
        }
        do {
            std::cout << "Level(0-" << filePathArr.size() - 1 << "): ";
            std::cin >> index;
            if(index <= filePathArr.size() - 1) flag = false;
        } while(flag);
        std::cout << std::endl;
    }
    filePath.append(filePathArr[index]);
}

int LevelData::getScore(const int index) {
    std::string str = "0000";
    std::string buffer = std::to_string(score);
    if(buffer.size() < str.size()) {
        int num = str.size() - buffer.size();
        str = "";
        for(int i = 0; i < num; i++) {
            str.append("0");
        }
        str.append(buffer);
    } else str = buffer;
    std::reverse(str.begin(), str.end());
    return (int)(str[index]) - '0';
}
