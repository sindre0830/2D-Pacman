/* library */
#include "header/character.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stb_image.h>

extern int  g_levelRow, g_levelCol;
extern float g_rowInc, g_colInc;
extern std::vector<std::vector<int>> g_level;

Character::~Character() {}

std::vector<GLfloat> Character::genCoordinates(const float xPos, const float yPos, const float xTex, const float yTex) {
    std::vector<GLfloat> arr = {
		//position								//texture coord
		xPos,			    yPos + g_colInc,	xTex,	        yTex + 0.25f,
		xPos,			    yPos,				xTex,	        yTex,
		xPos + g_rowInc,	yPos,				xTex + 0.16f,	yTex,
		xPos + g_rowInc,	yPos + g_colInc,	xTex + 0.16f,	yTex + 0.25f
    };
    std::cout << "pacman array: " << arr.size() * sizeof(GLfloat) << std::endl;
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
    auto pixels = stbi_load(filepath.c_str(), &w, &h,&bpp, STBI_rgb_alpha);
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
