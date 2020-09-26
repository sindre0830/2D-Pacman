/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "headers/pacman.h"
/**
 * Destroy the 'Pacman' object.
 */
Pacman::~Pacman() {}
/**
 * Generate pacman.
 */
GLuint Pacman::genAsset() {
    GLfloat square[4 * 7] = {
		//position      //color                 //texture coord
		-0.5f,	-0.5f,	1.0f,	1.0f,	1.0f,	0.02f,	0.03f,
		0.5f,	-0.5f,	1.0f,	1.0f,	1.0f,	0.15f,	0.03f,
		0.5f,	0.5f,	1.0f,	1.0f,	1.0f,	0.15f,	0.245f,
		-0.5f,	0.5f,	1.0f,	1.0f,	1.0f,	0.02f,	0.245f
    };

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
void Pacman::mov() {

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
void Pacman::draw() {

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