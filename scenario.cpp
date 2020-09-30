#include "header/scenario.h"

extern int  g_levelRow, g_levelCol;
extern float g_rowInc, g_colInc;
extern std::vector<std::vector<int>> g_level;

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
void Scenario::draw(const GLuint &shader, const GLuint &vao, const int n) {
	glUseProgram(shader);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, (6 * n), GL_UNSIGNED_INT, (const void*)0);
}

std::vector<GLfloat> Scenario::genCoordinates(const int target, const float xSize, const float ySize) {
    /* local data */
	float
		x = -1.0f,
		y = -1.0f,
		z = 0.0f;
	std::vector<GLfloat> arr;
	//fills in arr with coordinates
	for (int i = 0; i < g_levelCol; i++, x = -1.0f, y += g_colInc) {
		for (int j = 0; j < g_levelRow; j++, x += g_rowInc) {
			if (g_level[i][j] == target) {
				//top left coordinate
				arr.push_back(x + xSize);
				arr.push_back((y + g_colInc) - ySize);
				arr.push_back(z);
				//bottom left coordinate
				arr.push_back(x + xSize);
				arr.push_back(y + ySize);
				arr.push_back(z);
				//bottom right coordinate
				arr.push_back((x + g_rowInc) - xSize);
				arr.push_back(y + ySize);
				arr.push_back(z);
				//top right coordinate
				arr.push_back((x + g_rowInc) - xSize);
				arr.push_back((y + g_colInc) - ySize);
				arr.push_back(z);
			}
		}
	}
	return arr;
}
