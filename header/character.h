#ifndef __CHARACTER_H
#define __CHARACTER_H
/* library */
#include "header/framework.h"
#include <map>
#include <string>
/**
 * @brief Child class of 'Framework' with shared data and functionality
 * 
 */
class Character : public Framework {
    public:
        /* public functionality */
        ~Character();
    protected:
        /* protected data */
        std::map<std::string, std::vector<float>> spriteGrid;
        /* protected functionality */
        std::vector<GLfloat> genCoordinates(const float xPos, const float yPos, const float xTex, const float yTex);
        void translatePos(const float x, const float y, const GLuint &shader);
        void translateTex(const float x, const float y, const GLuint &shader);
        GLuint loadTexture(const std::string& filepath, GLuint slot);
        bool movUp(const int row, const int col, float &x, float &y, const int speed, const GLuint &shader);
        bool movLeft(const int row, const int col, float &x, float &y, const int speed, const GLuint &shader);
        bool movDown(const int row, const int col, float &x, float &y, const int speed, const GLuint &shader);
        bool movRight(const int row, const int col, float &x, float &y, const int speed, const GLuint &shader);
};
#endif
