/* libraries */
#include "headers/scenario.h"
#include "headers/functions.h"
#include <iostream>
#include <vector>
#include <fstream>
/* global variables */
extern int gCol, gRow, gWallSize, gPelletSize;
extern float gRowInc, gColInc, gPacX, gPacY;
extern std::vector<std::vector<int>> gLevel;
/**
 * Destroy the 'Scenario' object.
 */
Scenario::~Scenario() {}
/**
 * Reads data from level file
 */
void Scenario::readFile() {
    gRow = 28;
    gCol = 36;
    gLevel = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
		{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
		{1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	}; 
	//set increment value
	gRowInc = 1.0f / ((float)(gRow) / 2);
	gColInc = 1.0f / ((float)(gCol) / 2);
    //find amount of walls(1) and pellets(0)
    for (int i = 0; i < gCol; i++) {
		for (int j = 0; j < gRow; j++) {
			if (gLevel[i][j] == 1) {
				gWallSize++;
			} else if (gLevel[i][j] == 0) {
				gPelletSize++;
			}
		}
	}
	//!!!file read attempt
	/*
	std::ifstream file;
	file.open("/levels/level0");
	if (file) {
		int buffer;
		file >> gRow;
		file.ignore();
		file >> gCol;
		file.ignore();
		for (int i = 0; i < gCol; i++) {
			std::vector<int> arrRow;
			for (int j = 0; j < gRow; j++) {
				file >> buffer;
				arrRow.push_back(buffer);
				file.ignore();
			}
			gLevel.push_back(arrRow);
		}
		file.close();
	} else {
		std::cout << "Unable to find map file!\n"; //std::endl;
		std::cin.get();
	}
	*/
}
/**
 * @brief 
 * 
 * @return GLuint 
 */
GLuint Scenario::genMap() {
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
/**
 * @brief 
 * 
 * @return GLuint 
 */
GLuint Scenario::genPellet() {
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
/**
 * @brief 
 * 
 * @param shader 
 * @param vao 
 * @param window 
 */
void Scenario::draw(GLuint shader, GLuint vao, int n, float r, float g, float b) {
	auto vertexColorLocation = glGetUniformLocation(shader, "u_Color");
	glUseProgram(shader);
	glBindVertexArray(vao);
	glUniform4f(vertexColorLocation, r, g, b, 1.0f);
	glDrawElements(GL_TRIANGLES, (6 * n), GL_UNSIGNED_INT, (const void*)0);
}