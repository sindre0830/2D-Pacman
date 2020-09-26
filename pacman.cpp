/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "headers/pacman.h"
#include "headers/functions.h"
#include <vector>
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

    std::vector<GLfloat> arr = {
		//position						//color                 //texture coord
		gPacX,			gPacY + colInc,	1.0f,	1.0f,	1.0f,	0.02f,	0.03f,
		gPacX,			gPacY,			1.0f,	1.0f,	1.0f,	0.15f,	0.03f,
		gPacX + rowInc,	gPacY,			1.0f,	1.0f,	1.0f,	0.15f,	0.245f,
		gPacX + rowInc,	gPacY + colInc,	1.0f,	1.0f,	1.0f,	0.02f,	0.245f
    };
    std::vector<GLuint> arr_indices = { 0,1,2,0,2,3 };
	//reset values to be used in Pacman::draw()
	gPacX = 0.0f;
	gPacY = 0.0f;
    return createVAO(arr, arr_indices);
}
/**
 * Move the asset to a direction untill collision.
 */
void Pacman::mov(GLuint pacmanShaderProgram) {
	float
		rowInc = 1.0f / ((float)(gRow) / 2),
		colInc = 1.0f / ((float)(gCol) / 2);
	if(dir == 0) {
		Transform(gPacX, (gPacY += colInc / 100), pacmanShaderProgram);
	} else if (dir == 1) {
		Transform((gPacX -= rowInc / 100), gPacY, pacmanShaderProgram);
	} else if (dir == 2) {
		Transform(gPacX, (gPacY -= colInc / 100), pacmanShaderProgram);
	} else if (dir == 3) {
		Transform((gPacX += rowInc / 100), gPacY, pacmanShaderProgram);
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