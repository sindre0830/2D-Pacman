/* library */
#include "header/levelData.h"
#include "header/pellet.h"
#include "shader/pellet.h"
/* dictionary */
extern enum Corner {TOP_LEFT, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_RIGHT};
extern enum Position {X, Y};
extern enum Target {PELLET, WALL, PACMAN, EMPTY, MAGICPELLET};
/* global data */
extern LevelData g_level;
/**
 * @brief Destroy the Pellet:: Pellet object
 * 
 */
Pellet::~Pellet() {}
/**
 * @brief Construct a new Pellet:: Pellet object
 * 
 */
Pellet::Pellet() {
	//create shader program and VAO
	entityShaderProgram = compileShader(pelletVertexShaderSrc, pelletFragmentShaderSrc);
    entityVAO = genObject();
	//set the vertex attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void*)(2 * sizeof(GLfloat)));
	//set buffer position in refrence to position in level
	for(int i = 0, n = 0; i < g_level.arrHeight; i++) {
		for(int j = 0; j < g_level.arrWidth; j++) {
			if(g_level.arr[i][j] == PELLET || g_level.arr[i][j] == MAGICPELLET) {
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
	std::vector<GLfloat> arr = genCoordinates();
	std::vector<GLuint> arrIndices = genIndices(g_level.pelletSize);
	return createVAO(arr, arrIndices);
}
/**
 * @brief Draw object by installing the shader program and binding the VAO to the current rendering state.
 * 
 */
void Pellet::draw() {
	glUseProgram(entityShaderProgram);
	glBindVertexArray(entityVAO);
	glDrawElements(GL_TRIANGLES, (6 * g_level.pelletSize), GL_UNSIGNED_INT, (const void*)0);
}
/**
 * @brief Hide pellet by modifying the buffer array.
 * 
 * @param y 
 * @param x 
 */
void Pellet::hidePellet(const int col, const int row) {
	GLfloat display = 0.f;
	for(int i = 8; i < pelletByteSize; i += 12) {
		glBufferSubData(GL_ARRAY_BUFFER, bufferPos[std::make_pair(col, row)] + i, sizeof(GLfloat), &display);
	}
}
/**
 * @brief Generate buffer array(x, y, display).
 * 
 * @param target 
 * @return std::vector<GLfloat> 
 */
std::vector<GLfloat> Pellet::genCoordinates() {
	float
		//display pellet
		display = 1.f,
		//resize pellet
		xResize = (float)(g_level.elementWidth / 2.8f),
		yResize = (float)(g_level.elementHeight / 2.8f),
		//rotate pellet
		xRotate = (float)(g_level.elementWidth / 2.f),
		yRotate = (float)(g_level.elementHeight / 2.f);
	//buffer array
	std::vector<GLfloat> arr;
	//fills in array with coordinates
	for (int i = 0; i < g_level.arrHeight; i++) {
		for (int j = 0; j < g_level.arrWidth; j++) {
			if (g_level.arr[i][j] == PELLET) {
				arr.insert(arr.end(), {
					//middle left coordinate
					g_level.gridElement[std::make_pair(i, j)][TOP_LEFT][X] + xResize, g_level.gridElement[std::make_pair(i, j)][TOP_LEFT][Y] - yRotate, display,
					//middle down coordinate
					g_level.gridElement[std::make_pair(i, j)][BOTTOM_LEFT][X] + xRotate, g_level.gridElement[std::make_pair(i, j)][BOTTOM_LEFT][Y] + yResize, display,
					//middle right coordinate
					g_level.gridElement[std::make_pair(i, j)][BOTTOM_RIGHT][X] - xResize, g_level.gridElement[std::make_pair(i, j)][BOTTOM_RIGHT][Y] + yRotate, display,
					//middle top coordinate
					g_level.gridElement[std::make_pair(i, j)][TOP_RIGHT][X] - xRotate, g_level.gridElement[std::make_pair(i, j)][TOP_RIGHT][Y] - yResize, display
				});
			} else if (g_level.arr[i][j] == MAGICPELLET) {
				arr.insert(arr.end(), {
					//middle left coordinate
					g_level.gridElement[std::make_pair(i, j)][TOP_LEFT][X] + (xResize * 2.f), g_level.gridElement[std::make_pair(i, j)][TOP_LEFT][Y] - yRotate, display,
					//middle down coordinate
					g_level.gridElement[std::make_pair(i, j)][BOTTOM_LEFT][X] + xRotate, g_level.gridElement[std::make_pair(i, j)][BOTTOM_LEFT][Y] + (yResize * 2.f), display,
					//middle right coordinate
					g_level.gridElement[std::make_pair(i, j)][BOTTOM_RIGHT][X] - (xResize * 2.f), g_level.gridElement[std::make_pair(i, j)][BOTTOM_RIGHT][Y] + yRotate, display,
					//middle top coordinate
					g_level.gridElement[std::make_pair(i, j)][TOP_RIGHT][X] - xRotate, g_level.gridElement[std::make_pair(i, j)][TOP_RIGHT][Y] - (yResize * 2.f), display
				});
			}
		}
	}
	return arr;
}
