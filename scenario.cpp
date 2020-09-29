/* libraries */
#include "headers/scenario.h"
/* global variables */
extern int gCol, gRow, gWallSize, gPelletSize;
extern float gRowInc, gColInc, gPacX, gPacY, gPacRow, gPacCol;
extern std::vector<std::vector<int>> gLevel;
/**
 * @brief Destroy the Scenario object
 */
Scenario::~Scenario() {}
/**
 * @brief Draw VAO and shader program with custom color.
 * 
 * @param shader 	shader program
 * @param vao 		virtual array object
 * @param n 		size
 * @param r 		red
 * @param g 		green
 * @param b 		blue
 */
void Scenario::drawObject(GLuint shader, GLuint vao, int n, float r, float g, float b) {
	auto vertexColorLocation = glGetUniformLocation(shader, "u_Color");
	glUseProgram(shader);
	glBindVertexArray(vao);
	glUniform4f(vertexColorLocation, r, g, b, 1.0f);
	glDrawElements(GL_TRIANGLES, (6 * n), GL_UNSIGNED_INT, (const void*)0);
}
