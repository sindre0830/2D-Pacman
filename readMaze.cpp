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

    int row, col;       //Size of map
    int buffer;
    int gMap[row][col];

    fstream fil("levels_level0.txt", ios::in);

    if (fil) {                          //  Mulig å åpne filen:

    }
    fil.close();
}
 else
 cout << "\n\tFant ikke filen 'levels_level0.txt'!\n\n";

 return 0;
}
