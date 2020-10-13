#ifndef __WALL_H
#define __WALL_H
/* library */
#include "header/entity.h"
/**
 * @brief Child class of 'Entity' with shared data and functionality
 * 
 */
class Wall : public Entity {
    private:
        /* private data */
        GLuint cornerVAO;
        int wallSize = 0, cornerSize = 0;
        /* private functionality */
        std::vector<GLfloat> genWallCoordinates();
        GLuint genCornerVAO();
    public:
        /* public functionality */
        ~Wall();
        Wall();
        void draw();
};
#endif
