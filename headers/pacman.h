#ifndef __PACMAN_H
#define __PACMAN_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "headers/functions.h"
#include <vector>
#include <cmath>
/**
 * 'Pacman' class.
 */
class Pacman {
    private:
        int direction, clock;
        float speed;
        bool changeDirection;
    public:
        ~Pacman();
        Pacman();
        GLuint genAsset();
        void draw(GLuint shader, GLuint vao, GLFWwindow *window);
        void mov(GLuint shader);
		void texFocus(const float x, const float y, const GLuint shader);
};
#endif