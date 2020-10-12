#ifndef __CHARACTER_H
#define __CHARACTER_H
/* library */
#include "header/Entity.h"
#include <map>
#include <string>
/**
 * @brief Child class of 'Entity' with shared data and functionality
 * 
 */
class Character : public Entity {
    public:
        /* public functionality */
        ~Character();
        void draw();
    protected:
        /* protected data */
        GLuint texture;
        int direction, counter = 0, speed = 20;
        float xPos = 0.f, yPos = 0.f, yTex = 0.f;
        /* protected functionality */
        GLuint genObject(const int row, const int col);
        std::vector<GLfloat> genCoordinates(const int row, const int col);
        void translatePos(const float xPos, const float yPos);
        void translateTex(const float xPos, const float yPos);
        bool movUp(int &row, int &col);
        bool movLeft(int &row, int &col);
        bool movDown(int &row, int &col);
        bool movRight(int &row, int &col);
};
#endif
