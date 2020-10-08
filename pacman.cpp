/* libraries */
#include "header/pacman.h"
#include "shader/asset.h"
#include "header/pellet.h"
#include <iostream>
/* global variables */
extern int  g_levelRow, g_levelCol, g_wallSize, g_pelletSize, g_gameScore;
extern double g_rowInc, g_colInc;
extern std::vector<std::vector<int>> g_level;
extern std::vector<std::vector<bool>> g_ghostPos;
extern Pellet pellet;
extern bool g_gameover;
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
	speed = 20;
	n = 0;
	yTex = 0.0f;
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
		yTex = 0.5f;
		translateTex(0.0f, yTex, shader);
		direction = 0;
	} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && changeDirection && rowPos - 1 >= 0 && g_level[colPos][rowPos - 1] != 1) {
		yTex = 0.25f;
		translateTex(0.0f, yTex, shader);
		direction = 1;
	} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && changeDirection && colPos - 1 >= 0 && g_level[colPos - 1][rowPos] != 1) {
		yTex = 0.75f;
		translateTex(0.0f, yTex, shader);
		direction = 2;
	} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && changeDirection && rowPos + 1 < g_levelRow && g_level[colPos][rowPos + 1] != 1) {
		yTex = 0.0f;
		translateTex(0.0f, yTex, shader);
		direction = 3;
	}
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
		movUp();
		//update grid if it has completed one square
		if(n == speed) {
			if(colPos + 1 <= g_levelCol) {
				//check if there is a pellet
				if(g_level[++colPos][rowPos] == 0) {
					g_gameScore++;
					pellet.hidePellet(colPos, rowPos);
				}
				g_level[colPos][rowPos] = 2;
			}
		}
	//move left (A)
	} else if (direction == 1) {
		movLeft();
		//update grid if it has completed one square
		if(n == speed) {
			if(rowPos - 1 >= 0) {
				//check if there is a pellet
				if(g_level[colPos][--rowPos] == 0) {
					g_gameScore++;
					pellet.hidePellet(colPos, rowPos);
				}
				g_level[colPos][rowPos] = 2;
			}
		}
	//move down (S)
	} else if (direction == 2) {
		movDown();
		//update grid if it has completed one square
		if(n == speed) {
			if(colPos - 1 >= 0) {
				//check if there is a pellet
				if(g_level[--colPos][rowPos] == 0) {
					g_gameScore++;
					pellet.hidePellet(colPos, rowPos);
				}
				g_level[colPos][rowPos] = 2;
			}
		}
	//move right (D)
	} else if (direction == 3) {
		movRight();
		//update grid if it has completed one square
		if(n == speed) {
			if(rowPos + 1 < g_levelRow) {
				//check if there is a pellet
				if(g_level[colPos][++rowPos] == 0) {
					g_gameScore++;
					pellet.hidePellet(colPos, rowPos);
				}
				std::cout << "pacman moving\n";
				g_level[colPos][rowPos] = 2;
			}
		}
	}
	if (n == speed * 0.25f) {
		translateTex(0.167f, yTex, pacmanShaderProgram);
	} else if (n == speed * 0.5f) {
		translateTex(0.333f, yTex, pacmanShaderProgram);
	} else if (n == speed * 0.75f) {
		translateTex(0.5f, yTex, pacmanShaderProgram);
	} else if (n == speed) {
		translateTex(0.0f, yTex, pacmanShaderProgram);
		changeDirection = true;
		if(g_gameScore == g_pelletSize) g_gameover = true;
		if(g_ghostPos[colPos][rowPos]) g_gameover = true;
		n = 0;
	}
}

void Pacman::movUp() {
	//check if next location will be a wall or out of bound
	if(colPos + 1 < g_levelCol && g_level[colPos + 1][rowPos] != 1) {
		n++;
		changeDirection = false;
		//translate up on the x-axis
		translatePos(xPos, (yPos += g_colInc / (double)(speed)), pacmanShaderProgram);
	}
}

void Pacman::movLeft() {
	//check if next location will be a wall or out of bound
	if(rowPos - 1 >= 0 && g_level[colPos][rowPos - 1] != 1) {
		n++;
		changeDirection = false;
		//translate up on the x-axis
		translatePos((xPos -= g_rowInc / (double)(speed)), yPos, pacmanShaderProgram);
	}
}

void Pacman::movDown() {
	//check if next location will be a wall or out of bound
	if(colPos - 1 >= 0 && g_level[colPos - 1][rowPos] != 1) {
		n++;
		changeDirection = false;
		//translate up on the x-axis
		translatePos(xPos, (yPos -= g_colInc / (double)(speed)), pacmanShaderProgram);
	}
}

void Pacman::movRight() {
	//check if next location will be a wall or out of bound
	if(rowPos + 1 < g_levelRow && g_level[colPos][rowPos + 1] != 1) {
		n++;
		changeDirection = false;
		//translate up on the x-axis
		translatePos((xPos += g_rowInc / (double)(speed)), yPos, pacmanShaderProgram);
	}
}
