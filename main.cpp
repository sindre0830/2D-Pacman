/**
 * Assignment 1 - Pacman
 * Fully functional pacman game
 *
 * @author Sindre Eiklid (sindreik@stud.ntnu.no)
 * @author Casper Melhus
 * @author Brage Heimly N�ss
 */
/* libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaders/square.h"
#include <iostream>
#include <set>
#include <vector>
#include "headers/scenario.h"
/* global objects */
Scenario gScenario;
/* global variables */
int gCol, gRow, gWallSize, gPelletSize;
std::vector<std::vector<int>> gLevel;
/* defining functions */
GLuint CompileShader(const std::string& vertexShader, const std::string& fragmentShader);
void CleanVAO(GLuint &vao);
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
/**
 * Main program.
 */
int main() {
	//reads data from file
	gScenario.readFile();
	//initialization of GLFW
	if(!glfwInit()) {
		std::cerr << "GLFW initialization failed." << '\n';
		std::cin.get();
		return EXIT_FAILURE;
	}
	//setting window hints
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//create window
	auto window = glfwCreateWindow(840, 1080, "Pac-Man", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "GLFW failed on window creation." << '\n';
		std::cin.get();
		glfwTerminate();
		return EXIT_FAILURE;
	}
	//setting the OpenGL context to the window
	glfwMakeContextCurrent(window);
	//initialization of GLEW
	if(glewInit() != GLEW_OK) {
	  std::cerr << "GLEW initialization failuare." << '\n';
	  std::cin.get();
	  return EXIT_FAILURE;
	}
	//eanable capture of debug output
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(MessageCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	//create map
	auto mapVAO = gScenario.genMap();
	auto squareShaderProgram = CompileShader(squareVertexShaderSrc, squareFragmentShaderSrc);
	//create pellets
	auto pelletVAO = gScenario.genPellet();
	auto pelletShaderProgram = CompileShader(squareVertexShaderSrc, squareFragmentShaderSrc);
	//set background color black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//loop until user closes window
	while(!glfwWindowShouldClose(window)) {
		//processes all pending events - source: https://www.glfw.org/docs/3.3/group__window.html#ga37bd57223967b4211d60ca1a0bf3c832
		glfwPollEvents();
		//for every frame reset background color to the value in the buffer ???
		glClear(GL_COLOR_BUFFER_BIT);
		//draw maze
		auto vertexColorLocation = glGetUniformLocation(squareShaderProgram, "u_Color");
		glUseProgram(squareShaderProgram);
		glBindVertexArray(mapVAO);
		glUniform4f(vertexColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, (6 * gWallSize), GL_UNSIGNED_INT, (const void*)0);
		//draw pellets
		auto vertexColorLocation1 = glGetUniformLocation(pelletShaderProgram, "u_Color");
		glUseProgram(pelletShaderProgram);
		glBindVertexArray(pelletVAO);
		glUniform4f(vertexColorLocation1, 1.0f, 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, (6 * gPelletSize), GL_UNSIGNED_INT, (const void*)0);
		//swaps the front and back buffers of the specified window. - source: https://www.glfw.org/docs/3.3/group__window.html#ga15a5a1ee5b3c2ca6b15ca209a12efd14
		glfwSwapBuffers(window);
		//break loop if 'ESC' key is pressed
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
	}
	//clean memory
	glUseProgram(0);
	glDeleteProgram(squareShaderProgram);
	glDeleteProgram(pelletShaderProgram);
	CleanVAO(mapVAO);
	CleanVAO(pelletVAO);
	glfwTerminate();
	return EXIT_SUCCESS;
}
/**
 * Compile shader.
 */
GLuint CompileShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc) {

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

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
/**
 * Clear trash from memory.
 */
void CleanVAO(GLuint &vao) {
	GLint nAttr = 0;
	std::set<GLuint> vbos;

	GLint eboId;
	glGetVertexArrayiv(vao, GL_ELEMENT_ARRAY_BUFFER_BINDING, &eboId);
	glDeleteBuffers(1, (GLuint*)&eboId);

	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttr);
	glBindVertexArray(vao);

	for (int iAttr = 0; iAttr < nAttr; ++iAttr)
	{
		GLint vboId = 0;
		glGetVertexAttribiv(iAttr, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &vboId);
		if (vboId > 0)
		{
			vbos.insert(vboId);
		}

		glDisableVertexAttribArray(iAttr);
	}

	for(auto vbo : vbos)
	{
	  glDeleteBuffers(1, &vbo);
	}

	glDeleteVertexArrays(1, &vao);
}
/**
 * Generates error msg.
 */
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ) {
	std::cerr << "GL CALLBACK:" << ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ) <<
		"type = 0x" << type <<
		", severity = 0x" << severity <<
		", message =" << message << "\n";
}
