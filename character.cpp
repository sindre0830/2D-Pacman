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
    std::vector<GLfloat> arr = {
        //top left coordinate
        g_level.elementPos[std::make_pair(col, row)][topLeft][x], g_level.elementPos[std::make_pair(col, row)][topLeft][y],	
        0.f,                                                0.25f,
        //bottom left coordinate
        g_level.elementPos[std::make_pair(col, row)][bottomLeft][x], g_level.elementPos[std::make_pair(col, row)][bottomLeft][y], 
        0.f,                                                0.f,
        //bottom right coordinate
        g_level.elementPos[std::make_pair(col, row)][bottomRight][x], g_level.elementPos[std::make_pair(col, row)][bottomRight][y], 
        0.16f,                                              0.f,
        //top right coordinate
        g_level.elementPos[std::make_pair(col, row)][topRight][x], g_level.elementPos[std::make_pair(col, row)][topRight][y],	
        0.16f,                                              0.25f
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
void Character::translatePos(const float xPos, const float yPos, const GLuint &shader) {
    //Translation moves our object
    glm::mat4 translation = glm::translate(glm::mat4(1), glm::vec3(xPos, yPos, 0.f));
    //Create transformation matrix
    GLuint transformationmat = glGetUniformLocation(shader, "u_TransformationMat");
    //Send data from matrices to uniform
    glUniformMatrix4fv(transformationmat, 1, false, glm::value_ptr(translation));
}

void Character::translateTex(const float xPos, const float yPos, const GLuint &shader) {
	//Translation moves our object
	glm::mat3 translation = glm::translate(glm::mat3(1), glm::vec2(xPos, yPos));
	GLuint transformationmat = glGetUniformLocation(shader, "u_TransformationTex");
	//Send data from matrices to uniform
	glUniformMatrix3fv(transformationmat, 1, false, glm::value_ptr(translation));
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

bool Character::movUp(int &row, int &col, float &xPos, float &yPos, const int speed, const GLuint &shader) {
	//check if next location will be a wall or out of bound
	if(col + 1 < g_level.arrHeight) {
        if(g_level.arr[col + 1][row] != 1) {
            //translate up on the x-axis
            translatePos(xPos, (yPos += g_level.elementHeight / (double)(speed)), shader);
            return true;
        } else return false;
    } else {
        col = 0;
        translatePos(xPos, yPos -= (double)(g_level.arrHeight - 1) * g_level.elementHeight, shader);
        return false;
    }
}

bool Character::movLeft(int &row, int &col, float &xPos, float &yPos, const int speed, const GLuint &shader) {
	//check if next location will be a wall or out of bound
	if(row - 1 >= 0) {
        if(g_level.arr[col][row - 1] != 1) {
            //translate up on the x-axis
            translatePos((xPos -= g_level.elementWidth / (double)(speed)), yPos, shader);
            return true;
        } else return false;
    } else {
        row = g_level.arrWidth - 1;
        translatePos(xPos += (double)(g_level.arrWidth - 1) * g_level.elementWidth, yPos, shader);
        return false;
    }
}

bool Character::movDown(int &row, int &col, float &xPos, float &yPos, const int speed, const GLuint &shader) {
	//check if next location will be a wall or out of bound
	if(col - 1 >= 0) {
        if(g_level.arr[col - 1][row] != 1) {
            //translate up on the x-axis
            translatePos(xPos, (yPos -= g_level.elementHeight / (double)(speed)), shader);
            return true;
        } else return false;
    } else {
        col = g_level.arrHeight - 1;
        translatePos(xPos, yPos += (double)(g_level.arrHeight - 1) * g_level.elementHeight, shader);
        return false;
    }
}

bool Character::movRight(int &row, int &col, float &xPos, float &yPos, const int speed, const GLuint &shader) {
	//check if next location will be a wall or out of bound
	if(row + 1 < g_level.arrWidth) {
        if(g_level.arr[col][row + 1] != 1) {
            //translate up on the x-axis
            translatePos((xPos += g_level.elementWidth / (double)(speed)), yPos, shader);
            return true;
        } else return false;
	} else {
        row = 0;
        translatePos(xPos -= (double)(g_level.arrWidth - 1) * g_level.elementWidth, yPos, shader);
        return false;
    }
}
