#ifndef __GAMEOVER_H
#define __GAMEOVER_H
/* library */
#include "header/geometricShape.h"
/**
 * 'Pellet' class.
 */
class Gameover : public GeometricShape {
    private:
        /* private functionality */
        std::vector<GLfloat> genCoordinates();
    public:
        /* public functionality */
        ~Gameover();
        Gameover();
        void draw();
};
#endif
