#ifndef __SCENARIO_H
#define __SCENARIO_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
/**
 * 'Scenario' class.
 *  - Includes map and pebble generation
 */
class Scenario {
    public:
        ~Scenario();
        void readFile();
        GLuint genMap();
        GLuint genPellet();
};
#endif