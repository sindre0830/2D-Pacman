/* libraries */
#include "headers/pacman.h"
/* global variables */
extern int gCol, gRow;
extern float gRowInc, gColInc, gPacX, gPacY;
/**
 * @brief Destroy the Pacman object
 */
Pacman::~Pacman() {}
/**
 * @brief Declare variables on construction of Pacman object.
 */
Pacman::Pacman() {
	direction = 3;
}
/**
 * @brief Generate Pac-Man from the 2D array to the window.
 * 
 * @return GLuint 
 */
GLuint Pacman::genAsset() {
    std::vector<GLfloat> arr = {
		//position								//color                 //texture coord
		gPacX,				gPacY + gColInc,	1.0f,	1.0f,	1.0f,	0.02f,	0.03f,
		gPacX,				gPacY,				1.0f,	1.0f,	1.0f,	0.15f,	0.03f,
		gPacX + gRowInc,	gPacY,				1.0f,	1.0f,	1.0f,	0.15f,	0.245f,
		gPacX + gRowInc,	gPacY + gColInc,	1.0f,	1.0f,	1.0f,	0.02f,	0.245f
    };
    std::vector<GLuint> arr_indices = {0, 1, 2, 0, 2, 3};
	//reset values to be used in Pacman::draw()
	gPacX = 0.0f;
	gPacY = 0.0f;
    return createVAO(arr, arr_indices);
}
/**
 * @brief Check if the asset will collide with wall or pellet.
 * 
 * @return int 
 */
int Pacman::collisonCheck() {
	return 1;
}
/**
 * @brief Draw asset according to the direction it is facing.
 * 
 * @param shader
 * @param vao
 * @param window
 */
void Pacman::draw(GLuint shader, GLuint vao, GLFWwindow *window) {
    auto samplerSlotLocation0 = glGetUniformLocation(shader, "uTextureA");
	glUseProgram(shader);
	glBindVertexArray(vao);
	//change direction
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		direction = 0;
	} 
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		direction = 1;
	} 
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		direction = 2;
	} 
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		direction = 3;
	}
	//move asset
	mov(shader);
	glUniform1i(samplerSlotLocation0, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
}
/**
 * @brief Move the asset to a direction until collision.
 * 
 * @param shader
 */
void Pacman::mov(GLuint shader) {
	//move up 		(W)
	if(direction == 0) {
		transform(gPacX, (gPacY += gColInc / 100), shader);
	//move right 	(A)
	} else if (direction == 1) {
		transform((gPacX -= gRowInc / 100), gPacY, shader);
	//move down		(S)
	} else if (direction == 2) {
		transform(gPacX, (gPacY -= gColInc / 100), shader);
	//move left		(D)
	} else if (direction == 3) {
		transform((gPacX += gRowInc / 100), gPacY, shader);
	}
}
