/**
 * Assignment 1 - Pacman
 * Fully functional pacman game
 *
 * @author Sindre Eiklid (sindreik@stud.ntnu.no)
 * @author Casper Melhus
 * @author Brage Heimly N�ss
 */
/* libraries */
#include "header/wall.h"
#include "header/pellet.h"
#include "header/pacman.h"
#include "header/function.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
/* global objects */
int  g_levelRow, g_levelCol, g_wallSize, g_pelletSize, g_gameScore;
float g_rowInc, g_colInc;
std::vector<std::vector<int>> g_level;
bool g_atePellet = false;
/* global variables */

/**
 * Main program.
 */
int main() {
	//branch if GLFW is initialized
	if(!glfwInit()) {
		std::cerr << "GLFW initialization failed." << '\n';
		std::cin.get();
		return EXIT_FAILURE;
	}
	//set values from file
	readFile();
	std::cout << "wall: " << g_wallSize << " pellet: " << g_pelletSize << std::endl;
	//setting window hints
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//create window
	auto window = glfwCreateWindow(g_levelRow * 35, g_levelCol * 35, "Pac-Man", nullptr, nullptr);
	//setting the OpenGL context to the window
	glfwMakeContextCurrent(window);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//branch if window is created
	if (window == nullptr) {
		std::cerr << "GLFW failed on window creation." << '\n';
		std::cin.get();
		glfwTerminate();
		return EXIT_FAILURE;
	}
	//branch if GLEW is initialized
	if(glewInit() != GLEW_OK) {
	  std::cerr << "GLEW initialization failuare." << '\n';
	  std::cin.get();
	  return EXIT_FAILURE;
	}
	//configure global opengl state

	//eanable capture of debug output
	enableDebug();
	//construct wall
	Wall wall;
	//construct pellets
	Pellet pellet;
	//construct pacman
	Pacman pacman;
	//set background color black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//loop until user closes window
	while(!glfwWindowShouldClose(window)) {
		//processes all pending events - source: https://www.glfw.org/docs/3.3/group__window.html#ga37bd57223967b4211d60ca1a0bf3c832
		glfwPollEvents();
		//for every frame reset background color to the value in the buffer ???
		glClear(GL_COLOR_BUFFER_BIT);
		//draw wall
		wall.drawObject();
		//remove eaten pellets
		if(g_atePellet) {
			pellet.clearObject();
			pellet.setupObject();
			g_atePellet = false;
		}
		//draw pellets
		pellet.drawObject();
		//draw pacman
		pacman.drawObject(window);
		//go to next buffer
		glfwSwapBuffers(window);
		//break loop if 'ESC' key is pressed
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
	}
	std::cout << "\nFinal score was: " << g_gameScore << "\n";
	//clear memory
	glUseProgram(0);
	glfwTerminate();
	return EXIT_SUCCESS;
}
