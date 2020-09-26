#ifndef __PACMAN_H
#define __PACMAN_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "headers/functions.h"
#include <vector>
/**
 * 'Pacman' class.
 */
class Pacman {
    private:
        int direction;
    public:
        ~Pacman();
        Pacman();
        GLuint genAsset();
        int collisonCheck();
        void draw(GLuint shader, GLuint vao, GLFWwindow *window);
        void mov(GLuint shader);
};
#endif