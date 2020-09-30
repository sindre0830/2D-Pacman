#ifndef __FUNCTION_H
#define __FUNCTION_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>
/* defining functions */
bool readFile();
void enableDebug();
void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
//void readFile();
#endif
