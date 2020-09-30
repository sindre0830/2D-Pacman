/* libraries */
#include "header/pellet.h"
#include "shader/pellet.h"
/* global variables */
extern int  g_pelletSize;
extern float g_rowInc, g_colInc;
extern bool g_atePellet;

Pellet::~Pellet() {
    glDeleteProgram(pelletShaderProgram);
    cleanVAO(pelletVAO);
}

Pellet::Pellet() {
    pelletShaderProgram = compileShader(pelletVertexShaderSrc, pelletFragmentShaderSrc);
    setupObject();
}

void Pellet::setupObject() {
    pelletVAO = genObject();
	//set the vertex attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void*)(2 * sizeof(GLfloat)));
}

GLuint Pellet::genObject() {
	//target value 0, change size of x and y, add a display value
	std::vector<GLfloat> arr = genCoordinates(0, (g_rowInc / 2.5f), (g_colInc / 2.5f), true);
	std::vector<GLuint> arrIndices = genIndices(g_pelletSize);
	return createVAO(arr, arrIndices);
}

void Pellet::drawObject() {
	if(g_atePellet) {
		//cleanVAO(pelletVAO);
		//setupObject();
		g_atePellet = false;
	}
    draw(pelletShaderProgram, pelletVAO, g_pelletSize);
}
