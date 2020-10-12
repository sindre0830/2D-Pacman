#ifndef __FUNCTION_H
#define __FUNCTION_H
/* library */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>
/* functionality */
bool readFile();
void enableDebug();
void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
void getGhostPos(std::vector<std::vector<int>> &arr, int &row, int &col);
void get_resolution(GLFWwindow* window, int &width, int &height);
GLuint loadTexture(const std::string &filepath, GLuint slot);
#endif
