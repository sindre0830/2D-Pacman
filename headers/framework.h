#ifndef __FRAMEWORK_H
#define __FRAMEWORK_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "headers/functions.h"
#include <iostream>
#include <vector>
/**
 * 'Framework' class.
 */
class Framework {
    public:
        ~Framework();
        GLuint compileShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
};
#endif