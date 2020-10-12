/* library */
#include "header/scoreboard.h"
#include "header/levelData.h"
#include "shader/scoreboard.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <map>
/* dictionary */
extern enum Corner {TOP_LEFT, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_RIGHT};
extern enum Position {X, Y};
extern enum Target {PELLET, WALL, PACMAN, EMPTY};
/* global data */
extern LevelData g_level;

Scoreboard::~Scoreboard() {
    glDeleteTextures(1, &texture);
}

Scoreboard::Scoreboard(const int col, const int row) {
    lastScore = 0;
    entityShaderProgram = compileShader(scoreboardVertexShaderSrc, scoreboardFragmentShaderSrc);
    entityVAO = genObject(col, row);
    //specify the layout of the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    //load the texture image, create OpenGL texture, and bind it to the current context
    texture = loadTexture("sprite/number.png", 1);
}

void Scoreboard::draw() {
    auto samplerSlotLocation = glGetUniformLocation(entityShaderProgram, "uTexture");
    glUseProgram(entityShaderProgram);
    glBindVertexArray(entityVAO);
    glUniform1i(samplerSlotLocation, 1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
}

void Scoreboard::update(int num) {
    if(num != lastScore) translateTex(texturePos[num]);
    lastScore = num;
}

GLuint Scoreboard::genObject(const int col, const int row) {
    std::vector<GLfloat> arr = genCoordinates(col, row);
    std::vector<GLuint> arrIndices = genIndices(1);
    return createVAO(arr, arrIndices);
}

std::vector<GLfloat> Scoreboard::genCoordinates(const int col, const int row) {
    GLfloat texPos = 0.f;
    std::vector<GLfloat> arr = {
        //top left grid and texture coordinate
        g_level.gridElement[std::make_pair(col, row)][TOP_LEFT][X], g_level.gridElement[std::make_pair(col, row)][TOP_LEFT][Y],	
        texPos, texPos + 1.f,
        //bottom left grid and texture coordinate
        g_level.gridElement[std::make_pair(col, row)][BOTTOM_LEFT][X], g_level.gridElement[std::make_pair(col, row)][BOTTOM_LEFT][Y], 
        texPos, texPos,
        //bottom right rid and texture coordinate
        g_level.gridElement[std::make_pair(col, row)][BOTTOM_RIGHT][X], g_level.gridElement[std::make_pair(col, row)][BOTTOM_RIGHT][Y], 
        texPos + (1.f / 10.f), texPos,
        //top right grid and texture coordinate
        g_level.gridElement[std::make_pair(col, row)][TOP_RIGHT][X], g_level.gridElement[std::make_pair(col, row)][TOP_RIGHT][Y],	
        texPos + (1.f / 10.f), texPos + 1.f
    };
    return arr;
}

void Scoreboard::translateTex(const float xPos) {
    //Translation moves our object
	glm::mat3 translation = glm::translate(glm::mat3(1), glm::vec2(xPos, 0.f));
	GLuint transformationmat = glGetUniformLocation(entityShaderProgram, "u_TransformationTex");
	//Send data from matrices to uniform
	glUniformMatrix3fv(transformationmat, 1, false, glm::value_ptr(translation));
}
