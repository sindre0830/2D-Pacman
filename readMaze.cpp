/**
 *
 *
 *
 *
 *
 */


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    int row, col, buffer;
    vector<vector<int>> gLevel;
    char test;
    ifstream file;
    file.open("levels/level0");
    if (file) {

        file >> row;
        file.ignore();
        file >> col;
        file.ignore();
        for (int i = 0; i < col; i++)    {
            vector<int> arrRow;
            for (int j = 0; j < row; j++)   {
                file >> buffer;
                arrRow.push_back(buffer);
                file.ignore();
            }
            gLevel.push_back(arrRow);
        }
        file.close();
    } else {
        cout << "Unable to find map file!\n";
    }
    cout << "oi " << gLevel[4][1];
    return 0;
}
