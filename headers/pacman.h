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
        int xPos, yPos;
        //enum direction{right, left, up, down};
    public:
        ~Pacman();
        int collisonCheck();
        void movUp();
        void movDown();
        void movRight();
        void movLeft();
        void mov();
        void draw();
        GLuint genAsset();
};
#endif