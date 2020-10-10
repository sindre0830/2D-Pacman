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
        GLuint cornerVAO;
        GLuint wallShaderProgram;
        int wallSize = 0, cornerSize = 0;
        /* private functionality */
        GLuint genObject();
        std::vector<GLfloat> genWallCoordinates(const int target);
        GLuint genCornerVAO(const int target);
    public:
        /* public functionality */
        ~Wall();
        Wall();
        void drawObject();
};
#endif
