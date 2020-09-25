/**
 *
 *
 *
 *
 *
 */


#include <iostream>
#include <fstream>

using namespace std;

int main() {

    int row = 0;
    int col = 0;       //Size of map
    int buffer;
    int gMap[row][col];

    fstream fileMap("levels_level0.txt", ios::in);

    if (fileMap) {

        for (int i = 0; i < row; i++)    {
            for (int j = 0; j < col; j++)   {
                fileMap >> gMap[i][j];
            }

            fileMap.ignore();

        }
        fileMap.close();
    }
    else std::cout << "Unable to find map file!\n" std::endl;
}
 else
 cout << "\n\tFant ikke filen 'levels_level0.txt'!\n\n";

 return 0;
}
