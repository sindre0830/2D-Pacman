/* library */
#include "header/ghost.h"
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
 * @brief Destroy the Ghost object
 */
Ghost::~Ghost() {}
/**
 * @brief Set data on construction of Ghost object.
 */
Ghost::Ghost(const int row, const int col) {
	//set starting postions
	rowPos = row;
	colPos = col;
	//set starting direction compared to row position
	if(g_level.arrWidth / 2 <= row) {
		if(g_level.arr[col][row + 1] != WALL) {
			direction = RIGHT;
		} else direction = LEFT;
	} else {
		if(g_level.arr[col][row - 1] != WALL) {
			direction = LEFT;
		} else direction = RIGHT;
	}
	//generate VAO and shader program
    entityVAO = genObject(rowPos, colPos);
    entityShaderProgram = compileShader(characterVertexShaderSrc, characterFragmentShaderSrc);
	//specify the layout of the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    //load the texture image, create OpenGL texture, and bind it to the current context
    texture = loadTexture("sprite/pacman.png", 0);
	//translate texture to show ghost
	translateTex(4.0f / 6.0f, yTex);
}

/**
 * @brief Move the asset to a direction until collision.
 * 
 * @param shader
 */
void Ghost::mov() {
	checkCoalition(rowPos, colPos);
	animate();
	switch (direction) {
		case UP:
			//face up
			yTex = 0.5f;
			//branch if charcter was able to move and increase counter
			if(movUp(rowPos, colPos)) {
				//update the character position in array
				colPos++;
				checkCoalition(rowPos, colPos);
				//branch if character isn't going to teleport
				if(colPos + 1 < g_level.arrHeight) pathfinding();
			} else if(counter >= speed / 4) checkCoalition(rowPos, colPos + 1);
			break;
		case LEFT:
			//face left
			yTex = 0.25f;
			//branch if charcter was able to move and increase counter
			if(movLeft(rowPos, colPos)) {
				//update the character position in array
				rowPos--;
				checkCoalition(rowPos, colPos);
				//branch if character isn't going to teleport
				if(rowPos - 1 >= 0) pathfinding();
			} else if(counter >= speed / 4) checkCoalition(rowPos - 1, colPos);
			break;
		case DOWN:
			//face down
			yTex = 0.75f;
			//branch if charcter was able to move and increase counter
			if(movDown(rowPos, colPos)) {
				//update the character position in array
				colPos--;
				checkCoalition(rowPos, colPos);
				//branch if character isn't going to teleport
				if(colPos - 1 >= 0) pathfinding();
			} else if(counter >= speed / 4) checkCoalition(rowPos, colPos - 1);
			break;
		case RIGHT:
			//face right
			yTex = 0.0f;
			//branch if charcter was able to move and increase counter
			if(movRight(rowPos, colPos)) {
				//update the character position in array
				rowPos++;
				checkCoalition(rowPos, colPos);
				//branch if character isn't going to teleport and find a path
				if(rowPos + 1 < g_level.arrWidth) pathfinding();
			} else if(counter >= speed / 4) checkCoalition(rowPos + 1, colPos);
			break;
	}
}

void Ghost::animate() {
	if (counter == speed * 0.25f) {
		translateTex(4.0f / 6.0f, yTex);
	} else if (counter == speed * 0.5f) {
		translateTex(5.0f / 6.0f, yTex);
	} else if (counter == speed * 0.75f) {
		translateTex(4.0f / 6.0f, yTex);
	} else if (counter >= speed) {
		translateTex(5.0f / 6.0f, yTex);
		counter = 0;
	}
}

void Ghost::findRandomPath() {
	//store all possible directions in an array
	std::vector<int> possiblePaths;
	//branch if path isn't opposite of current direction and there isn't a wall
	if(direction != DOWN && g_level.arr[colPos + 1][rowPos] != WALL) possiblePaths.push_back(UP);
	if(direction != RIGHT && g_level.arr[colPos][rowPos - 1] != WALL) possiblePaths.push_back(LEFT);
	if(direction != UP && g_level.arr[colPos - 1][rowPos] != WALL) possiblePaths.push_back(DOWN);
	if(direction != LEFT && g_level.arr[colPos][rowPos + 1] != WALL) possiblePaths.push_back(RIGHT);
	//pick direction randomly
	direction = possiblePaths[rand() % possiblePaths.size()];
}

void Ghost::pathfinding() {
	if(!g_level.magicPellet) {
		//branch if path isn't opposite of current direction and there isn't a wall
		if(direction != DOWN && g_level.arr[colPos + 1][rowPos] != WALL && colPos < g_level.pacmanCol) {
			direction = UP;
		} else if(direction != UP && g_level.arr[colPos - 1][rowPos] != WALL && colPos > g_level.pacmanCol) {
			direction = DOWN;
		} else if(direction != RIGHT && g_level.arr[colPos][rowPos - 1] != WALL && rowPos > g_level.pacmanRow) {
			direction = LEFT;
		} else if(direction != LEFT && g_level.arr[colPos][rowPos + 1] != WALL && rowPos < g_level.pacmanRow) {
			direction = RIGHT;
		} else findRandomPath();
	} else findRandomPath();
}

void Ghost::checkCoalition(const int row, const int col) {
	if(row == g_level.pacmanRow && col == g_level.pacmanCol) {
		if(g_level.magicPellet) {
			dead = true;
		} else {
			g_gameover = true;
			std::cout << "Better luck next time...\n";
		}
	}
}

void Ghost::changeColor(const int flag) {
	//Translation moves our object
	GLuint color = glGetUniformLocation(entityShaderProgram, "u_ChangeColor");
	//Send data from matrices to uniform
	glUniform1i(color, flag);
	draw();
}
