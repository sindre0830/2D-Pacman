
#include "header/wall.h"
#include "shader/wall.h"

extern int  g_wallSize;
extern double g_rowInc, g_colInc;

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
	std::vector<GLfloat> arr = genCoordinates(1, 0.f, 0.f, false);
	std::vector<GLuint> arrIndices = genIndices(g_wallSize);
	return createVAO(arr, arrIndices);
}

void Wall::drawObject() {
    draw(wallShaderProgram, wallVAO, g_wallSize);
}
