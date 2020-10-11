#ifndef __ENTITY_H
#define __ENTITY_H
/* library */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <set>
/**
 * @brief Root class with shared data and functionality
 * 
 */
class Entity {
    public:
        /* public functionality */
        ~Entity();
    protected:
        /* protected data */
        GLuint entityVAO;
        GLuint entityShaderProgram;
        /* protected functionality */
        GLuint createVAO(const std::vector<GLfloat> &arr, const std::vector<GLuint> &arr_indices);
        GLuint compileShader(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc);
        void cleanVAO(GLuint &vao);
        std::vector<GLuint> genIndices(const int size);
};
#endif
