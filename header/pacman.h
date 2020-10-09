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
        GLuint texture;
        int direction, rowPos, colPos, n, speed;
        float xPos, yPos, yTex;
        bool changeDirection;
        /* private functionality */
        GLuint genObject();
        void draw(GLuint &shader, GLuint &vao, GLFWwindow *window);
    public:
        /* public functionality */
        ~Pacman();
        Pacman();
        void drawObject(GLFWwindow *window);
        void movObject();
        void getPosition();
};
#endif