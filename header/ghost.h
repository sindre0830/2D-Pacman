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
        GLuint texture0;
        int direction, rowPos, colPos, n, speed;
        float xPos, yPos, yTex;
        bool changeDirection;
        /* private functionality */
        GLuint genObject();
        void draw(GLuint &shader, GLuint &vao, GLFWwindow *window);
        void movUp();
        void movLeft();
        void movDown();
        void movRight();
    public:
        /* public functionality */
        ~Ghost();
        Ghost();
        void drawObject(GLFWwindow *window);
        void movObject();
        void getPosition();
};
#endif