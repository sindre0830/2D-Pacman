#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H
/* library */
#include "header/entity.h"
/**
 * 'Pellet' class.
 */
class Scoreboard : public Entity {
    private:
        /* private data */
        const int numberByteSize = 4 * 4 * sizeof(GLfloat);
        int lastScore = 0;
        /* private functionality */
        GLuint genObject(const int col, const int row);
        std::vector<GLfloat> genCoordinates(const int col, const int row);
        void translateTex(const float xPos);
    public:
        /* public functionality */
        ~Scoreboard();
        Scoreboard(const int col, const int row);
        void draw();
        void update(int num);
};
#endif