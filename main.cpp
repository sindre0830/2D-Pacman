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
#include "header/ghost.h"
#include "header/function.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
/* global variables */
int  g_levelRow, g_levelCol, g_wallSize, g_pelletSize, g_gameScore;
double g_rowInc, g_colInc;
std::vector<std::vector<int>> g_level;
std::vector<std::vector<bool>> g_ghostPos;
bool g_gameover = false;
/* global objects */
Pellet pellet;
/**
 * Main program.
 */
int main() {
	//branch if file isn't found
	if (!readFile()) {
		std::cerr << "File initialization failed.\n";
		std::cin.get();
		return EXIT_FAILURE;
	}
	std::cout << "wall: " << g_wallSize << " pellet: " << g_pelletSize << std::endl;
	//branch if GLFW isn't initialized
	if(!glfwInit()) {
		std::cerr << "GLFW initialization failed.\n";
		std::cin.get();
		return EXIT_FAILURE;
	}
	//set window hints
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
	//branch if window isn't created
	if (window == nullptr) {
		std::cerr << "GLFW failed on window creation.\n";
		std::cin.get();
		glfwTerminate();
		return EXIT_FAILURE;
	}
	//branch if GLEW isn't initialized
	if(glewInit() != GLEW_OK) {
		std::cerr << "GLEW initialization failuare.\n";
		std::cin.get();
		return EXIT_FAILURE;
	}
	//eanable capture of debug output
	enableDebug();
	//construct wall
	Wall wall;
	//construct pacman
	Pacman pacman;
	//construct ghost
	Ghost ghost;
	//construct pellets
	pellet.setupObject();
	//set background color black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//setup timer
	static double limitFPS = 1.0 / 60.0;
    double lastTime = glfwGetTime(), nowTime = 0, timer = lastTime;
    double deltaTime = 0;
	//loop until user closes window
	while(!glfwWindowShouldClose(window)) {
		//processes all pending events - source: https://www.glfw.org/docs/3.3/group__window.html#ga37bd57223967b4211d60ca1a0bf3c832
		glfwPollEvents();
		//time managment
		nowTime = glfwGetTime();
        deltaTime += (nowTime - lastTime) / limitFPS;
        lastTime = nowTime;
		//for every frame reset background color to the value in the buffer ???
		glClear(GL_COLOR_BUFFER_BIT);
		if(!g_gameover) {
			//draw wall
			wall.drawObject();
			//draw pellets
			pellet.drawObject();
			//draw pacman
			pacman.drawObject(window);
			if (deltaTime >= 1.0){
				pacman.movObject();
			}
			//draw ghost
			ghost.drawObject(window);
			if (deltaTime >= 1.0){
				ghost.movObject();
				deltaTime -= 1.0;
			}
		}
		//go to next buffer
		glfwSwapBuffers(window);
		//break loop if 'ESC' key is pressed
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
	}
	std::cout << "\nFinal score was: " << g_gameScore << '\n';
	//clear memory
	glUseProgram(0);
	glfwTerminate();
	return EXIT_SUCCESS;
}
