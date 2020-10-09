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
        int direction, rowPos, colPos, counter = 0, speed = 20;
        float xPos, yPos, yTex = 0.0f;
        /* private functionality */
        GLuint genObject();
        void draw(GLuint &shader, GLuint &vao);
    public:
        /* public functionality */
        ~Ghost();
        Ghost(int row, int col);
        void drawObject();
        void movObject();
};
#endif