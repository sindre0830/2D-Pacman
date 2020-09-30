#ifndef __SCENARIO_H
#define __SCENARIO_H
/* library */
#include "header/framework.h"
/**
 * @brief Child class of 'Framework' with shared data and functionality
 * 
 */
class Scenario : public Framework {
    public:
        /* public functionality */
        ~Scenario();
    protected:
        /* protected functionality */
        void draw(const GLuint &shader, const GLuint &vao, const int n);
        std::vector<GLfloat> genCoordinates(const int target, const float xSize, const float ySize);
};
#endif
