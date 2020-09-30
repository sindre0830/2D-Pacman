#ifndef __WALL_H
#define __WALL_H
/* library */
#include "header/scenario.h"
/**
 * @brief Child class of 'Framework' with shared data and functionality
 * 
 */
class Wall : public Scenario {
    private:
        /* private data */
        GLuint wallVAO;
        GLuint wallShaderProgram;
        /* private functionality */
        GLuint genObject();
    public:
        /* public functionality */
        ~Wall();
        Wall();
        void drawObject();
};
#endif
