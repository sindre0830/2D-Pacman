/* library */
#include "header/character.h"
#include "header/levelData.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
/* dictionary */
extern enum Corner {TOP_LEFT, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_RIGHT};
extern enum Position {X, Y};
extern enum Target {PELLET, WALL, PACMAN, EMPTY, MAGICPELLET};
/* global data */
extern LevelData g_level;

Character::~Character() {}
/**
 * @brief Draw asset according to the direction it is facing.
 * 
 * @param shader
 * @param vao
 * @param window
 */
void Character::draw() {
    auto samplerSlotLocation = glGetUniformLocation(entityShaderProgram, "uTexture");
	glUseProgram(entityShaderProgram);
	glBindVertexArray(entityVAO);
	glUniform1i(samplerSlotLocation, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
}
/**
 * @brief Generate Pac-Man from the 2D array to the window.
 * 
 * @return GLuint 
 */
GLuint Character::genObject(const int row, const int col) {
    std::vector<GLfloat> arr = genCoordinates(row, col);
    std::vector<GLuint> arrIndices = genIndices(1);
    return createVAO(arr, arrIndices);
}

std::vector<GLfloat> Character::genCoordinates(const int row, const int col) {
    GLfloat texPos = 0.f;
    std::vector<GLfloat> arr = {
        //top left grid and texture coordinate
        g_level.gridElement[std::make_pair(col, row)][TOP_LEFT][X], g_level.gridElement[std::make_pair(col, row)][TOP_LEFT][Y],	
        texPos, texPos + 0.25f,
        //bottom left grid and texture coordinate
        g_level.gridElement[std::make_pair(col, row)][BOTTOM_LEFT][X], g_level.gridElement[std::make_pair(col, row)][BOTTOM_LEFT][Y], 
        texPos, texPos,
        //bottom right rid and texture coordinate
        g_level.gridElement[std::make_pair(col, row)][BOTTOM_RIGHT][X], g_level.gridElement[std::make_pair(col, row)][BOTTOM_RIGHT][Y], 
        texPos + 0.16f, texPos,
        //top right grid and texture coordinate
        g_level.gridElement[std::make_pair(col, row)][TOP_RIGHT][X], g_level.gridElement[std::make_pair(col, row)][TOP_RIGHT][Y],	
        texPos + 0.16f, texPos + 0.25f
    };
    return arr;
}
/**
 * @brief Translate the shader on the y- and x-axis.
 * 
 * @param x 
 * @param y 
 * @param shader 
 */
void Character::translatePos(const float xPos, const float yPos) {
    //Translation moves our object
    glm::mat4 translation = glm::translate(glm::mat4(1), glm::vec3(xPos, yPos, 0.f));
    //Create transformation matrix
    GLuint transformationmat = glGetUniformLocation(entityShaderProgram, "u_TransformationMat");
    //Send data from matrices to uniform
    glUniformMatrix4fv(transformationmat, 1, false, glm::value_ptr(translation));
}

void Character::translateTex(const float xPos, const float yPos) {
	//Translation moves our object
	glm::mat3 translation = glm::translate(glm::mat3(1), glm::vec2(xPos, yPos));
	GLuint transformationmat = glGetUniformLocation(entityShaderProgram, "u_TransformationTex");
	//Send data from matrices to uniform
	glUniformMatrix3fv(transformationmat, 1, false, glm::value_ptr(translation));
}

bool Character::movUp(int &row, int &col) {
	//check if next location will be a wall or out of bound
	if(col + 1 < g_level.arrHeight) {
        if(g_level.arr[col + 1][row] != WALL) {
            //translate up on the x-axis
            translatePos(xPos, (yPos += g_level.elementHeight / (double)(speed)));
            counter++;
            if(counter == speed) return true;
        }
    } else {
        col = 0;
        translatePos(xPos, yPos -= (double)(g_level.arrHeight - 1) * g_level.elementHeight);
    }
    return false;
}

bool Character::movLeft(int &row, int &col) {
	//check if next location will be a wall or out of bound
	if(row - 1 >= 0) {
        if(g_level.arr[col][row - 1] != WALL) {
            //translate up on the x-axis
            translatePos((xPos -= g_level.elementWidth / (double)(speed)), yPos);
            counter++;
            if(counter == speed) return true;
        }
    } else {
        row = g_level.arrWidth - 1;
        translatePos(xPos += (double)(g_level.arrWidth - 1) * g_level.elementWidth, yPos);
    }
    return false;
}

bool Character::movDown(int &row, int &col) {
	//check if next location will be a wall or out of bound
	if(col - 1 >= 0) {
        if(g_level.arr[col - 1][row] != WALL) {
            //translate up on the x-axis
            translatePos(xPos, (yPos -= g_level.elementHeight / (double)(speed)));
            counter++;
            if(counter == speed) return true;
        }
    } else {
        col = g_level.arrHeight - 1;
        translatePos(xPos, yPos += (double)(g_level.arrHeight - 1) * g_level.elementHeight);
    }
    return false;
}

bool Character::movRight(int &row, int &col) {
	//check if next location will be a wall or out of bound
	if(row + 1 < g_level.arrWidth) {
        if(g_level.arr[col][row + 1] != WALL) {
            //translate up on the x-axis
            translatePos((xPos += g_level.elementWidth / (double)(speed)), yPos);
            counter++;
            if(counter == speed) return true;
        }
	} else {
        row = 0;
        translatePos(xPos -= (double)(g_level.arrWidth - 1) * g_level.elementWidth, yPos);
    }
    return false;
}
