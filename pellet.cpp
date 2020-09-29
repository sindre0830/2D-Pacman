/* libraries */
#include "headers/pellet.h"
/* global variables */
extern int gCol, gRow, gWallSize, gPelletSize;
extern float gRowInc, gColInc, gPacX, gPacY, gPacRow, gPacCol;
extern std::vector<std::vector<int>> gLevel;

Pellet::~Pellet() {}
/**
 * @brief Generate the pellets from the 2D array to the window.
 * 
 * @return GLuint VAO
 */
GLuint Pellet::genObject() {
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
			if (gLevel[i][j] == 0) {
				//top left coordinate
				arr.push_back((x + (gRowInc / 2.5f)));
				arr.push_back((y + gColInc) - (gColInc / 2.5f));
				arr.push_back(z);
				//bottom left coordinate
				arr.push_back((x + (gRowInc / 2.5f)));
				arr.push_back(y + (gColInc / 2.5f));
				arr.push_back(z);
				//bottom right coordinate
				arr.push_back((x + gRowInc) - (gRowInc / 2.5f));
				arr.push_back(y + (gColInc / 2.5f));
				arr.push_back(z);
				//top right coordinate
				arr.push_back((x + gRowInc) - (gRowInc / 2.5f));
				arr.push_back((y + gColInc) - (gColInc / 2.5f));
				arr.push_back(z);
			}
		}
	}
	//fills in map_indicies array
	for (int i = 0, j = 0; i < gPelletSize; i++, j += 4) {
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
