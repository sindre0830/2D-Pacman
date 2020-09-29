#ifndef __WALL_H
#define __WALL_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "headers/scenario.h"
#include "headers/functions.h"
/**
 * 'Wall' class.
 */
class Wall : public Scenario {
    public:
        ~Wall();
        GLuint genObject();
};
#endif