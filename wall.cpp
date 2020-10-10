
#include "header/wall.h"
#include "shader/wall.h"
#include "header/levelData.h"
#include <iostream>

extern LevelData g_level;

Wall::~Wall() {
    glDeleteProgram(wallShaderProgram);
    cleanVAO(wallVAO);
}

Wall::Wall() {
    wallShaderProgram = compileShader(wallVertexShaderSrc, wallFragmentShaderSrc);
	//generate wall VAO
    wallVAO = genObject();
	//set the vertex attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLuint), (const void*)0);
	glEnableVertexAttribArray(0);
	//generate corner VAO
	cornerVAO = genCornerVAO(1);
	//set the vertex attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLuint), (const void*)0);
	glEnableVertexAttribArray(0);
}

GLuint Wall::genObject() {
	//target value 1, don't change size of x and y, don't add a display value
	std::vector<GLfloat> arr = genWallCoordinates(1);
	std::vector<GLuint> arrIndices = genIndices(wallSize);
	return createVAO(arr, arrIndices);
}

void Wall::drawObject() {
	glUseProgram(wallShaderProgram);
	//draw walls
	glBindVertexArray(wallVAO);
	glDrawElements(GL_TRIANGLES, (6 * wallSize), GL_UNSIGNED_INT, (const void*)0);
	//draw corners
	glBindVertexArray(cornerVAO);
	glDrawArrays(GL_TRIANGLES, 0, (3 * cornerSize));
}

std::vector<GLfloat> Wall::genWallCoordinates(const int target) {
    /* local data */
	float
		//wall position
		x = -1.0f,
		y = -1.0f,
		//resize wall
		xResize = (float)(g_level.elementWidth / 1.2f),
		yResize = (float)(g_level.elementHeight / 1.2f);
	std::vector<GLfloat> arr;
	//fills in array with coordinates
	for (int i = 0; i < g_level.arrHeight; i++, x = -1.0f, y += g_level.elementHeight) {
		for (int j = 0; j < g_level.arrWidth; j++, x += g_level.elementWidth) {
			if (g_level.arr[i][j] == target) {
				//check over target
				if(i + 1 < g_level.arrHeight && g_level.arr[i + 1][j] != 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x, y + (float)(g_level.elementHeight),
						//bottom left coordinate
						x, y + yResize,
						//bottom right coordinate
						x + (float)(g_level.elementWidth), y + yResize,
						//top right coordinate
						x + (float)(g_level.elementWidth), y + (float)(g_level.elementHeight)
					});
					wallSize++;
				}
				//check under target
				if(i - 1 >= 0 && g_level.arr[i - 1][j] != 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x, y + (float)(g_level.elementHeight) - yResize,
						//bottom left coordinate
						x, y,
						//bottom right coordinate
						x + (float)(g_level.elementWidth), y,
						//top right coordinate
						x + (float)(g_level.elementWidth), y + (float)(g_level.elementHeight) - yResize
					});
					wallSize++;
				}
				//check left of target
				if(j - 1 >= 0 && g_level.arr[i][j - 1] != 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x, y + (float)(g_level.elementHeight),
						//bottom left coordinate
						x, y,
						//bottom right coordinate
						x + (float)(g_level.elementWidth) - xResize, y,
						//top right coordinate
						x + (float)(g_level.elementWidth) - xResize, y + (float)(g_level.elementHeight)
					});
					wallSize++;
				}
				//check right of target
				if(j + 1 < g_level.arrWidth && g_level.arr[i][j + 1] != 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x + xResize, y + (float)(g_level.elementHeight),
						//bottom left coordinate
						x + xResize, y,
						//bottom right coordinate
						x + (float)(g_level.elementWidth), y,
						//top right coordinate
						x + (float)(g_level.elementWidth), y + (float)(g_level.elementHeight)
					});
					wallSize++;
				}
			}
		}
	}
	return arr;
}

GLuint Wall::genCornerVAO(const int target) {
    /* local data */
	float
		//wall position
		x = -1.0f,
		y = -1.0f,
		//resize wall
		xResize = (float)(g_level.elementWidth / 1.2f) / 5.f,
		yResize = (float)(g_level.elementHeight / 1.2f) / 5.f;
	std::vector<GLfloat> arr;
	//fills in array with coordinates
	for (int i = 0; i < g_level.arrHeight; i++, x = -1.0f, y += g_level.elementHeight) {
		for (int j = 0; j < g_level.arrWidth; j++, x += g_level.elementWidth) {
			if (g_level.arr[i][j] == target) {
				//check top right
				if(i + 1 < g_level.arrHeight && g_level.arr[i + 1][j] != 1 && j + 1 < g_level.arrWidth && g_level.arr[i + 1][j + 1] == 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x + (float)(g_level.elementWidth), y + (float)(g_level.elementHeight),
						//bottom left coordinate
						x + (float)(g_level.elementWidth), y + (float)(g_level.elementHeight) - yResize,
						//top right coordinate
						x + (float)(g_level.elementWidth) + xResize, y + (float)(g_level.elementHeight)
					});
					cornerSize++;
				}
				//check top left
				if(i + 1 < g_level.arrHeight && g_level.arr[i + 1][j] != 1 && j - 1 >= 0 && g_level.arr[i + 1][j - 1] == 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x - xResize, y + (float)(g_level.elementHeight),
						//bottom right coordinate
						x, y + (float)(g_level.elementHeight) - yResize,
						//top right coordinate
						x, y + (float)(g_level.elementHeight)
					});
					cornerSize++;
				}
				//check bottom right
				if(i - 1 >= 0 && g_level.arr[i - 1][j] != 1 && j + 1 < g_level.arrWidth && g_level.arr[i - 1][j + 1] == 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x + (float)(g_level.elementWidth), y,
						//bottom left coordinate
						x + (float)(g_level.elementWidth), y + yResize,
						//top right coordinate
						x + (float)(g_level.elementWidth) + xResize, y
					});
					cornerSize++;
				}
				//check bottom left
				if(i - 1 >= 0 && g_level.arr[i - 1][j] != 1 && j - 1 >= 0 && g_level.arr[i - 1][j - 1] == 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x - xResize, y,
						//bottom right coordinate
						x, y + yResize,
						//top right coordinate
						x, y
					});
					cornerSize++;
				}
			}
		}
	}

	GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, arr.size() * sizeof(GLfloat), arr.data(), GL_STATIC_DRAW);

	return vao;
}