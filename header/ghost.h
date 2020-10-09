#ifndef __GHOST_H
#define __GHOST_H
/* libraries */
#include "header/character.h"
/**
 * 'Pacman' class.
 */
class Ghost : public Character {
    private:
        /* private data */
        GLuint ghostVAO;
        GLuint ghostShaderProgram;
        GLuint texture;
        int direction, rowPos, colPos, n, speed;
        float xPos, yPos, yTex;
        bool changeDirection;
        /* private functionality */
        GLuint genObject();
        void draw(GLuint &shader, GLuint &vao, GLFWwindow *window);
    public:
        /* public functionality */
        ~Ghost();
        Ghost();
        void drawObject(GLFWwindow *window);
        void movObject();
        void getPosition();
};
#endif