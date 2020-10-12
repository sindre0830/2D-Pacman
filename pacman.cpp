/* library */
#include "header/pacman.h"
#include "shader/character.h"
#include "header/levelData.h"
#include <iostream>
/* dictionary */
extern enum Direction {UP, LEFT, DOWN, RIGHT};
extern enum Target {PELLET, WALL, PACMAN, EMPTY};
/* global data */
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
	if (g_level.pacmanCol == 0) {
		yTex = 0.5f;
		direction = UP;
	} else if (g_level.pacmanRow == g_level.arrWidth - 1) {
		yTex = 0.25f;
		direction = LEFT;
	} else if (g_level.pacmanCol == g_level.arrHeight - 1) {
		yTex = 0.75f;
		direction = DOWN;
	} else if(g_level.pacmanRow == 0) {
		yTex = 0.0f;
		direction = RIGHT;
	}
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
			if (g_level.arr[i][j] == PACMAN) {
				g_level.pacmanCol = i;
				g_level.pacmanRow = j;
				return;
			}
		}
	}
}
/**
 * @brief Move the asset to a direction until collision.
 * 
 * @param shader
 */
void Pacman::mov(Pellet &pellet) {
	if(counter < speed) changeDirection = false;
	switch (direction) {
		case UP:
			if(movUp(g_level.pacmanRow, g_level.pacmanCol)) {
				//check if there is a pellet
				if(g_level.arr[++g_level.pacmanCol][g_level.pacmanRow] == 4) {
					eat(pellet);
					g_level.magicEffect = true;
				} else if(g_level.arr[g_level.pacmanCol][g_level.pacmanRow] == PELLET) eat(pellet);
			} else if(g_level.arr[g_level.pacmanCol + 1][g_level.pacmanRow] == WALL) changeDirection = true;
			break;
		case LEFT:
			if(movLeft(g_level.pacmanRow, g_level.pacmanCol)) {
				//check if there is a pellet
				if(g_level.arr[g_level.pacmanCol][--g_level.pacmanRow] == 4) {
					eat(pellet);
					g_level.magicEffect = true;
				} else if(g_level.arr[g_level.pacmanCol][g_level.pacmanRow] == PELLET) eat(pellet);
			} else if(g_level.arr[g_level.pacmanCol][g_level.pacmanRow - 1] == WALL) changeDirection = true;	
			break;
		case DOWN:
			if(movDown(g_level.pacmanRow, g_level.pacmanCol)) {
				//check if there is a pellet
				if(g_level.arr[--g_level.pacmanCol][g_level.pacmanRow] == 4) {
					eat(pellet);
					g_level.magicEffect = true;
				} else if(g_level.arr[g_level.pacmanCol][g_level.pacmanRow] == PELLET) eat(pellet);
			} else if(g_level.arr[g_level.pacmanCol - 1][g_level.pacmanRow] == WALL) changeDirection = true;
			break;
		case RIGHT:
			if(movRight(g_level.pacmanRow, g_level.pacmanCol)) {
				//check if there is a pellet
				if(g_level.arr[g_level.pacmanCol][++g_level.pacmanRow] == 4) {
					eat(pellet);
					g_level.magicEffect = true;
				} else if(g_level.arr[g_level.pacmanCol][g_level.pacmanRow] == PELLET) eat(pellet);
			} else if(g_level.arr[g_level.pacmanCol][g_level.pacmanRow + 1] == WALL) changeDirection = true;
			break;
	}
	animate();
}

void Pacman::animate() {
	if (counter == speed * 0.25f) {
		translateTex(0.167f, yTex);
	} else if (counter == speed * 0.5f) {
		translateTex(0.333f, yTex);
	} else if (counter == speed * 0.75f) {
		translateTex(0.5f, yTex);
	} else if (counter >= speed) {
		translateTex(0.0f, yTex);
		changeDirection = true;
		counter = 0;
	}
}

void Pacman::eat(Pellet &pellet) {
	//replace pellet in array
	g_level.arr[g_level.pacmanCol][g_level.pacmanRow] = EMPTY;
	//increment score
	g_level.score++;
	//hide pellet
	pellet.hidePellet(g_level.pacmanCol, g_level.pacmanRow);
	if(g_level.score == g_level.pelletSize) {
		g_gameover = true;
		std::cout << "Congratulations, you won...\n";
	}
}

void Pacman::inputDirection(GLFWwindow *window) {
	//change direction on key press if pacman has completed a translation and it wont hit a wall
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && changeDirection && g_level.pacmanCol + 1 < g_level.arrHeight && g_level.arr[g_level.pacmanCol + 1][g_level.pacmanRow] != WALL) {
		yTex = 0.5f;
		translateTex(0.0f, yTex);
		direction = UP;
	} else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && changeDirection && g_level.pacmanRow - 1 >= 0 && g_level.arr[g_level.pacmanCol][g_level.pacmanRow - 1] != WALL) {
		yTex = 0.25f;
		translateTex(0.0f, yTex);
		direction = LEFT;
	} else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && changeDirection && g_level.pacmanCol - 1 >= 0 && g_level.arr[g_level.pacmanCol - 1][g_level.pacmanRow] != WALL) {
		yTex = 0.75f;
		translateTex(0.0f, yTex);
		direction = DOWN;
	} else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && changeDirection && g_level.pacmanRow + 1 < g_level.arrWidth && g_level.arr[g_level.pacmanCol][g_level.pacmanRow + 1] != WALL) {
		yTex = 0.0f;
		translateTex(0.0f, yTex);
		direction = RIGHT;
	}
}
