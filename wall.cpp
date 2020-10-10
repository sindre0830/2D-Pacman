
#include "header/wall.h"
#include "shader/wall.h"
#include <iostream>

extern int  g_wallSize, g_levelRow, g_levelCol;
extern double g_rowInc, g_colInc;
extern std::vector<std::vector<int>> g_level;

Wall::~Wall() {
    glDeleteProgram(wallShaderProgram);
    cleanVAO(wallVAO);
}

Wall::Wall() {
    wallVAO = genObject();
    wallShaderProgram = compileShader(wallVertexShaderSrc, wallFragmentShaderSrc);
	//set the vertex attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLuint), (const void*)0);
	glEnableVertexAttribArray(0);
}

GLuint Wall::genObject() {
	//target value 1, don't change size of x and y, don't add a display value
	std::vector<GLfloat> arr = genCoordinates(1);
	std::vector<GLuint> arrIndices = genIndices(g_wallSize);
	return createVAO(arr, arrIndices);
}

void Wall::drawObject() {
	glUseProgram(wallShaderProgram);
	glBindVertexArray(wallVAO);
	glDrawElements(GL_TRIANGLES, (6 * g_wallSize), GL_UNSIGNED_INT, (const void*)0);
}

std::vector<GLfloat> Wall::genCoordinates(const int target) {
    /* local data */
	float
		//wall position
		x = -1.0f,
		y = -1.0f,
		//resize wall
		xResize = (float)(g_rowInc / 1.2f),
		yResize = (float)(g_colInc / 1.2f);
	std::vector<GLfloat> arr;
	//fills in array with coordinates
	for (int i = 0; i < g_levelCol; i++, x = -1.0f, y += g_colInc) {
		for (int j = 0; j < g_levelRow; j++, x += g_rowInc) {
			if (g_level[i][j] == target) {
				//check over target
				if(i + 1 < g_levelCol && g_level[i + 1][j] != 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x, y + (float)(g_colInc),
						//bottom left coordinate
						x, y + yResize,
						//bottom right coordinate
						x + (float)(g_rowInc), y + yResize,
						//top right coordinate
						x + (float)(g_rowInc), y + (float)(g_colInc)
					});
				}
				//check under target
				if(i - 1 >= 0 && g_level[i - 1][j] != 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x, y + (float)(g_colInc) - yResize,
						//bottom left coordinate
						x, y,
						//bottom right coordinate
						x + (float)(g_rowInc), y,
						//top right coordinate
						x + (float)(g_rowInc), y + (float)(g_colInc) - yResize
					});
				}
				//check left of target
				if(j - 1 >= 0 && g_level[i][j - 1] != 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x, y + (float)(g_colInc),
						//bottom left coordinate
						x, y,
						//bottom right coordinate
						x + (float)(g_rowInc) - xResize, y,
						//top right coordinate
						x + (float)(g_rowInc) - xResize, y + (float)(g_colInc)
					});
				}
				//check right of target
				if(j + 1 < g_levelRow && g_level[i][j + 1] != 1) {
					arr.insert(arr.end(), {
						//top left coordinate
						x + xResize, y + (float)(g_colInc),
						//bottom left coordinate
						x + xResize, y,
						//bottom right coordinate
						x + (float)(g_rowInc), y,
						//top right coordinate
						x + (float)(g_rowInc), y + (float)(g_colInc)
					});
				}
			}
		}
	}
	return arr;
}