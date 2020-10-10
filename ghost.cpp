/* libraries */
#include "header/ghost.h"
#include "shader/character.h"
#include "header/levelData.h"
/* global variables */
extern LevelData g_level;
/**
 * @brief Destroy the Ghost object
 */
Ghost::~Ghost() {
    glDeleteProgram(ghostShaderProgram);
    glDeleteTextures(1, &texture);
    cleanVAO(ghostVAO);
}
/**
 * @brief Set data on construction of Ghost object.
 */
Ghost::Ghost(int row, int col) {
	//set starting postions
	rowPos = row;
	colPos = col;
	//set starting direction compared to row position
	if(g_level.arrWidth / 2 <= row) {
		direction = 3;
	} else direction = 1;
	//generate VAO and shader program
    ghostVAO = genObject(rowPos, colPos);
    ghostShaderProgram = compileShader(characterVertexShaderSrc, characterFragmentShaderSrc);
	//specify the layout of the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    //load the texture image, create OpenGL texture, and bind it to the current context
    texture = loadTexture("sprite/pacman.png", 0);
	//translate texture to show ghost
	translateTex(4.0f / 6.0f, yTex, ghostShaderProgram);
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
			//update the character position in array
			g_level.ghostPos[colPos][rowPos] = false;
			g_level.ghostPos[++colPos][rowPos] = true;
			//branch if character isn't going to teleport
			if(colPos + 1 <= g_level.arrHeight) {
				//store all possible directions in an array
				std::vector<int> possiblePaths;
				if(g_level.arr[colPos + 1][rowPos] != 1) possiblePaths.push_back(0);
				if(g_level.arr[colPos][rowPos - 1] != 1) possiblePaths.push_back(1);
				if(g_level.arr[colPos][rowPos + 1] != 1) possiblePaths.push_back(3);
				//pick direction randomly
				direction = possiblePaths[rand() % possiblePaths.size()];
			}
		}
	//move left (A)
	} else if (direction == 1) {
		yTex = 0.25f;
		if(movLeft(rowPos, colPos, xPos, yPos, speed, ghostShaderProgram)) counter++;
		//update grid if it has completed one square
		if(counter == speed) {
			//update the character position in array
			g_level.ghostPos[colPos][rowPos] = false;
			g_level.ghostPos[colPos][--rowPos] = true;
			//branch if character isn't going to teleport
			if(rowPos - 1 >= 0) {
				//store all possible directions in an array
				std::vector<int> possiblePaths;
				if(g_level.arr[colPos + 1][rowPos] != 1) possiblePaths.push_back(0);
				if(g_level.arr[colPos][rowPos - 1] != 1) possiblePaths.push_back(1);
				if(g_level.arr[colPos - 1][rowPos] != 1) possiblePaths.push_back(2);
				//pick direction randomly
				direction = possiblePaths[rand() % possiblePaths.size()];
			}
		}
	//move down (S)
	} else if (direction == 2) {
		yTex = 0.75f;
		if(movDown(rowPos, colPos, xPos, yPos, speed, ghostShaderProgram)) counter++;
		//update grid if it has completed one square
		if(counter == speed) {
			//update the character position in array
			g_level.ghostPos[colPos][rowPos] = false;
			g_level.ghostPos[--colPos][rowPos] = true;
			//branch if character isn't going to teleport
			if(colPos - 1 >= 0) {
				//store all possible directions in an array
				std::vector<int> possiblePaths;
				if(g_level.arr[colPos][rowPos - 1] != 1) possiblePaths.push_back(1);
				if(g_level.arr[colPos - 1][rowPos] != 1) possiblePaths.push_back(2);
				if(g_level.arr[colPos][rowPos + 1] != 1) possiblePaths.push_back(3);
				//pick direction randomly
				direction = possiblePaths[rand() % possiblePaths.size()];
			}
		}
	//move right (D)
	} else if (direction == 3) {
		yTex = 0.0f;
		if(movRight(rowPos, colPos, xPos, yPos, speed, ghostShaderProgram)) counter++;
		//update grid if it has completed one square
		if(counter == speed) {
			//update the character position in array
			g_level.ghostPos[colPos][rowPos] = false;
			g_level.ghostPos[colPos][++rowPos] = true;
			//branch if character isn't going to teleport
			if(rowPos + 1 < g_level.arrWidth) {
				//store all possible directions in an array
				std::vector<int> possiblePaths;
				if(g_level.arr[colPos + 1][rowPos] != 1) possiblePaths.push_back(0);
				if(g_level.arr[colPos - 1][rowPos] != 1) possiblePaths.push_back(2);
				if(g_level.arr[colPos][rowPos + 1] != 1) possiblePaths.push_back(3);
				//pick direction randomly
				direction = possiblePaths[rand() % possiblePaths.size()];
			}
		}
	}
	//animate
	if (counter == speed * 0.25f) {
		translateTex(4.0f / 6.0f, yTex, ghostShaderProgram);
	} else if (counter == speed * 0.5f) {
		translateTex(5.0f / 6.0f, yTex, ghostShaderProgram);
	} else if (counter == speed * 0.75f) {
		translateTex(4.0f / 6.0f, yTex, ghostShaderProgram);
	} else if (counter >= speed) {
		translateTex(5.0f / 6.0f, yTex, ghostShaderProgram);
		counter = 0;
	}
}
