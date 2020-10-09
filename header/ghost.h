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
        /* private functionality */
        GLuint genObject();
        void draw(GLuint &shader, GLuint &vao);
    public:
        /* public functionality */
        ~Ghost();
        Ghost(int row, int col);
        void drawObject();
        void movObject();
        void getPosition();
};
#endif