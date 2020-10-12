#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H
/* library */
#include "header/entity.h"
#include <map>
/**
 * 'Pellet' class.
 */
class Scoreboard : public Entity {
    private:
        /* private data */
        int lastScore;
        std::vector<float> texturePos = {
            0.f,
            1.f / 10.f,
            2.f / 10.f,
            3.f / 10.f,
            4.f / 10.f,
            5.f / 10.f,
            6.f / 10.f,
            7.f / 10.f,
            8.f / 10.f,
            9.f / 10.f
        };
        std::vector<GLuint> numberVAO;
        std::vector<GLuint> numberShader;
        const int numberByteSize = 4 * 4 * sizeof(GLfloat);
        GLuint texture;
        std::map<std::pair<int, int>, float> numberPos;
        /* private functionality */
        GLuint genObject(const int col, const int row);
        std::vector<GLfloat> genCoordinates(const int col, const int row);
        void translateTex(const float xPos);
    public:
        /* public functionality */
        ~Scoreboard();
        Scoreboard(const int col, const int row);
        void draw();
        void update(int num);
};
#endif