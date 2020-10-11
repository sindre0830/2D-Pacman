/* library */
#include "header/levelData.h"
#include <iostream>

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

/*int lesInt(const char* t, const int min, const int max)  {
    char buffer[MAXCHAR] = "";
    int  tall = 0;
    bool feil = false;

    do {
        feil = false;
        std::cout << t << " (" << min << " - " << max << "):  ";
        std::cin.getline(buffer, MAXCHAR);
        tall = atoi(buffer);
        if (tall == 0 && buffer[0] != '0')
        {  feil = true;   std::cout << "\nERROR: Not an integer\n\n";  }
    } while (feil  ||  tall < min  ||  tall > max);

    return tall;
}*/