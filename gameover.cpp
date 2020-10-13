/* library */
#include "header/gameover.h"
#include "shader/gameover.h"
#include "header/levelData.h"
/* dictionary */
extern enum Corner {TOP_LEFT, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_RIGHT};
extern enum Position {X, Y};
extern enum Target {PELLET, WALL, PACMAN, EMPTY, MAGICPELLET};
/* global data */
extern LevelData *g_level;

Gameover::~Gameover() {}

Gameover::Gameover() {
    shapeShaderProgram = compileShader(gameoverVertexShaderSrc, gameoverFragmentShaderSrc);
	std::vector<GLfloat> arr = genCoordinates();
    shapeVAO = genObject(arr, 1);
    //specify the layout of the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
}

std::vector<GLfloat> Gameover::genCoordinates() {
    std::vector<GLfloat> arr = {
        //top left grid and texture coordinate
        -0.5f, 0.5f,
        0.f, 1.f,
        //bottom left grid and texture coordinate
        -0.5f, -0.5f,
        0.f, 0.f,
        //bottom right rid and texture coordinate
        0.5f, -0.5f,
        1.f, 0.f,
        //top right grid and texture coordinate
        0.5f, 0.5f,
        1.f, 1.f
    };
    return arr;
}

void Gameover::draw() {
    auto samplerSlotLocation = glGetUniformLocation(shapeShaderProgram, "uTexture");
    glUseProgram(shapeShaderProgram);
    glBindVertexArray(shapeVAO);
    glUniform1i(samplerSlotLocation, 2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
}
