/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "headers/pacman.h"
#include "headers/functions.h"
extern int gCol, gRow;
extern float gPacX, gPacY;
/**
 * Destroy the 'Pacman' object.
 */
Pacman::~Pacman() {}
/**
 * Declare variables on construction.
 */
Pacman::Pacman() {
	//0 = w, 1 = a, 2 = s, 3 = d
	dir = 3;
}
/**
 * Generate pacman.
 */
GLuint Pacman::genAsset() {
	float
		rowInc = 1.0f / ((float)(gRow) / 2),
		colInc = 1.0f / ((float)(gCol) / 2);

    GLfloat square[4 * 7] = {
		//position						//color                 //texture coord
		gPacX,			gPacY + colInc,	1.0f,	1.0f,	1.0f,	0.02f,	0.03f,
		gPacX,			gPacY,			1.0f,	1.0f,	1.0f,	0.15f,	0.03f,
		gPacX + rowInc,	gPacY,			1.0f,	1.0f,	1.0f,	0.15f,	0.245f,
		gPacX + rowInc,	gPacY + colInc,	1.0f,	1.0f,	1.0f,	0.02f,	0.245f
    };
	//reset values to be used in Pacman::draw()
	gPacX = 0.0f;
	gPacY = 0.0f;

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

	/*glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (const void*)0);	//position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (const void*)8);	//color
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (const void*)20);	//texture coord

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);*/






    GLuint square_indices[6] = { 0,1,2,0,2,3 };

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);


    GLuint ebo;
    glGenBuffers(1, &ebo);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);

    return vao;
}
/**
 * Move the asset to a direction untill collision.
 */
void Pacman::mov(GLuint pacmanShaderProgram) {
	if(dir == 0) {
		Transform(gPacX, (gPacY += 0.001f), pacmanShaderProgram);
	} else if (dir == 1) {
		Transform((gPacX -= 0.001f), gPacY, pacmanShaderProgram);
	} else if (dir == 2) {
		Transform(gPacX, (gPacY -= 0.001f), pacmanShaderProgram);
	} else if (dir == 3) {
		Transform((gPacX += 0.001f), gPacY, pacmanShaderProgram);
	}
}
/**
 * Check if the asset will collide with wall or pellet.
 */
int Pacman::collisonCheck() {
	return 1;
}
/**
 * Draw asset.
 */
void Pacman::draw(GLuint pacmanShaderProgram, GLuint pacmanVAO, GLFWwindow *window) {
    auto samplerSlotLocation0 = glGetUniformLocation(pacmanShaderProgram, "uTextureA");
	glUseProgram(pacmanShaderProgram);
	glBindVertexArray(pacmanVAO);
	//change direction
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		dir = 0;
	} if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		dir = 1;
	} if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		dir = 2;
	} if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		dir = 3;
	}
	//move asset
	mov(pacmanShaderProgram);

	glUniform1i(samplerSlotLocation0, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
}
/**
 * Change direction of asset to UP.
 */
void Pacman::movUp() {

}
/**
 * Change direction of asset to DOWN.
 */
void Pacman::movDown() {

}
/**
 * Change direction of asset to RIGHT.
 */
void Pacman::movRight() {

}
/**
 * Change direction of asset to LEFT.
 */
void Pacman::movLeft() {

}