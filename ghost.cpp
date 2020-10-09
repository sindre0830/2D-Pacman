/* libraries */
#include "header/ghost.h"
#include "shader/ghost.h"
#include "header/pellet.h"
#include <iostream>
/* global variables */
extern int  g_levelRow, g_levelCol;
extern double g_rowInc, g_colInc;
extern std::vector<std::vector<int>> g_level;
extern std::vector<std::vector<bool>> g_ghostPos;
/**
 * @brief Destroy the Pacman object
 */
Ghost::~Ghost() {
    glDeleteProgram(ghostShaderProgram);
    glDeleteTextures(1, &texture);
    cleanVAO(ghostVAO);
}
/**
 * @brief Declare variables on construction of Pacman object.
 */
Ghost::Ghost(int row, int col) {
	//set starting postions
	xPos = -1.0f + (g_rowInc * row);
	yPos = -1.0f + (g_colInc * col);
	rowPos = row;
	colPos = col;
	//setting direction compared to position
	if(g_levelRow / 2 <= row) {
		direction = 3;
	} else direction = 1;
	//generate VAO and shader program
    ghostVAO = genObject();
    ghostShaderProgram = compileShader(ghostVertexShaderSrc, ghostFragmentShaderSrc);
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
GLuint Ghost::genObject() {
    std::vector<GLfloat> arr = genCoordinates(xPos, yPos, 0.0f, 0.0f);
    std::vector<GLuint> arrIndices = genIndices(1);
	//reset values to be used in Pacman::draw()
	xPos = 0.0f;
	yPos = 0.0f;
    return createVAO(arr, arrIndices);
}

void Ghost::drawObject() {
    draw(ghostShaderProgram, ghostVAO);
}
/**
 * @brief Draw asset according to the direction it is facing.
 * 
 * @param shader
 * @param vao
 * @param window
 */
void Ghost::draw(GLuint &shader, GLuint &vao) {
    auto samplerSlotLocation = glGetUniformLocation(shader, "uTexture");
	glUseProgram(shader);
	glBindVertexArray(vao);
	glUniform1i(samplerSlotLocation, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
}
/**
 * @brief Move the asset to a direction until collision.
 * 
 * @param shader
 */
void Ghost::movObject() {
	//move up (W)
	if(direction == 0) {
		yTex = 0.5f;
		if(movUp(rowPos, colPos, xPos, yPos, speed, ghostShaderProgram)) counter++;
		//update grid if it has completed one square
		if(counter == speed) {
			if(colPos + 1 <= g_levelCol) {
				g_ghostPos[colPos][rowPos] = false;
				g_ghostPos[++colPos][rowPos] = true;

				std::vector<int> possiblePaths;
				if(g_level[colPos + 1][rowPos] != 1) possiblePaths.push_back(0);
				if(g_level[colPos][rowPos - 1] != 1) possiblePaths.push_back(1);
				if(g_level[colPos][rowPos + 1] != 1) possiblePaths.push_back(3);

				direction = possiblePaths[rand() % possiblePaths.size()];
			}
		}
	//move left (A)
	} else if (direction == 1) {
		yTex = 0.25f;
		if(movLeft(rowPos, colPos, xPos, yPos, speed, ghostShaderProgram)) counter++;
		//update grid if it has completed one square
		if(counter == speed) {
			if(rowPos - 1 >= 0) {
				g_ghostPos[colPos][rowPos] = false;
				g_ghostPos[colPos][--rowPos] = true;

				std::vector<int> possiblePaths;
				if(g_level[colPos + 1][rowPos] != 1) possiblePaths.push_back(0);
				if(g_level[colPos][rowPos - 1] != 1) possiblePaths.push_back(1);
				if(g_level[colPos - 1][rowPos] != 1) possiblePaths.push_back(2);

				direction = possiblePaths[rand() % possiblePaths.size()];
			}
		}
	//move down (S)
	} else if (direction == 2) {
		yTex = 0.75f;
		if(movDown(rowPos, colPos, xPos, yPos, speed, ghostShaderProgram)) counter++;
		//update grid if it has completed one square
		if(counter == speed) {
			if(colPos - 1 >= 0) {
				g_ghostPos[colPos][rowPos] = false;
				g_ghostPos[--colPos][rowPos] = true;

				std::vector<int> possiblePaths;
				if(g_level[colPos][rowPos - 1] != 1) possiblePaths.push_back(1);
				if(g_level[colPos - 1][rowPos] != 1) possiblePaths.push_back(2);
				if(g_level[colPos][rowPos + 1] != 1) possiblePaths.push_back(3);

				direction = possiblePaths[rand() % possiblePaths.size()];
			}
		}
	//move right (D)
	} else if (direction == 3) {
		yTex = 0.0f;
		if(movRight(rowPos, colPos, xPos, yPos, speed, ghostShaderProgram)) counter++;
		//update grid if it has completed one square
		if(counter == speed) {
			if(rowPos + 1 <= g_levelRow) {
				g_ghostPos[colPos][rowPos] = false;
				g_ghostPos[colPos][++rowPos] = true;

				std::vector<int> possiblePaths;
				if(g_level[colPos + 1][rowPos] != 1) possiblePaths.push_back(0);
				if(g_level[colPos - 1][rowPos] != 1) possiblePaths.push_back(2);
				if(g_level[colPos][rowPos + 1] != 1) possiblePaths.push_back(3);

				direction = possiblePaths[rand() % possiblePaths.size()];
			}
		}
	}
	if (counter == speed * 0.25f) {
		translateTex(4.0f / 6.0f, yTex, ghostShaderProgram);
	} else if (counter == speed * 0.5f) {
		translateTex(5.0f / 6.0f, yTex, ghostShaderProgram);
	} else if (counter == speed * 0.75f) {
		translateTex(4.0f / 6.0f, yTex, ghostShaderProgram);
	} else if (counter == speed) {
		translateTex(5.0f / 6.0f, yTex, ghostShaderProgram);
		counter = 0;
	}
}
