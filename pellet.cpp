/* library */
#include "header/levelData.h"
#include "header/pellet.h"
#include "shader/pellet.h"
/* global data */
extern LevelData g_level;
extern enum direction {topLeft, bottomLeft, bottomRight, topRight};
extern enum position {x, y};
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
	//set target to pellets
	target = 0;
	//create shader program and VAO
	entityShaderProgram = compileShader(pelletVertexShaderSrc, pelletFragmentShaderSrc);
    entityVAO = genObject();
	//set the vertex attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void*)(2 * sizeof(GLfloat)));
	//set bufferposition in refrence to position in level
	for(int i = 0, n = 0; i < g_level.arrHeight; i++) {
		for(int j = 0; j < g_level.arrWidth; j++) {
			if(g_level.arr[i][j] == target) {
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
void Pellet::drawObject() {
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
void Pellet::hidePellet(const int yPos, const int xPos) {
	GLfloat display = 0.f;
	for(int i = 8; i < pelletByteSize; i += 12) {
		glBufferSubData(GL_ARRAY_BUFFER, bufferPos[std::make_pair(yPos, xPos)] +  i, sizeof(GLfloat), &display);
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
			if (g_level.arr[i][j] == target) {
				arr.insert(arr.end(), {
					//middle left coordinate
					g_level.elementPos[std::make_pair(i, j)][topLeft][x] + xResize, g_level.elementPos[std::make_pair(i, j)][topLeft][y] - yRotate, display,
					//middle down coordinate
					g_level.elementPos[std::make_pair(i, j)][bottomLeft][x] + xRotate, g_level.elementPos[std::make_pair(i, j)][bottomLeft][y] + yResize, display,
					//middle right coordinate
					g_level.elementPos[std::make_pair(i, j)][bottomRight][x] - xResize, g_level.elementPos[std::make_pair(i, j)][bottomRight][y] + yRotate, display,
					//middle top coordinate
					g_level.elementPos[std::make_pair(i, j)][topRight][x] - xRotate, g_level.elementPos[std::make_pair(i, j)][topRight][y] - yResize, display
				});
			}
		}
	}
	return arr;
}
