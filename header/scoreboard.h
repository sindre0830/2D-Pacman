#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H
/* library */
#include "header/geometricShape.h"
/**
 * @brief Leaf class
 * 
 */
class Scoreboard : public GeometricShape {
    private:
        /* private data */
        int lastNumber = 0;
        /* private functionality */
        std::vector<GLfloat> genCoordinates(const int col, const int row);
        void translateTex(const float xPos);
    public:
        /* public functionality */
        ~Scoreboard();
        Scoreboard(const int col, const int row);
        void draw();
        void update(const int num);
};
#endif