
#include "header/wall.h"
#include "shader/wall.h"
#include "header/levelData.h"
#include <iostream>

extern LevelData g_level;
extern enum direction {topLeft, bottomLeft, bottomRight, topRight};
extern enum position {x, y};

Wall::~Wall() {
    cleanVAO(cornerVAO);
}

Wall::Wall() {
	//set target to walls
	target = 1;
	//create shader program
    entityShaderProgram = compileShader(wallVertexShaderSrc, wallFragmentShaderSrc);
	//generate wall VAO
    entityVAO = genObject();
	//set the vertex attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLuint), (const void*)0);
	glEnableVertexAttribArray(0);
	//generate corner VAO
	cornerVAO = genCornerVAO();
	//set the vertex attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLuint), (const void*)0);
	glEnableVertexAttribArray(0);
}

GLuint Wall::genObject() {
	//target value 1, don't change size of x and y, don't add a display value
	std::vector<GLfloat> arr = genWallCoordinates();
	std::vector<GLuint> arrIndices = genIndices(wallSize);
	return createVAO(arr, arrIndices);
}

void Wall::drawObject() {
	glUseProgram(entityShaderProgram);
	//draw walls
	glBindVertexArray(entityVAO);
	glDrawElements(GL_TRIANGLES, (6 * wallSize), GL_UNSIGNED_INT, (const void*)0);
	//draw corners
	glBindVertexArray(cornerVAO);
	glDrawArrays(GL_TRIANGLES, 0, (3 * cornerSize));
}

std::vector<GLfloat> Wall::genWallCoordinates() {
	float
		//resize wall
		xResize = (float)(g_level.elementWidth / 1.2f),
		yResize = (float)(g_level.elementHeight / 1.2f);
	//buffer array
	std::vector<GLfloat> arr;
	//fills in array with coordinates
	for (int i = 0; i < g_level.arrHeight; i++) {
		for (int j = 0; j < g_level.arrWidth; j++) {
			if (g_level.arr[i][j] == target) {
				//check if there can be a wall above
				if(i + 1 < g_level.arrHeight && g_level.arr[i + 1][j] != target) {
					arr.insert(arr.end(), {
						//top left coordinate
						g_level.elementPos[std::make_pair(i, j)][topLeft][x], g_level.elementPos[std::make_pair(i, j)][topLeft][y],
						//bottom left coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomLeft][x], g_level.elementPos[std::make_pair(i, j)][bottomLeft][y] + yResize,
						//bottom right coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomRight][x], g_level.elementPos[std::make_pair(i, j)][bottomRight][y] + yResize,
						//top right coordinate
						g_level.elementPos[std::make_pair(i, j)][topRight][x], g_level.elementPos[std::make_pair(i, j)][topRight][y]
					});
					wallSize++;
				}
				//check if there can be a wall under
				if(i - 1 >= 0 && g_level.arr[i - 1][j] != target) {
					arr.insert(arr.end(), {
						//top left coordinate
						g_level.elementPos[std::make_pair(i, j)][topLeft][x], g_level.elementPos[std::make_pair(i, j)][topLeft][y] - yResize,
						//bottom left coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomLeft][x], g_level.elementPos[std::make_pair(i, j)][bottomLeft][y],
						//bottom right coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomRight][x], g_level.elementPos[std::make_pair(i, j)][bottomRight][y],
						//top right coordinate
						g_level.elementPos[std::make_pair(i, j)][topRight][x], g_level.elementPos[std::make_pair(i, j)][topRight][y] - yResize
					});
					wallSize++;
				}
				//check if there can be a wall to the left
				if(j - 1 >= 0 && g_level.arr[i][j - 1] != target) {
					arr.insert(arr.end(), {
						//top left coordinate
						g_level.elementPos[std::make_pair(i, j)][topLeft][x], g_level.elementPos[std::make_pair(i, j)][topLeft][y],
						//bottom left coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomLeft][x], g_level.elementPos[std::make_pair(i, j)][bottomLeft][y],
						//bottom right coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomRight][x] - xResize, g_level.elementPos[std::make_pair(i, j)][bottomRight][y],
						//top right coordinate
						g_level.elementPos[std::make_pair(i, j)][topRight][x] - xResize, g_level.elementPos[std::make_pair(i, j)][topRight][y]
					});
					wallSize++;
				}
				//check if there can be a wall to the right
				if(j + 1 < g_level.arrWidth && g_level.arr[i][j + 1] != target) {
					arr.insert(arr.end(), {
						//top left coordinate
						g_level.elementPos[std::make_pair(i, j)][topLeft][x] + xResize, g_level.elementPos[std::make_pair(i, j)][topLeft][y],
						//bottom left coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomLeft][x] + xResize, g_level.elementPos[std::make_pair(i, j)][bottomLeft][y],
						//bottom right coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomRight][x], g_level.elementPos[std::make_pair(i, j)][bottomRight][y],
						//top right coordinate
						g_level.elementPos[std::make_pair(i, j)][topRight][x], g_level.elementPos[std::make_pair(i, j)][topRight][y]
					});
					wallSize++;
				}
			}
		}
	}
	return arr;
}

GLuint Wall::genCornerVAO() {
	float
		//resize corner acording to size of wall
		xResize = (float)(g_level.elementWidth / 1.2f) / 5.f,
		yResize = (float)(g_level.elementHeight / 1.2f) / 5.f;
	//buffer array
	std::vector<GLfloat> arr;
	//fills in array with coordinates
	for (int i = 0; i < g_level.arrHeight; i++) {
		for (int j = 0; j < g_level.arrWidth; j++) {
			if (g_level.arr[i][j] == target) {
				//check if there can be a corner top right
				if(i + 1 < g_level.arrHeight && g_level.arr[i + 1][j] != target && j + 1 < g_level.arrWidth && g_level.arr[i + 1][j + 1] == target) {
					arr.insert(arr.end(), {
						//top left coordinate
						g_level.elementPos[std::make_pair(i, j)][topRight][x], g_level.elementPos[std::make_pair(i, j)][topRight][y],
						//bottom left coordinate
						g_level.elementPos[std::make_pair(i, j)][topRight][x], g_level.elementPos[std::make_pair(i, j)][topRight][y] - yResize,
						//top right coordinate
						g_level.elementPos[std::make_pair(i, j)][topRight][x] + xResize, g_level.elementPos[std::make_pair(i, j)][topRight][y]
					});
					cornerSize++;
				}
				//check if there can be a corner top left
				if(i + 1 < g_level.arrHeight && g_level.arr[i + 1][j] != target && j - 1 >= 0 && g_level.arr[i + 1][j - 1] == target) {
					arr.insert(arr.end(), {
						//top left coordinate
						g_level.elementPos[std::make_pair(i, j)][topLeft][x] - xResize, g_level.elementPos[std::make_pair(i, j)][topLeft][y],
						//bottom right coordinate
						g_level.elementPos[std::make_pair(i, j)][topLeft][x], g_level.elementPos[std::make_pair(i, j)][topLeft][y] - yResize,
						//top right coordinate
						g_level.elementPos[std::make_pair(i, j)][topLeft][x], g_level.elementPos[std::make_pair(i, j)][topLeft][y]
					});
					cornerSize++;
				}
				//check if there can be a corner bottom right
				if(i - 1 >= 0 && g_level.arr[i - 1][j] != target && j + 1 < g_level.arrWidth && g_level.arr[i - 1][j + 1] == target) {
					arr.insert(arr.end(), {
						//top left coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomRight][x], g_level.elementPos[std::make_pair(i, j)][bottomRight][y],
						//bottom left coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomRight][x], g_level.elementPos[std::make_pair(i, j)][bottomRight][y] + yResize,
						//top right coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomRight][x] + xResize, g_level.elementPos[std::make_pair(i, j)][bottomRight][y]
					});
					cornerSize++;
				}
				//check if there can be a corner bottom left
				if(i - 1 >= 0 && g_level.arr[i - 1][j] != target && j - 1 >= 0 && g_level.arr[i - 1][j - 1] == target) {
					arr.insert(arr.end(), {
						//top left coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomLeft][x] - xResize, g_level.elementPos[std::make_pair(i, j)][bottomLeft][y],
						//bottom right coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomLeft][x], g_level.elementPos[std::make_pair(i, j)][bottomLeft][y] + yResize,
						//top right coordinate
						g_level.elementPos[std::make_pair(i, j)][bottomLeft][x], g_level.elementPos[std::make_pair(i, j)][bottomLeft][y]
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