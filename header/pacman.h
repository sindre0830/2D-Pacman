#ifndef __PACMAN_H
#define __PACMAN_H
/* libraries */
#include "header/character.h"
/**
 * 'Pacman' class.
 */
class Pacman : public Character {
    private:
        /* private data */
        GLuint pacmanVAO;
        GLuint pacmanShaderProgram;
        GLuint texture0;
        int direction, clock, rowPos, colPos, n;
        float speed, xPos, yPos;
        bool changeDirection;
        /* private functionality */
        GLuint genObject();
        void draw(GLuint &shader, GLuint &vao, GLFWwindow *window);
        void movRight();
    public:
        /* public functionality */
        ~Pacman();
        Pacman();
        void drawObject(GLFWwindow *window);
        void movObject();
        void getPosition();
};
#endif