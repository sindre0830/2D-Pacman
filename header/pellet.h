#ifndef __PELLET_H
#define __PELLET_H
/* libraries */
#include "header/scenario.h"
/**
 * 'Pellet' class.
 */
class Pellet : public Scenario {
    private:
        /* private data */
        GLuint pelletVAO;
        GLuint pelletShaderProgram;
        /* private functionality */
        GLuint genObject();
    public:
        /* public functionality */
        ~Pellet();
        Pellet();
        void setupObject();
        void drawObject();
        void clearObject();
};
#endif