/* libraries */
#include "headers/scenario.h"
#include <iostream>
#include <vector>
#include <fstream>
/* global variables */
extern int gCol, gRow, gWallSize, gPelletSize;
extern std::vector<std::vector<int>> gLevel;
extern float gPacX, gPacY;
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
		z = 0.0f,
		rowInc = 1.0f / ((float)(gRow) / 2),
		colInc = 1.0f / ((float)(gCol) / 2);
	std::vector<GLfloat> arr;
	std::vector<GLuint> arr_indices;
	//fills in arr with coordinates
	for (int i = 0; i < gCol; i++, x = -1.0f, y += colInc) {
		for (int j = 0; j < gRow; j++, x += rowInc) {
			if (gLevel[i][j] == 1) {
				//top left coordinate
				arr.push_back(x);
				arr.push_back(y + colInc);
				arr.push_back(z);
				//bottom left coordinate
				arr.push_back(x);
				arr.push_back(y);
				arr.push_back(z);
				//bottom right coordinate
				arr.push_back(x + rowInc);
				arr.push_back(y);
				arr.push_back(z);
				//top right coordinate
				arr.push_back(x + rowInc);
				arr.push_back(y + colInc);
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
	//create and bind the vertex array object
	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//create the vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	//set vbo to map data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, arr.size() * sizeof(GLfloat), &arr[0], GL_STATIC_DRAW);
	//create the element buffer object
	GLuint ebo;
	glGenBuffers(1, &ebo);
	//set ebo to map_indices data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arr_indices.size() * sizeof(GLuint), &arr_indices[0], GL_STATIC_DRAW);
	//set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void *)0);
	glEnableVertexAttribArray(0);
	return vao;
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
		z = 0.0f,
		rowInc = 1.0f / ((float)(gRow) / 2),
		colInc = 1.0f / ((float)(gCol) / 2);
	std::vector<GLfloat> arr;
	std::vector<GLuint> arr_indices;
	//fills in arr with coordinates
	for (int i = 0; i < gCol; i++, x = -1.0f, y += colInc) {
		for (int j = 0; j < gRow; j++, x += rowInc) {
			if (gLevel[i][j] == 0) {
				//top left coordinate
				arr.push_back((x + (rowInc / 2.5f)));
				arr.push_back((y + colInc) - (colInc / 2.5f));
				arr.push_back(z);
				//bottom left coordinate
				arr.push_back((x + (rowInc / 2.5f)));
				arr.push_back(y + (colInc / 2.5f));
				arr.push_back(z);
				//bottom right coordinate
				arr.push_back((x + rowInc) - (rowInc / 2.5f));
				arr.push_back(y + (colInc / 2.5f));
				arr.push_back(z);
				//top right coordinate
				arr.push_back((x + rowInc) - (rowInc / 2.5f));
				arr.push_back((y + colInc) - (colInc / 2.5f));
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
	//create and bind the vertex array object
	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//create the vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	//set vbo to map data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, arr.size() * sizeof(arr), &arr[0], GL_STATIC_DRAW);
	//create the element buffer object
	GLuint ebo;
	glGenBuffers(1, &ebo);
	//set ebo to map_indices data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arr_indices.size() * sizeof(arr_indices), &arr_indices[0], GL_STATIC_DRAW);
	//set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void*)0);
	glEnableVertexAttribArray(0);
	return vao;
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