#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
/* defining functions */
GLuint createVAO(std::vector<GLfloat> arr, std::vector<GLuint> arr_indices); 
GLuint load_opengl_texture(const std::string& filepath, GLuint slot);
void Transform(const float x, const float y, const GLuint shaderprogram);
void enableDebug();
GLuint CompileShader(const std::string& vertexShader, const std::string& fragmentShader);
void CleanVAO(GLuint &vao);
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
#endif