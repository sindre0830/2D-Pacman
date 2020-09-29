#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <set>
#include <string>
#include <vector>
/* defining functions */
GLuint createVAO(std::vector<GLfloat> arr, std::vector<GLuint> arr_indices); 
GLuint loadTexture(const std::string& filepath, GLuint slot);
void transform(const float x, const float y, const GLuint shader);
void texFocus(const float x, const float y, const GLuint shader);
void enableDebug();
GLuint compileShader(const std::string& vertexShader, const std::string& fragmentShader);
void cleanVAO(GLuint &vao);
void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
void readFile();
#endif