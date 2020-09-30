/* libraries */
#include "header/pellet.h"
#include "shader/pellet.h"
/* global variables */
extern int  g_pelletSize;
extern float g_rowInc, g_colInc;

Pellet::~Pellet() {
    glDeleteProgram(pelletShaderProgram);
    cleanVAO(pelletVAO);
}

Pellet::Pellet() {
    pelletVAO = genObject();
    pelletShaderProgram = compileShader(squareVertexShaderSrc, squareFragmentShaderSrc);
	//set the vertex attribute
    GLint posAttrib = glGetAttribLocation(pelletShaderProgram, "a_Position");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLuint) * 3, (const void*)0);
	glEnableVertexAttribArray(0);
}

void Pellet::setupObject() {
    pelletVAO = genObject();
	//set the vertex attribute
    GLint posAttrib = glGetAttribLocation(pelletShaderProgram, "a_Position");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLuint) * 3, (const void*)0);
	glEnableVertexAttribArray(0);
}

GLuint Pellet::genObject() {
	std::vector<GLfloat> arr = genCoordinates(0, (g_rowInc / 2.5f), (g_colInc / 2.5f));
	std::vector<GLuint> arrIndices = genIndices(g_pelletSize);
	return createVAO(arr, arrIndices);
}

void Pellet::drawObject() {
    draw(pelletShaderProgram, pelletVAO, g_pelletSize);
}

void Pellet::clearObject() {
    cleanVAO(pelletVAO);
}
