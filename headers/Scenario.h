#ifndef __SCENARIO_H
#define __SCENARIO_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "headers/scenario.h"
#include "headers/functions.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
/**
 * 'Scenario' class.
 */
class Scenario {
    public:
        ~Scenario();
        void readFile();
        GLuint genMap();
        GLuint genPellet();
        void draw(GLuint shader, GLuint vao, int n, float r, float g, float b);
};
#endif