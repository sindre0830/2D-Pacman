/* libraries */
#include "header/pellet.h"
#include "shader/pellet.h"
#include <iostream>
#include <iterator>
/* global variables */
extern int  g_levelRow, g_levelCol, g_pelletSize;
extern float g_rowInc, g_colInc;
extern std::vector<std::vector<int>> g_level;
extern bool g_atePellet;

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

	std::vector<std::vector<int>> pelletArrPos = g_level;
	//reverse order of array
	int tmp = 0;
	for(int i = 0, n = 0; i < g_levelCol; i++) {
		for(int j = 0; j < g_levelRow; j++) {
			if(pelletArrPos[i][j] == 0) {
				bufferPos[std::make_pair(i, j)] = n * pelletByteSize;
				n++;
			}
		}
	}
}

GLuint Pellet::genObject() {
	//target value 0, change size of x and y, add a display value
	std::vector<GLfloat> arr = genCoordinates(0, (g_rowInc / 2.5f), (g_colInc / 2.5f), true);
	std::vector<GLuint> arrIndices = genIndices(g_pelletSize);
	return createVAO(arr, arrIndices);
}

void Pellet::drawObject() {
    draw(pelletShaderProgram, pelletVAO, g_pelletSize);
}

void Pellet::hidePellet(const int y, const int x) {
	GLfloat display = 0.0f;
	//std::cout << y << ',' << x << ' ' << bufferPos[std::make_pair(y, x)] << std::endl;
	glBufferSubData(GL_ARRAY_BUFFER, bufferPos[std::make_pair(y, x)] +  8, sizeof(GLfloat), &display);
	glBufferSubData(GL_ARRAY_BUFFER, bufferPos[std::make_pair(y, x)] + 20, sizeof(GLfloat), &display);
	glBufferSubData(GL_ARRAY_BUFFER, bufferPos[std::make_pair(y, x)] + 32, sizeof(GLfloat), &display);
	glBufferSubData(GL_ARRAY_BUFFER, bufferPos[std::make_pair(y, x)] + 44, sizeof(GLfloat), &display);
}
