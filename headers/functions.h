#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
/* defining functions */
GLuint CompileShader(const std::string& vertexShader, const std::string& fragmentShader);
void CleanVAO(GLuint &vao);
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
#endif