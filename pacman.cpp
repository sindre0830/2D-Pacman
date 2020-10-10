/* libraries */
#include "header/pacman.h"
#include "shader/character.h"
#include "header/levelData.h"
#include "header/pellet.h"
#include <iostream>
/* global variables */
extern LevelData g_level;
extern Pellet pellet;
extern bool g_gameover;
/**
 * @brief Destroy the Pacman object
 */
Pacman::~Pacman() {
    glDeleteProgram(pacmanShaderProgram);
    glDeleteTextures(1, &texture);
    cleanVAO(pacmanVAO);
}
/**
 * @brief Declare variables on construction of Pacman object.
 */
Pacman::Pacman() {
	direction = 3;
    getPosition();
    pacmanVAO = genObject();
    pacmanShaderProgram = compileShader(characterVertexShaderSrc, characterFragmentShaderSrc);
	//specify the layout of the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    //load the texture image, create OpenGL texture, and bind it to the current context
    texture = loadTexture("sprite/pacman.png", 0);
}
/**
 * @brief Generate Pac-Man from the 2D array to the window.
 * 
 * @return GLuint 
 */
GLuint Pacman::genObject() {
    std::vector<GLfloat> arr = genCoordinates(rowPos, colPos);
    std::vector<GLuint> arrIndices = genIndices(1);
    return createVAO(arr, arrIndices);
}

void Pacman::getPosition() {
	for (int i = 0; i < g_level.arrHeight; i++) {
		for (int j = 0; j < g_level.arrWidth; j++) {
			if (g_level.arr[i][j] == 2) {
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
    auto samplerSlotLocation = glGetUniformLocation(shader, "uTexture");
	glUseProgram(shader);
	glBindVertexArray(vao);
	//change direction on key press if clock has reset and it wont hit a wall
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && changeDirection && colPos + 1 < g_level.arrHeight && g_level.arr[colPos + 1][rowPos] != 1) {
		yTex = 0.5f;
		translateTex(0.0f, yTex, shader);
		direction = 0;
	} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && changeDirection && rowPos - 1 >= 0 && g_level.arr[colPos][rowPos - 1] != 1) {
		yTex = 0.25f;
		translateTex(0.0f, yTex, shader);
		direction = 1;
	} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && changeDirection && colPos - 1 >= 0 && g_level.arr[colPos - 1][rowPos] != 1) {
		yTex = 0.75f;
		translateTex(0.0f, yTex, shader);
		direction = 2;
	} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && changeDirection && rowPos + 1 < g_level.arrWidth && g_level.arr[colPos][rowPos + 1] != 1) {
		yTex = 0.0f;
		translateTex(0.0f, yTex, shader);
		direction = 3;
	}
	glUniform1i(samplerSlotLocation, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
}
/**
 * @brief Move the asset to a direction until collision.
 * 
 * @param shader
 */
void Pacman::movObject() {
	if(g_level.ghostPos[colPos][rowPos]) {
		g_gameover = true;
			std::cout << "Better luck next time...\n";
	}
	//move up (W)
	if(direction == 0) {
		if(movUp(rowPos, colPos, xPos, yPos, speed, pacmanShaderProgram)) {
			n++;
			changeDirection = false;
		}
		//update grid if it has completed one square
		if(n == speed) {
			//check if there is a pellet
			if(g_level.arr[++colPos][rowPos] == 0) {
				g_level.score++;
				pellet.hidePellet(colPos, rowPos);
			}
			g_level.arr[colPos][rowPos] = 2;
		}
	//move left (A)
	} else if (direction == 1) {
		if(movLeft(rowPos, colPos, xPos, yPos, speed, pacmanShaderProgram)) {
			n++;
			changeDirection = false;
		}
		//update grid if it has completed one square
		if(n == speed) {
			//check if there is a pellet
			if(g_level.arr[colPos][--rowPos] == 0) {
				g_level.score++;
				pellet.hidePellet(colPos, rowPos);
			}
			g_level.arr[colPos][rowPos] = 2;
		}
	//move down (S)
	} else if (direction == 2) {
		if(movDown(rowPos, colPos, xPos, yPos, speed, pacmanShaderProgram)) {
			n++;
			changeDirection = false;
		}
		//update grid if it has completed one square
		if(n == speed) {
			//check if there is a pellet
			if(g_level.arr[--colPos][rowPos] == 0) {
				g_level.score++;
				pellet.hidePellet(colPos, rowPos);
			}
			g_level.arr[colPos][rowPos] = 2;
		}
	//move right (D)
	} else if (direction == 3) {
		if(movRight(rowPos, colPos, xPos, yPos, speed, pacmanShaderProgram)) {
			n++;
			changeDirection = false;
		}
		//update grid if it has completed one square
		if(n == speed) {
			//check if there is a pellet
			if(g_level.arr[colPos][++rowPos] == 0) {
				g_level.score++;
				pellet.hidePellet(colPos, rowPos);
			}
			g_level.arr[colPos][rowPos] = 2;
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
		if(g_level.score == g_level.pelletSize) {
			g_gameover = true;
			std::cout << "Congratulations, you won...\n";
		}
		n = 0;
	}
}
