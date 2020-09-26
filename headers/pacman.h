#ifndef __PACMAN_H
#define __PACMAN_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
/**
 * 'Pacman' class.
 */
class Pacman {
    private:
        int xPos, yPos, dir;
        //enum direction{right, left, up, down};
    public:
        ~Pacman();
        Pacman();
        int collisonCheck();
        void movUp();
        void movDown();
        void movRight();
        void movLeft();
        void mov(GLuint pacmanShaderProgram);
        void draw(GLuint pacmanShaderProgram, GLuint pacmanVAO, GLFWwindow *window);
        GLuint genAsset();
};
#endif