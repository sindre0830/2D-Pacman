#ifndef __PELLET_H
#define __PELLET_H
/* libraries */
#include "header/scenario.h"
#include <map>
/**
 * 'Pellet' class.
 */
class Pellet : public Scenario {
    private:
        /* private data */
        GLuint pelletVAO;
        GLuint pelletShaderProgram;
        std::map<std::pair<int,int>, int> bufferPos;
        int pelletByteSize = 3 * 4 * sizeof(GLfloat);
        /* private functionality */
        GLuint genObject();
    public:
        /* public functionality */
        ~Pellet();
        Pellet();
        void setupObject();
        void drawObject();
        void hidePellet(const int x, const int y);
};
#endif