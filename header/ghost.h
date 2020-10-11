#ifndef __GHOST_H
#define __GHOST_H
/* library */
#include "header/character.h"
/**
 * 'Pacman' class.
 */
class Ghost : public Character {
    private:
        /* private data */
        int rowPos, colPos;
        /* private functionality */
        void findPath();
        void pathfinding();
        void animate();
    public:
        /* public functionality */
        ~Ghost();
        Ghost(int row, int col);
        void mov();
        void checkCoalition();
};
#endif