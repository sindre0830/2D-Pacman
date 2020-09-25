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
#include "headers/functions.h"
/* global objects */
Scenario gScenario;
/* global variables */
int gCol, gRow, gWallSize, gPelletSize;
std::vector<std::vector<int>> gLevel;
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
	enableDebug();
	//generate map
	auto mapVAO = gScenario.genMap();
	auto squareShaderProgram = CompileShader(squareVertexShaderSrc, squareFragmentShaderSrc);
	//generate pellets
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
