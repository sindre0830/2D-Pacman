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
 //   int buffer;
    vector gMap[row][col];

    ifstream file;
    file.open("levels/level0");

    if (file) {

        for (int i = 0; i < col; i++)    {
            for (int j = 0; j < row; j++)   {
                file >> gMap[i][j];
                cout << gMap[i][j] << ' ';
            }

            file.ignore();
        }
        file.close();
    }
    else {
        cout << "Unable to find map file!\n";
    }
    return 0;
}
