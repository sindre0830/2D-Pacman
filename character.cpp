/* library */
#include "header/character.h"
#include "header/levelData.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stb_image.h>

extern LevelData g_level;
extern enum direction {topLeft, bottomLeft, bottomRight, topRight};
extern enum position {x, y};

Character::~Character() {
    glDeleteTextures(1, &texture);
}
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
        g_level.elementPos[std::make_pair(col, row)][topLeft][x], g_level.elementPos[std::make_pair(col, row)][topLeft][y],	
        texPos, texPos + 0.25f,
        //bottom left grid and texture coordinate
        g_level.elementPos[std::make_pair(col, row)][bottomLeft][x], g_level.elementPos[std::make_pair(col, row)][bottomLeft][y], 
        texPos, texPos,
        //bottom right rid and texture coordinate
        g_level.elementPos[std::make_pair(col, row)][bottomRight][x], g_level.elementPos[std::make_pair(col, row)][bottomRight][y], 
        texPos + 0.16f, texPos,
        //top right grid and texture coordinate
        g_level.elementPos[std::make_pair(col, row)][topRight][x], g_level.elementPos[std::make_pair(col, row)][topRight][y],	
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
        if(g_level.arr[col + 1][row] != 1) {
            //translate up on the x-axis
            translatePos(xPos, (yPos += g_level.elementHeight / (double)(speed)));
            return true;
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
        if(g_level.arr[col][row - 1] != 1) {
            //translate up on the x-axis
            translatePos((xPos -= g_level.elementWidth / (double)(speed)), yPos);
            return true;
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
        if(g_level.arr[col - 1][row] != 1) {
            //translate up on the x-axis
            translatePos(xPos, (yPos -= g_level.elementHeight / (double)(speed)));
            return true;
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
        if(g_level.arr[col][row + 1] != 1) {
            //translate up on the x-axis
            translatePos((xPos += g_level.elementWidth / (double)(speed)), yPos);
            return true;
        }
	} else {
        row = 0;
        translatePos(xPos -= (double)(g_level.arrWidth - 1) * g_level.elementWidth, yPos);
    }
    return false;
}
/**
 * @brief Loads texture from filepath through CMake.
 * 
 * @param filepath
 * @param slot
 * @return GLuint
 */
GLuint Character::loadTexture(const std::string& filepath, GLuint slot) {
	//flip image
	stbi_set_flip_vertically_on_load(true);
	//load pixel data from a stored image
    int w, h, bpp;
    auto pixels = stbi_load(filepath.c_str(), &w, &h, &bpp, STBI_rgb_alpha);
    //generate the texture
	GLuint tex{};
    glGenTextures(1, &tex);					//generate a texture object
    glActiveTexture(GL_TEXTURE0 + slot);	//set the active texture
    glBindTexture(GL_TEXTURE_2D, tex);		//bind texture
	//transfer the image data to the texture in GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    //set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //free the memory returned by STBI
    if(pixels) stbi_image_free(pixels);
    return tex;
}
