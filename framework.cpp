
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "headers/framework.h"
#include <iostream>
#include <vector>
Framework::~Framework() {}
/**
 * @brief Compile the vertex and fragment shader.
 * 
 * @param vertexShaderSrc 
 * @param fragmentShaderSrc 
 * @return GLuint 
 */
GLuint Framework::compileShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc) {

	auto vertexSrc = vertexShaderSrc.c_str();
	auto fragmentSrc = fragmentShaderSrc.c_str();

	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
	glCompileShader(vertexShader);

	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
	glCompileShader(fragmentShader);

	auto shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}