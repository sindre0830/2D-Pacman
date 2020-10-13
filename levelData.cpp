/* library */
#include "header/levelData.h"
#include <iostream>
#include <fstream>
/* dictionary */
extern enum Target {PELLET, WALL, PACMAN, EMPTY, MAGICPELLET};

LevelData::LevelData() {
    int index = 0;
    bool flag = true;
    //array with all possible levels
    std::vector<std::string> filePathArr = {"level0", "level1"};
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
/**
 * @brief Reads data from level file.
 */
bool LevelData::inputData() {
    std::ifstream file;
	file.open(filePath);
    //branch if file is open else tell program to not run
	if (file) {
		int buffer;
        //input grid width from file
		file >> gridWidth;
		file.ignore();
        //input grid height from file
		file >> gridHeight;
		file.ignore();
		for (int i = 0; i < gridHeight; i++) {
			std::vector<int> arrRow;
			for (int j = 0; j < gridWidth; j++) {
                //input element type from file
				file >> buffer;
                //branch if element is a pellet
				if (buffer == PELLET) {
					//branch if position is a teleportation entrence else increase pellet size
					if(i == 0 || i == gridHeight - 1 || j == 0 || j == gridWidth - 1) {
                        //set element to empty
						buffer = EMPTY;
					} else pelletSize++;
				}
				arrRow.push_back(buffer);
				file.ignore();
			}
			grid.push_back(arrRow);
		}
		file.close();
		//set top left magicpellet
		for (int i = 0, j = 0; i < gridHeight && j < gridWidth; i++, j++) {
			if(grid[i][j] == PELLET) {
				grid[i][j] = MAGICPELLET;
				break;
			}
		}
		//set bottom right magicpellet
		for (int i = gridHeight - 1, j = gridWidth - 1; i >= 0 && j >= 0; i--, j--) {
			if(grid[i][j] == PELLET) {
				grid[i][j] = MAGICPELLET;
				break;
			}
		}
		//reverse order of array
		std::reverse(grid.begin(), grid.end());
		//set element value
		gridElementWidth = 1.f / ((float)(gridWidth) / 2.f);
		gridElementHeight = 1.f / ((float)(gridHeight) / 2.f);
		
		float
			x = -1.f,
			y = -1.f;
		//fills in array with coordinates
		for (int i = 0; i < gridHeight; i++, x = -1.f, y += gridElementHeight) {
			for (int j = 0; j < gridWidth; j++, x += gridElementWidth) {
				//top left
				gridElement[std::make_pair(i, j)].push_back({x, y + (float)(gridElementHeight)});
				//bottom left
				gridElement[std::make_pair(i, j)].push_back({x, y});
				//bottom right
				gridElement[std::make_pair(i, j)].push_back({x + (float)(gridElementWidth), y});
				//top right
				gridElement[std::make_pair(i, j)].push_back({x + (float)(gridElementWidth), y + (float)(gridElementHeight)});
			}
		}
		return true;
	} else return false;
}
