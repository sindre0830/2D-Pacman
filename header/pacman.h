#ifndef __PACMAN_H
#define __PACMAN_H
/* library */
#include "header/character.h"
#include "header/pellet.h"
/**
 * 'Pacman' class.
 */
class Pacman : public Character {
    private:
        /* private data */
        bool changeDirection;
        /* private functionality */
        void animate();
        void eatPellet(Pellet &pellet);
    public:
        /* public functionality */
        ~Pacman();
        Pacman();
        void mov(Pellet &pellet);
        void getPosition();
        void inputDirection(GLFWwindow *window);
};
#endif