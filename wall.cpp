/* libraries */
#include "headers/wall.h"
/* global variables */
extern int gCol, gRow, gWallSize, gPelletSize;
extern float gRowInc, gColInc, gPacX, gPacY, gPacRow, gPacCol;
extern std::vector<std::vector<int>> gLevel;

Wall::~Wall() {}
/**
 * @brief Generate the walls from the 2D array to the window.
 * 
 * @return GLuint VAO
 */
GLuint Wall::genObject() {
    /* local variables */
	float
		x = -1.0f,
		y = -1.0f,
		z = 0.0f;
	std::vector<GLfloat> arr;
	std::vector<GLuint> arr_indices;
	//fills in arr with coordinates
	for (int i = 0; i < gCol; i++, x = -1.0f, y += gColInc) {
		for (int j = 0; j < gRow; j++, x += gRowInc) {
			if (gLevel[i][j] == 1) {
				//top left coordinate
				arr.push_back(x);
				arr.push_back(y + gColInc);
				arr.push_back(z);
				//bottom left coordinate
				arr.push_back(x);
				arr.push_back(y);
				arr.push_back(z);
				//bottom right coordinate
				arr.push_back(x + gRowInc);
				arr.push_back(y);
				arr.push_back(z);
				//top right coordinate
				arr.push_back(x + gRowInc);
				arr.push_back(y + gColInc);
				arr.push_back(z);
			} else if (gLevel[i][j] == 2) {
				gPacX = x;
				gPacY = y;
				gPacRow = j;
				gPacCol = i;
			}
		}
	}
	//fills in map_indicies array
	for (int i = 0, j = 0; i < gWallSize; i++, j += 4) {
		//row 1
		arr_indices.push_back(j);
		arr_indices.push_back(j + 1);
		arr_indices.push_back(j + 2);
		//row 2
		arr_indices.push_back(j);
		arr_indices.push_back(j + 2);
		arr_indices.push_back(j + 3);
	}
	return createVAO(arr, arr_indices);
}
