/* libraries */
#include "header/pacman.h"
#include "shader/character.h"
#include "header/levelData.h"
#include <iostream>
/* global variables */
extern LevelData g_level;
extern bool g_gameover;
/**
 * @brief Destroy the Pacman object
 */
Pacman::~Pacman() {}
/**
 * @brief Declare variables on construction of Pacman object.
 */
Pacman::Pacman() {
	//set starting postions
    getPosition();
	//set starting direction
	direction = 3;
	//generate VAO and shader program
    entityVAO = genObject(g_level.pacmanRow, g_level.pacmanCol);
    entityShaderProgram = compileShader(characterVertexShaderSrc, characterFragmentShaderSrc);
	//specify the layout of the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    //load the texture image, create OpenGL texture, and bind it to the current context
    texture = loadTexture("sprite/pacman.png", 0);
}

void Pacman::getPosition() {
	for (int i = 0; i < g_level.arrHeight; i++) {
		for (int j = 0; j < g_level.arrWidth; j++) {
			if (g_level.arr[i][j] == 2) {
				g_level.pacmanCol = i;
				g_level.pacmanRow = j;
				return;
			}
		}
	}
}

void Pacman::drawObject(GLFWwindow *window) {
    draw(entityShaderProgram, entityVAO, window);
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
	//change direction on key press if pacman has completed a translation and it wont hit a wall
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && changeDirection && g_level.pacmanCol + 1 < g_level.arrHeight && g_level.arr[g_level.pacmanCol + 1][g_level.pacmanRow] != 1) {
		yTex = 0.5f;
		translateTex(0.0f, yTex, shader);
		direction = 0;
	} else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && changeDirection && g_level.pacmanRow - 1 >= 0 && g_level.arr[g_level.pacmanCol][g_level.pacmanRow - 1] != 1) {
		yTex = 0.25f;
		translateTex(0.0f, yTex, shader);
		direction = 1;
	} else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && changeDirection && g_level.pacmanCol - 1 >= 0 && g_level.arr[g_level.pacmanCol - 1][g_level.pacmanRow] != 1) {
		yTex = 0.75f;
		translateTex(0.0f, yTex, shader);
		direction = 2;
	} else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && changeDirection && g_level.pacmanRow + 1 < g_level.arrWidth && g_level.arr[g_level.pacmanCol][g_level.pacmanRow + 1] != 1) {
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
void Pacman::movObject(Pellet &pellet) {
	switch (direction) {
		case 0:
			if(movUp(g_level.pacmanRow, g_level.pacmanCol, xPos, yPos, speed, entityShaderProgram)) {
				counter++;
				changeDirection = false;
			}
			//update grid if it has completed one square
			if(counter == speed) {
				//check if there is a pellet
				if(g_level.arr[++g_level.pacmanCol][g_level.pacmanRow] == 0) eatPellet(pellet);
			}
			break;
		case 1:
			if(movLeft(g_level.pacmanRow, g_level.pacmanCol, xPos, yPos, speed, entityShaderProgram)) {
				counter++;
				changeDirection = false;
			}
			//update grid if it has completed one square
			if(counter == speed) {
				//check if there is a pellet
				if(g_level.arr[g_level.pacmanCol][--g_level.pacmanRow] == 0) eatPellet(pellet);
			}			
			break;
		case 2:
			if(movDown(g_level.pacmanRow, g_level.pacmanCol, xPos, yPos, speed, entityShaderProgram)) {
				counter++;
				changeDirection = false;
			}
			//update grid if it has completed one square
			if(counter == speed) {
				//check if there is a pellet
				if(g_level.arr[--g_level.pacmanCol][g_level.pacmanRow] == 0) eatPellet(pellet);
			}			
			break;
		case 3:
			if(movRight(g_level.pacmanRow, g_level.pacmanCol, xPos, yPos, speed, entityShaderProgram)) {
				counter++;
				changeDirection = false;
			}
			//update grid if it has completed one square
			if(counter == speed) {
				//check if there is a pellet
				if(g_level.arr[g_level.pacmanCol][++g_level.pacmanRow] == 0) eatPellet(pellet);
			}			
			break;
	}
	animate();
}

void Pacman::animate() {
	if (counter == speed * 0.25f) {
		translateTex(0.167f, yTex, entityShaderProgram);
	} else if (counter == speed * 0.5f) {
		translateTex(0.333f, yTex, entityShaderProgram);
	} else if (counter == speed * 0.75f) {
		translateTex(0.5f, yTex, entityShaderProgram);
	} else if (counter == speed) {
		translateTex(0.0f, yTex, entityShaderProgram);
		changeDirection = true;
		counter = 0;
	}
}

void Pacman::eatPellet(Pellet &pellet) {
	g_level.score++;
	pellet.hidePellet(g_level.pacmanCol, g_level.pacmanRow);
	g_level.arr[g_level.pacmanCol][g_level.pacmanRow] = 2;
	if(g_level.score == g_level.pelletSize) {
		g_gameover = true;
		std::cout << "Congratulations, you won...\n";
	}
}
