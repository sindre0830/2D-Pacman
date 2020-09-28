/* libraries */
#include "headers/pacman.h"
#include <glm/gtx/matrix_transform_2d.hpp>
/* global variables */
extern int gCol, gRow, gScore, gPelletSize;
extern float gRowInc, gColInc, gPacX, gPacY, gPacRow, gPacCol;
extern std::vector<std::vector<int>> gLevel;
extern bool atePellet;
/**
 * @brief Destroy the Pacman object
 */
Pacman::~Pacman() {}
/**
 * @brief Declare variables on construction of Pacman object.
 */
Pacman::Pacman() {
	direction = 3;
	clock = 0;
	speed = 50.0f;
}
/**
 * @brief Generate Pac-Man from the 2D array to the window.
 * 
 * @return GLuint 
 */
GLuint Pacman::genAsset() {
    std::vector<GLfloat> arr = {
		//position								//color                 //texture coord	//Down https://learnopengl.com/Getting-started/Textures
		/*gPacX,				gPacY + gColInc,*/-0.5f, 0.5f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	//0.02f,	0.03f,
		/*gPacX,				gPacY,			*/-0.5f, -0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	//0.15f,	0.03f,
		/*gPacX + gRowInc,	gPacY,				*/0.5f, -0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	//0.15f,	0.245f,
		/*gPacX + gRowInc,	gPacY + gColInc,	*/0.5f, 0.5f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f	//0.02f,	0.245f
    };
    std::vector<GLuint> arr_indices = {0, 1, 2, 0, 2, 3};
	//reset values to be used in Pacman::draw()
	gPacX = 0.0f;
	gPacY = 0.0f;
    return createVAO(arr, arr_indices);
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
	//move asset
	//mov(shader);
	//change direction on key press if clock has reset and it wont hit a wall
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && clock == 0 && gPacCol <= gCol && gLevel[gPacCol + 1][gPacRow] != 1) {
		texFocus(0.0f, 0.25f, shader);
		direction = 0;
	} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && clock == 0 && gPacRow >= 0 && gLevel[gPacCol][gPacRow - 1] != 1) {
		texFocus(0.0f, 0.75f, shader);
		direction = 1;
	} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && clock == 0 && gPacCol >= 0 && gLevel[gPacCol - 1][gPacRow] != 1) {
		texFocus(0.0f, 0.0f, shader);
		direction = 2;
	} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && clock == 0 && gPacRow <= gRow && gLevel[gPacCol][gPacRow + 1] != 1) {
		texFocus(0.0f, 0.5f, shader);
		direction = 3;
	}
	//update clock
	if(clock == (int)(speed)) {
		clock = 0;
	} else clock++;

	glUniform1i(samplerSlotLocation0, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
}
/**
 * @brief Move the asset to a direction until collision.
 * 
 * @param shader
 */
void Pacman::mov(GLuint shader) {
	//move up (W)
	if(direction == 0) {
		//check if next location will be a wall or go out of bound
		if(gPacCol + 1 <= gCol && gLevel[gPacCol + 1][gPacRow] != 1) {
			//translate up on the y-axis
			transform(gPacX, (gPacY += gColInc / speed), shader);
			//update grid
			if(clock == (int)(speed)) {
				if(gPacCol + 1 <= gCol) {
					if(gLevel[++gPacCol][gPacRow] == 0) {
						gScore++;
						gPelletSize--;
						atePellet = true;
					}
					gLevel[gPacCol][gPacRow] = 2;
				}
				//reset clock
				clock = 0;
			}
		} else clock = 0;
	//move left (A)
	} else if (direction == 1) {
		//check if next location will be a wall
		if(gPacRow - 1 >= 0 && gLevel[gPacCol][gPacRow - 1] != 1) {
			//translate left on the x-axis
			transform((gPacX -= gRowInc / speed), gPacY, shader);
			//update grid
			if(clock == (int)(speed)) {
				if(gPacRow - 1 >= 0) {
					if(gLevel[gPacCol][--gPacRow] == 0) {
						gScore++;
						gPelletSize--;
						atePellet = true;
					}
					gLevel[gPacCol][gPacRow] = 2;
				}
				//reset clock
				clock = 0;	
			}
		} else clock = 0;
	//move down (S)
	} else if (direction == 2) {
		//check if next location will be a wall
		if(gPacCol - 1 >= 0 && gLevel[gPacCol - 1][gPacRow] != 1) {
			//translate down on the y-axis
			transform(gPacX, (gPacY -= gColInc / speed), shader);
			//update grid
			if(clock == (int)(speed)) {
				if(gPacCol - 1 >= 0) {
					if(gLevel[--gPacCol][gPacRow] == 0) {
						gScore++;
						gPelletSize--;
						atePellet = true;
					}
					gLevel[gPacCol][gPacRow] = 2;
				}
				//reset clock
				clock = 0;
			}
		} else clock = 0;
	//move right (D)
	} else if (direction == 3) {
		//check if next location will be a wall
		if(gPacRow + 1 < gRow && gLevel[gPacCol][gPacRow + 1] != 1) {
			//translate right on the x-axis
			transform((gPacX += gRowInc / speed), gPacY, shader);
			//update grid
			if(clock == (int)(speed)) {
				if(gPacRow + 1 < gRow) {
					if(gLevel[gPacCol][++gPacRow] == 0) {
						gScore++;
						gPelletSize--;
						atePellet = true;
					}
					gLevel[gPacCol][gPacRow] = 2;
				}
				//reset clock
				clock = 0;
			}
		}  else clock = 0;
	}
}

void Pacman::texFocus(const float x, const float y, const GLuint shader) {
	//Translation moves our object
	glm::mat3 translation = glm::translate(glm::mat3(1), glm::vec2(x, y));
	GLuint transformationmat = glGetUniformLocation(shader, "u_TransformationTex");
	//Send data from matrices to uniform
	glUniformMatrix3fv(transformationmat, 1, false, glm::value_ptr(translation));
}
