/* libraries */
#include "header/pellet.h"
#include "shader/pellet.h"
#include <iostream>
#include <iterator>
/* global variables */
extern int  g_levelRow, g_levelCol, g_pelletSize;
extern double g_rowInc, g_colInc;
extern std::vector<std::vector<int>> g_level;

Pellet::~Pellet() {
    glDeleteProgram(pelletShaderProgram);
    cleanVAO(pelletVAO);
}

Pellet::Pellet() {}

void Pellet::setupObject() {
    pelletShaderProgram = compileShader(pelletVertexShaderSrc, pelletFragmentShaderSrc);
    pelletVAO = genObject();
	//set the vertex attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void*)(2 * sizeof(GLfloat)));

	for(int i = 0, n = 0; i < g_levelCol; i++) {
		for(int j = 0; j < g_levelRow; j++) {
			if(g_level[i][j] == 0) {
				bufferPos[std::make_pair(i, j)] = n * pelletByteSize;
				n++;
			}
		}
	}
}

GLuint Pellet::genObject() {
	//target value 0, change size of x and y, add a display value
	std::vector<GLfloat> arr = genCoordinates(0);
	std::vector<GLuint> arrIndices = genIndices(g_pelletSize);
	return createVAO(arr, arrIndices);
}

void Pellet::drawObject() {
	glUseProgram(pelletShaderProgram);
	glBindVertexArray(pelletVAO);
	glDrawElements(GL_TRIANGLES, (6 * g_pelletSize), GL_UNSIGNED_INT, (const void*)0);
}

void Pellet::hidePellet(const int y, const int x) {
	GLfloat display = 0.0f;
	//std::cout << y << ',' << x << ' ' << bufferPos[std::make_pair(y, x)] << std::endl;
	glBufferSubData(GL_ARRAY_BUFFER, bufferPos[std::make_pair(y, x)] +  8, sizeof(GLfloat), &display);
	glBufferSubData(GL_ARRAY_BUFFER, bufferPos[std::make_pair(y, x)] + 20, sizeof(GLfloat), &display);
	glBufferSubData(GL_ARRAY_BUFFER, bufferPos[std::make_pair(y, x)] + 32, sizeof(GLfloat), &display);
	glBufferSubData(GL_ARRAY_BUFFER, bufferPos[std::make_pair(y, x)] + 44, sizeof(GLfloat), &display);
}

std::vector<GLfloat> Pellet::genCoordinates(const int target) {
    /* local data */
	float
		x = -1.0f,
		y = -1.0f,
		xSize = (float)(g_rowInc / 2.5f),
		ySize = (float)(g_colInc / 2.5f);
	std::vector<GLfloat> arr;
	//fills in arr with coordinates
	for (int i = 0; i < g_levelCol; i++, x = -1.0f, y += g_colInc) {
		for (int j = 0; j < g_levelRow; j++, x += g_rowInc) {
			if (g_level[i][j] == target) {
				//top left coordinate
				arr.push_back(x + xSize);
				arr.push_back(y + g_colInc - ySize);
				arr.push_back(1.f);
				//bottom left coordinate
				arr.push_back(x + xSize);
				arr.push_back(y + ySize);
				arr.push_back(1.f);
				//bottom right coordinate
				arr.push_back(x + g_rowInc - xSize);
				arr.push_back(y + ySize);
				arr.push_back(1.f);
				//top right coordinate
				arr.push_back(x + g_rowInc - xSize);
				arr.push_back(y + g_colInc - ySize);
				arr.push_back(1.f);
			}
		}
	}
	return arr;
}
