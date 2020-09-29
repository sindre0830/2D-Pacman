#ifndef __PELLET_H
#define __PELLET_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "headers/scenario.h"
#include "headers/functions.h"
/**
 * 'Pellet' class.
 */
class Pellet : public Scenario {
    public:
        ~Pellet();
        GLuint genObject();
};
#endif