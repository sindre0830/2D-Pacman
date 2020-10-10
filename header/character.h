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
        GLuint texture;
        int direction, rowPos, colPos, counter = 0, speed = 20;
        float xPos = 0.f, yPos = 0.f, yTex = 0.f;
        /* protected functionality */
        GLuint genObject(const int row, const int col);
        std::vector<GLfloat> genCoordinates(const int row, const int col);
        void translatePos(const float x, const float y, const GLuint &shader);
        void translateTex(const float x, const float y, const GLuint &shader);
        GLuint loadTexture(const std::string& filepath, GLuint slot);
        bool movUp(int &row, int &col, float &x, float &y, const int speed, const GLuint &shader);
        bool movLeft(int &row, int &col, float &x, float &y, const int speed, const GLuint &shader);
        bool movDown(int &row, int &col, float &x, float &y, const int speed, const GLuint &shader);
        bool movRight(int &row, int &col, float &x, float &y, const int speed, const GLuint &shader);
};
#endif
