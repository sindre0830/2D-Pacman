/* library */
#include "header/pacman.h"
#include "shader/character.h"
#include "header/levelData.h"
#include <iostream>
/* dictionary */
extern enum Direction {UP, LEFT, DOWN, RIGHT};
extern enum Target {PELLET, WALL, PACMAN, EMPTY, MAGICPELLET};
/* global data */
extern LevelData *g_level;
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
	if (g_level->pacmanCol == 0) {
		yTex = 0.5f;
		direction = UP;
	} else if (g_level->pacmanRow == g_level->gridWidth - 1) {
		yTex = 0.25f;
		direction = LEFT;
	} else if (g_level->pacmanCol == g_level->gridHeight - 1) {
		yTex = 0.75f;
		direction = DOWN;
	} else if(g_level->pacmanRow == 0) {
		yTex = 0.0f;
		direction = RIGHT;
	}
	//generate VAO and shader program
    entityShaderProgram = compileShader(characterVertexShaderSrc, characterFragmentShaderSrc);
	std::vector<GLfloat> arr = genCoordinates(g_level->pacmanRow, g_level->pacmanCol);
    entityVAO = genObject(arr, 1);
	//specify the layout of the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
}

void Pacman::getPosition() {
	for (int i = 0; i < g_level->gridHeight; i++) {
		for (int j = 0; j < g_level->gridWidth; j++) {
			if (g_level->grid[i][j] == PACMAN) {
				g_level->pacmanCol = i;
				g_level->pacmanRow = j;
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
	if(changeDirection && counter < speed) changeDirection = false;
	switch (direction) {
		case UP:
			if(movUp(g_level->pacmanRow, g_level->pacmanCol)) {
				//check if there is a pellet
				if(g_level->grid[++g_level->pacmanCol][g_level->pacmanRow] == MAGICPELLET) {
					g_level->magicEffect = true;
					eat(pellet);
				} else if(g_level->grid[g_level->pacmanCol][g_level->pacmanRow] == PELLET) eat(pellet);
			} else if(g_level->grid[g_level->pacmanCol + 1][g_level->pacmanRow] == WALL) changeDirection = true;
			break;
		case LEFT:
			if(movLeft(g_level->pacmanRow, g_level->pacmanCol)) {
				//check if there is a pellet
				if(g_level->grid[g_level->pacmanCol][--g_level->pacmanRow] == MAGICPELLET) {
					g_level->magicEffect = true;
					eat(pellet);
				} else if(g_level->grid[g_level->pacmanCol][g_level->pacmanRow] == PELLET) eat(pellet);
			} else if(g_level->grid[g_level->pacmanCol][g_level->pacmanRow - 1] == WALL) changeDirection = true;	
			break;
		case DOWN:
			if(movDown(g_level->pacmanRow, g_level->pacmanCol)) {
				//check if there is a pellet
				if(g_level->grid[--g_level->pacmanCol][g_level->pacmanRow] == MAGICPELLET) {
					g_level->magicEffect = true;
					eat(pellet);
				} else if(g_level->grid[g_level->pacmanCol][g_level->pacmanRow] == PELLET) eat(pellet);
			} else if(g_level->grid[g_level->pacmanCol - 1][g_level->pacmanRow] == WALL) changeDirection = true;
			break;
		case RIGHT:
			if(movRight(g_level->pacmanRow, g_level->pacmanCol)) {
				//check if there is a pellet
				if(g_level->grid[g_level->pacmanCol][++g_level->pacmanRow] == MAGICPELLET) {
					g_level->magicEffect = true;
					eat(pellet);
				} else if(g_level->grid[g_level->pacmanCol][g_level->pacmanRow] == PELLET) eat(pellet);
			} else if(g_level->grid[g_level->pacmanCol][g_level->pacmanRow + 1] == WALL) changeDirection = true;
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
		counter = 0;
		changeDirection = true;
		translateTex(0.f, yTex);
	}
}

void Pacman::eat(Pellet &pellet) {
	//replace pellet in array
	g_level->grid[g_level->pacmanCol][g_level->pacmanRow] = EMPTY;
	//increment score
	g_level->score++;
	g_level->scoreChanged = true;
	//hide pellet
	pellet.hidePellet(g_level->pacmanCol, g_level->pacmanRow);
	if(g_level->score == g_level->pelletSize) {
		g_level->gameover = true;
		std::cout << "Congratulations, you won...\n";
	}
}

void Pacman::inputDirection(GLFWwindow *window) {
	//change direction on key press if pacman has completed a translation and it wont hit a wall
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && changeDirection && g_level->pacmanCol + 1 < g_level->gridHeight && g_level->grid[g_level->pacmanCol + 1][g_level->pacmanRow] != WALL) {
		direction = UP;
		yTex = 0.5f;
		translateTex(0.f, yTex);
	} else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && changeDirection && g_level->pacmanRow - 1 >= 0 && g_level->grid[g_level->pacmanCol][g_level->pacmanRow - 1] != WALL) {
		direction = LEFT;
		yTex = 0.25f;
		translateTex(0.f, yTex);
	} else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && changeDirection && g_level->pacmanCol - 1 >= 0 && g_level->grid[g_level->pacmanCol - 1][g_level->pacmanRow] != WALL) {
		direction = DOWN;
		yTex = 0.75f;
		translateTex(0.f, yTex);
	} else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && changeDirection && g_level->pacmanRow + 1 < g_level->gridWidth && g_level->grid[g_level->pacmanCol][g_level->pacmanRow + 1] != WALL) {
		direction = RIGHT;
		yTex = 0.0f;
		translateTex(0.f, yTex);
	}
}
