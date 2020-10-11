#ifndef __PELLET_H
#define __PELLET_H
/* library */
#include "header/entity.h"
#include <map>
/**
 * 'Pellet' class.
 */
class Pellet : public Entity {
    private:
        /* private data */
        std::map<std::pair<int, int>, int> bufferPos;
        const int pelletByteSize = 3 * 4 * sizeof(GLfloat);
        /* private functionality */
        GLuint genObject();
        std::vector<GLfloat> genCoordinates();
    public:
        /* public functionality */
        ~Pellet();
        Pellet();
        void draw();
        void hidePellet(const int xPos, const int yPos);
};
#endif