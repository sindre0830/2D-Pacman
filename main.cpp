/**
 * Assignment 1 - Pacman
 * Fully functional pacman game
 *
 * @author Sindre Eiklid (sindreik@stud.ntnu.no)
 * @author Casper Melhus
 * @author Brage Heimly N�ss
 */
/* libraries */
#include "header/levelData.h"
#include "header/wall.h"
#include "header/pellet.h"
#include "header/pacman.h"
#include "header/ghost.h"
#include "header/function.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
/* global data */
bool g_gameover = false;
LevelData g_level;
enum direction {topLeft, bottomLeft, bottomRight, topRight};
enum position {x, y};
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
	/*int width, height;
	get_resolution(width, height);
	auto window = glfwCreateWindow(width, height, "Pac-Man", glfwGetPrimaryMonitor(), nullptr);*/
	auto window = glfwCreateWindow(g_level.arrWidth * 35, g_level.arrHeight * 35, "Pac-Man", nullptr, nullptr);
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
	//construct ghosts
	int ghostStartRow, ghostStartCol;
	std::vector<Ghost*> ghostArr(4, nullptr);
	if(!getGhostPos(ghostArr.size(), ghostStartRow, ghostStartCol)){
		std::cerr << "Get ghost position failed.\n";
		glfwTerminate();
		std::cin.get();
		return EXIT_FAILURE;
	}
	for(int i = 0; i < ghostArr.size(); i++) {
		ghostArr[i] = new Ghost(ghostStartRow + i, ghostStartCol);
	}
	//construct pellets
	Pellet pellet;
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
		//draw wall
		wall.drawObject();
		//draw pellets
		pellet.drawObject();
		//draw pacman
		pacman.drawObject(window);
		if (!g_gameover && deltaTime >= 1.0){
			pacman.movObject(pellet);
		}
		//draw ghosts
		for(int i = 0; i < ghostArr.size(); i++) {
			ghostArr[i]->drawObject();
			if (!g_gameover && deltaTime >= 1.0){
				ghostArr[i]->movObject();
			}
		}
		//reset time control
		if (!g_gameover && deltaTime >= 1.0) deltaTime -= 1.0;
		//go to next buffer
		glfwSwapBuffers(window);
		//break loop if 'ESC' key is pressed
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
	}
	std::cout << "\nFinal score was: " << g_level.score << '/' << g_level.pelletSize << '\n';
	//clear memory
	for(int i = 0; i < ghostArr.size(); i++) {
		delete ghostArr[i];
	}
	ghostArr.clear();
	glUseProgram(0);
	glfwTerminate();
	return EXIT_SUCCESS;
}
