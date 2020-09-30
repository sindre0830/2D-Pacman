
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
}

GLuint Wall::genObject() {
	std::vector<GLfloat> arr = genCoordinates(1, .0f, .0f);
	std::vector<GLuint> arrIndices = genIndices(g_wallSize);
	return createVAO(arr, arrIndices);
}

void Wall::drawObject() {
    draw(wallShaderProgram, wallVAO, g_wallSize);
}
