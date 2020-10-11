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
        int rowPos, colPos;
        /* private functionality */
        void draw(GLuint &shader, GLuint &vao);
        void findPath();
        void pathfinding();
        void animate();
    public:
        /* public functionality */
        ~Ghost();
        Ghost(int row, int col);
        void drawObject();
        void movObject();
        void checkCoalition();
};
#endif