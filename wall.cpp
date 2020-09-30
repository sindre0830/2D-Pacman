
#include "header/wall.h"
#include "shader/wall.h"

extern int  g_wallSize;
extern float g_rowInc, g_colInc;

Wall::~Wall() {
    glDeleteProgram(wallShaderProgram);
    cleanVAO(wallVAO);
}

Wall::Wall() {
    wallVAO = genObject();
    wallShaderProgram = compileShader(squareVertexShaderSrc, squareFragmentShaderSrc);
	//set the vertex attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLuint), (const void*)0);
	glEnableVertexAttribArray(0);
}

GLuint Wall::genObject() {
	std::vector<GLfloat> arr = genCoordinates(1, .0f, .0f);
	std::vector<GLuint> arrIndices = genIndices(g_wallSize);
	return createVAO(arr, arrIndices);
}

void Wall::drawObject() {
    draw(wallShaderProgram, wallVAO, g_wallSize);
}
