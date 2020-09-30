#ifndef __CHARACTER_H
#define __CHARACTER_H
/* library */
#include "header/framework.h"
/**
 * @brief Child class of 'Framework' with shared data and functionality
 * 
 */
class Character : public Framework {
    public:
        /* public functionality */
        ~Character();
    protected:
        /* protected functionality */
        std::vector<GLfloat> genCoordinates(const float xPos, const float yPos, const float xTex, const float yTex);
        void translatePos(const float x, const float y, const GLuint &shader);
        void translateTex(const float x, const float y, const GLuint &shader);
        GLuint loadTexture(const std::string& filepath, GLuint slot);
};
#endif
