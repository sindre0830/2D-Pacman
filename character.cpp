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

Character::~Character() {}

std::vector<GLfloat> Character::genCoordinates(const int row, const int col) {
    std::vector<GLfloat> arr = {
        //top left coordinate
        g_level.elementPos[std::make_pair(col, row)][0][0], g_level.elementPos[std::make_pair(col, row)][0][1],	
        0.f,                                                0.25f,
        //bottom left coordinate
        g_level.elementPos[std::make_pair(col, row)][1][0], g_level.elementPos[std::make_pair(col, row)][1][1], 
        0.f,                                                0.f,
        //bottom right coordinate
        g_level.elementPos[std::make_pair(col, row)][2][0], g_level.elementPos[std::make_pair(col, row)][2][1], 
        0.16f,                                              0.f,
        //top right coordinate
        g_level.elementPos[std::make_pair(col, row)][3][0], g_level.elementPos[std::make_pair(col, row)][3][1],	
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
void Character::translatePos(const float x, const float y, const GLuint &shader) {
    //Translation moves our object
    glm::mat4 translation = glm::translate(glm::mat4(1), glm::vec3(x, y, 0.f));
    //Create transformation matrix
    glm::mat4 transformation = translation;
    GLuint transformationmat = glGetUniformLocation(shader, "u_TransformationMat");
    //Send data from matrices to uniform
    glUniformMatrix4fv(transformationmat, 1, false, glm::value_ptr(transformation));
}

void Character::translateTex(const float x, const float y, const GLuint &shader) {
	//Translation moves our object
	glm::mat3 translation = glm::translate(glm::mat3(1), glm::vec2(x, y));
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

bool Character::movUp(int &row, int &col, float &x, float &y, const int speed, const GLuint &shader) {
	//check if next location will be a wall or out of bound
	if(col + 1 < g_level.arrHeight) {
        if(g_level.arr[col + 1][row] != 1) {
            //translate up on the x-axis
            translatePos(x, (y += g_level.elementHeight / (double)(speed)), shader);
            return true;
        } else return false;
    } else {
        translatePos(x, y -= (double)(g_level.arrHeight - 1) * g_level.elementHeight, shader);
        col = 0;
        g_level.ghostPos[g_level.arrHeight - 1][row] = false;
        return false;
    }
}

bool Character::movLeft(int &row, int &col, float &x, float &y, const int speed, const GLuint &shader) {
	//check if next location will be a wall or out of bound
	if(row - 1 >= 0) {
        if(g_level.arr[col][row - 1] != 1) {
            //translate up on the x-axis
            translatePos((x -= g_level.elementWidth / (double)(speed)), y, shader);
            return true;
        } else return false;
    } else {
        translatePos(x += (double)(g_level.arrWidth - 1) * g_level.elementWidth, y, shader);
        row = g_level.arrWidth - 1;
        g_level.ghostPos[col][0] = false;
        return false;
    }
}

bool Character::movDown(int &row, int &col, float &x, float &y, const int speed, const GLuint &shader) {
	//check if next location will be a wall or out of bound
	if(col - 1 > 0) {
        if(g_level.arr[col - 1][row] != 1) {
            //translate up on the x-axis
            translatePos(x, (y -= g_level.elementHeight / (double)(speed)), shader);
            return true;
        } else return false;
    } else {
        translatePos(x, y += (double)(g_level.arrHeight - 1) * g_level.elementHeight, shader);
        col = g_level.arrHeight - 1;
        g_level.ghostPos[0][row] = false;
        return false;
    }
}

bool Character::movRight(int &row, int &col, float &x, float &y, const int speed, const GLuint &shader) {
	//check if next location will be a wall or out of bound
	if(row + 1 < g_level.arrWidth) {
        if(g_level.arr[col][row + 1] != 1) {
            //translate up on the x-axis
            translatePos((x += g_level.elementWidth / (double)(speed)), y, shader);
            return true;
        } else return false;
	} else {
        translatePos(x -= (double)(g_level.arrWidth - 1) * g_level.elementWidth, y, shader);
        row = 0;
        g_level.ghostPos[col][g_level.arrWidth - 1] = false;
        return false;
    }
}
