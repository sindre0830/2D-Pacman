#ifndef __ENTITY_H
#define __ENTITY_H
/* library */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
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
        GLuint entityShaderProgram;
        GLuint entityVAO;
        /* protected functionality */
        GLuint compileShader(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc);
        GLuint genObject(const std::vector<GLfloat> arr, const int size);
        GLuint createVAO(const std::vector<GLfloat> &arr, const std::vector<GLuint> &arr_indices);
        std::vector<GLuint> genIndices(const int size);
        void destroyVAO(GLuint &vao);
};
#endif
