#ifndef __PELLET_H
#define __PELLET_H
/* libraries */
#include "header/framework.h"
#include <map>
/**
 * 'Pellet' class.
 */
class Pellet : public Framework {
    private:
        /* private data */
        GLuint pelletVAO;
        GLuint pelletShaderProgram;
        std::map<std::pair<int, int>, int> bufferPos;
        const int pelletByteSize = 3 * 4 * sizeof(GLfloat);
        /* private functionality */
        GLuint genObject();
        std::vector<GLfloat> genCoordinates(const int target);
    public:
        /* public functionality */
        ~Pellet();
        Pellet();
        void setupObject();
        void drawObject();
        void hidePellet(const int x, const int y);
};
#endif