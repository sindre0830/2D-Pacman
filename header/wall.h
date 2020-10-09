#ifndef __WALL_H
#define __WALL_H
/* library */
#include "header/framework.h"
/**
 * @brief Child class of 'Framework' with shared data and functionality
 * 
 */
class Wall : public Framework {
    private:
        /* private data */
        GLuint wallVAO;
        GLuint wallShaderProgram;
        /* private functionality */
        GLuint genObject();
        std::vector<GLfloat> genCoordinates(const int target);
    public:
        /* public functionality */
        ~Wall();
        Wall();
        void drawObject();
};
#endif
