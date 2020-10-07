/* libraries */
#include "header/pacman.h"
#include "shader/asset.h"
#include "header/pellet.h"
#include <iostream>
/* global variables */
extern int  g_levelRow, g_levelCol, g_wallSize, g_pelletSize, g_gameScore;
extern float g_rowInc, g_colInc;
extern std::vector<std::vector<int>> g_level;
extern double g_deltaTime;
extern Pellet pellet;
/**
 * @brief Destroy the Pacman object
 */
Pacman::~Pacman() {
    glDeleteProgram(pacmanShaderProgram);
    glDeleteTextures(1, &texture0);
    cleanVAO(pacmanVAO);
}
/**
 * @brief Declare variables on construction of Pacman object.
 */
Pacman::Pacman() {
	direction = 3;
	clock = 0;
	speed = 50.0f;
	n = 0;
    getPosition();
    pacmanVAO = genObject();

    pacmanShaderProgram = compileShader(assetVertexShaderSrc, assetFragmentShaderSrc);
	//specify the layout of the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    //load the texture image, create OpenGL texture, and bind it to the current context
    texture0 = loadTexture("sprite/pacman.png", 0);
}
/**
 * @brief Generate Pac-Man from the 2D array to the window.
 * 
 * @return GLuint 
 */
GLuint Pacman::genObject() {
    std::vector<GLfloat> arr = genCoordinates(xPos, yPos, .0f, .0f);
    std::vector<GLuint> arrIndices = genIndices(1);
	//reset values to be used in Pacman::draw()
	xPos = 0.0f;
	yPos = 0.0f;
    return createVAO(arr, arrIndices);
}

void Pacman::getPosition() {
	/* local variables */
	float
		x = -1.0f,
		y = -1.0f;
	for (int i = 0; i < g_levelCol; i++, x = -1.0f, y += g_colInc) {
		for (int j = 0; j < g_levelRow; j++, x += g_rowInc) {
			if (g_level[i][j] == 2) {
				xPos = x;
				yPos = y;
				rowPos = j;
				colPos = i;
				return;
			}
		}
	}
}

void Pacman::drawObject(GLFWwindow *window) {
    draw(pacmanShaderProgram, pacmanVAO, window);
}
/**
 * @brief Draw asset according to the direction it is facing.
 * 
 * @param shader
 * @param vao
 * @param window
 */
void Pacman::draw(GLuint &shader, GLuint &vao, GLFWwindow *window) {
    auto samplerSlotLocation0 = glGetUniformLocation(shader, "uTextureA");
	glUseProgram(shader);
	glBindVertexArray(vao);
	//move asset
	//movObject();
	//change direction on key press if clock has reset and it wont hit a wall
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && changeDirection && colPos + 1 < g_levelCol && g_level[colPos + 1][rowPos] != 1) {
		translateTex(0.0f, 0.5f, shader);
		direction = 0;
	} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && changeDirection && rowPos - 1 >= 0 && g_level[colPos][rowPos - 1] != 1) {
		translateTex(0.0f, 0.25f, shader);
		direction = 1;
	} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && changeDirection && colPos - 1 >= 0 && g_level[colPos - 1][rowPos] != 1) {
		translateTex(0.0f, 0.75f, shader);
		direction = 2;
	} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && changeDirection && rowPos + 1 < g_levelRow && g_level[colPos][rowPos + 1] != 1) {
		translateTex(0.0f, 0.0f, shader);
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
void Pacman::movObject() {
	//move up (W)
	if(direction == 0) {
		//check if next location will be a wall or go out of bound
		if(colPos + 1 < g_levelCol && g_level[colPos + 1][rowPos] != 1) {
			//update grid
			if(g_deltaTime >= 60.0) {
				if(colPos + 1 <= g_levelCol) {
					if(g_level[++colPos][rowPos] == 0) {
						g_gameScore++;
						pellet.hidePellet(colPos, rowPos);
					}
					g_level[colPos][rowPos] = 2;
				}
				clock = 0;
				changeDirection = true;
			} else {
				changeDirection = false;
				//translate up on the y-axis
				translatePos(xPos, (yPos += g_colInc), pacmanShaderProgram);
			}
		} else changeDirection = true;
	//move left (A)
	} else if (direction == 1) {
		//check if next location will be a wall
		if(rowPos - 1 >= 0 && g_level[colPos][rowPos - 1] != 1) {
			//update grid
			if(g_deltaTime >= 60.0) {
				if(rowPos - 1 >= 0) {
					if(g_level[colPos][--rowPos] == 0) {
						g_gameScore++;
						pellet.hidePellet(colPos, rowPos);
					}
					g_level[colPos][rowPos] = 2;
				}
				clock = 0;
				changeDirection = true;	
			} else {
				changeDirection = false;
				//translate left on the x-axis
				translatePos((xPos -= g_rowInc), yPos, pacmanShaderProgram);
			}
		} else changeDirection = true;
	//move down (S)
	} else if (direction == 2) {
		//check if next location will be a wall
		if(colPos - 1 >= 0 && g_level[colPos - 1][rowPos] != 1) {
			//update grid
			if(g_deltaTime >= 60.0) {
				if(colPos - 1 >= 0) {
					if(g_level[--colPos][rowPos] == 0) {
						g_gameScore++;
						pellet.hidePellet(colPos, rowPos);
					}
					g_level[colPos][rowPos] = 2;
				}
				clock = 0;
				changeDirection = true;
			} else {
				changeDirection = false;
				//translate up on the y-axis
				translatePos(xPos, (yPos -= g_colInc), pacmanShaderProgram);
			}
		} else changeDirection = true;
	//move right (D)
	} else if (direction == 3) {
		movRight();
	}
}

void Pacman::movRight() {
	//check if next location will be a wall or out of bound
	if(rowPos + 1 < g_levelRow && g_level[colPos][rowPos + 1] != 1) {
		//translate up on the x-axis
		translatePos((xPos += g_rowInc / 40), yPos, pacmanShaderProgram);
		n++;
		//update grid if it has completed one square
		if(n == 40) {
			if(rowPos + 1 < g_levelRow) {
				//animate pacman
				translateTex(0.0f, 0.0f, pacmanShaderProgram);
				//check if there is a pellet
				if(g_level[colPos][++rowPos] == 0) {
					g_gameScore++;
					pellet.hidePellet(colPos, rowPos);
				}
				g_level[colPos][rowPos] = 2;
			}
			n = 0;
			changeDirection = true;
		} else if (n == 30) {
			translateTex(0.5f, 0.0f, pacmanShaderProgram);
		} else if (n == 20) {
			translateTex(0.333f, 0.0f, pacmanShaderProgram);
		} else if (n == 10) {
			translateTex(0.167f, 0.0f, pacmanShaderProgram);
		} else changeDirection = false;
	}
}
