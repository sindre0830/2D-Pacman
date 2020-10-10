/* libraries */
#include "header/pellet.h"
#include "shader/pellet.h"
#include <iostream>
#include <iterator>
/* global variables */
extern int  g_levelRow, g_levelCol, g_pelletSize;
extern double g_rowInc, g_colInc;
extern std::vector<std::vector<int>> g_level;
/**
 * @brief Destroy the Pellet:: Pellet object
 * 
 */
Pellet::~Pellet() {
    glDeleteProgram(pelletShaderProgram);
    cleanVAO(pelletVAO);
}
/**
 * @brief Construct a new Pellet:: Pellet object
 * 
 */
Pellet::Pellet() {}
/**
 * @brief Setup object by generating shader program, VAO and getting buffer array position.
 * 
 */
void Pellet::setupObject() {
    pelletShaderProgram = compileShader(pelletVertexShaderSrc, pelletFragmentShaderSrc);
    pelletVAO = genObject();
	//set the vertex attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void*)(2 * sizeof(GLfloat)));
	//set bufferposition in refrence to position in level
	for(int i = 0, n = 0; i < g_levelCol; i++) {
		for(int j = 0; j < g_levelRow; j++) {
			if(g_level[i][j] == 0) {
				bufferPos[std::make_pair(i, j)] = n * pelletByteSize;
				n++;
			}
		}
	}
}
/**
 * @brief Generate the VAO by buffer array and indicies.
 * 
 * @return GLuint 
 */
GLuint Pellet::genObject() {
	std::vector<GLfloat> arr = genCoordinates(0);
	std::vector<GLuint> arrIndices = genIndices(g_pelletSize);
	return createVAO(arr, arrIndices);
}
/**
 * @brief Draw object by installing the shader program and binding the VAO to the current rendering state.
 * 
 */
void Pellet::drawObject() {
	glUseProgram(pelletShaderProgram);
	glBindVertexArray(pelletVAO);
	glDrawElements(GL_TRIANGLES, (6 * g_pelletSize), GL_UNSIGNED_INT, (const void*)0);
}
/**
 * @brief Hide pellet by modifying the buffer array.
 * 
 * @param y 
 * @param x 
 */
void Pellet::hidePellet(const int y, const int x) {
	GLfloat display = 0.f;
	for(int i = 8; i < pelletByteSize; i += 12) {
		glBufferSubData(GL_ARRAY_BUFFER, bufferPos[std::make_pair(y, x)] +  i, sizeof(GLfloat), &display);
	}
}
/**
 * @brief Generate buffer array(x, y, display).
 * 
 * @param target 
 * @return std::vector<GLfloat> 
 */
std::vector<GLfloat> Pellet::genCoordinates(const int target) {
    /* local data */
	float
		//pellet position
		x = -1.f,
		y = -1.f,
		//display pellet
		display = 1.f,
		//resize pellet
		xResize = (float)(g_rowInc / 2.8f),
		yResize = (float)(g_colInc / 2.8f),
		//rotate pellet
		xRotate = (float)(g_rowInc / 2.f),
		yRotate = (float)(g_colInc / 2.f);
	std::vector<GLfloat> arr;
	//fills in arr with coordinates
	for (int i = 0; i < g_levelCol; i++, x = -1.f, y += g_colInc) {
		for (int j = 0; j < g_levelRow; j++, x += g_rowInc) {
			if (g_level[i][j] == target) {
				//middle left coordinate
				arr.push_back(x + xResize);
				arr.push_back(y + g_colInc - yRotate);
				arr.push_back(display);
				//middle down coordinate
				arr.push_back(x + xRotate);
				arr.push_back(y + yResize);
				arr.push_back(display);
				//middle right coordinate
				arr.push_back(x + g_rowInc - xResize);
				arr.push_back(y + yRotate);
				arr.push_back(display);
				//middle top coordinate
				arr.push_back(x + g_rowInc - xRotate);
				arr.push_back(y + g_colInc - yResize);
				arr.push_back(display);
			}
		}
	}
	return arr;
}
