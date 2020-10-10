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
        bool changeDirection;
        /* private functionality */
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