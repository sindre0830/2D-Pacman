/* libraries */
#include "header/ghost.h"
#include "shader/character.h"
#include "header/levelData.h"
#include <iostream>
/* global variables */
extern LevelData g_level;
extern bool g_gameover;
/**
 * @brief Destroy the Ghost object
 */
Ghost::~Ghost() {}
/**
 * @brief Set data on construction of Ghost object.
 */
Ghost::Ghost(int row, int col) {
	//set starting postions
	rowPos = row;
	colPos = col;
	//set starting direction compared to row position
	if(g_level.arrWidth / 2 <= row) {
		if(g_level.arr[col][row + 1] != 1) {
			direction = 3;
		} else direction = 1;
	} else {
		if(g_level.arr[col][row - 1] != 1) {
			direction = 1;
		} else direction = 3;
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
	checkCoalition();
	animate();
	switch (direction) {
		case 0:
			//face up
			yTex = 0.5f;
			//branch if charcter was able to move and increase counter
			if(movUp(rowPos, colPos)) counter++;
			//update grid if it has completed one square
			if(counter == speed) {
				//update the character position in array
				colPos++;
				//branch if character isn't going to teleport
				if(colPos + 1 < g_level.arrHeight) findPath();
			}
			break;
		case 1:
			//face left
			yTex = 0.25f;
			//branch if charcter was able to move and increase counter
			if(movLeft(rowPos, colPos)) counter++;
			//update grid if it has completed one square
			if(counter == speed) {
				//update the character position in array
				rowPos--;
				//branch if character isn't going to teleport
				if(rowPos - 1 >= 0) findPath();
			}
			break;
		case 2:
			//face down
			yTex = 0.75f;
			//branch if charcter was able to move and increase counter
			if(movDown(rowPos, colPos)) counter++;
			//update grid if it has completed one square
			if(counter == speed) {
				//update the character position in array
				colPos--;
				//branch if character isn't going to teleport
				if(colPos - 1 >= 0) findPath();
			}
			break;
		case 3:
			//face right
			yTex = 0.0f;
			//branch if charcter was able to move and increase counter
			if(movRight(rowPos, colPos)) counter++;
			//update grid if it has completed one square
			if(counter == speed) {
				//update the character position in array
				rowPos++;
				//branch if character isn't going to teleport and find a path
				if(rowPos + 1 < g_level.arrWidth) findPath();
			}
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

void Ghost::findPath() {
	//store all possible directions in an array
	std::vector<int> possiblePaths;
	//branch if path isn't opposite of current direction and there isn't a wall
	if(direction != 2 && g_level.arr[colPos + 1][rowPos] != 1) possiblePaths.push_back(0);
	if(direction != 3 && g_level.arr[colPos][rowPos - 1] != 1) possiblePaths.push_back(1);
	if(direction != 0 && g_level.arr[colPos - 1][rowPos] != 1) possiblePaths.push_back(2);
	if(direction != 1 && g_level.arr[colPos][rowPos + 1] != 1) possiblePaths.push_back(3);
	//pick direction randomly
	direction = possiblePaths[rand() % possiblePaths.size()];
}

void Ghost::pathfinding() {
	
}

void Ghost::checkCoalition() {
	if(colPos == g_level.pacmanCol && rowPos == g_level.pacmanRow) {
		g_gameover = true;
		std::cout << "Better luck next time...\n";
	}
}
