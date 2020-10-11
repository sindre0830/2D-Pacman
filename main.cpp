/**
 * Assignment 1 - Pacman
 * Fully functional pacman game
 *
 * @author Sindre Eiklid (sindreik@stud.ntnu.no)
 * @author Casper Melhus
 * @author Brage Heimly N�ss
 */
/* library */
#include "header/levelData.h"
#include "header/wall.h"
#include "header/pellet.h"
#include "header/pacman.h"
#include "header/ghost.h"
#include "header/function.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
/* dictionary */
enum Direction {UP, LEFT, DOWN, RIGHT};
enum Corner {TOP_LEFT, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_RIGHT};
enum Position {X, Y};
enum Target {PELLET, WALL, PACMAN, EMPTY};
/* global data */
bool g_gameover = false;
LevelData g_level;
/**
 * Main program.
 */
int main() {
	//branch if file isn't initialized and kill the application
	if (!readFile()) {
		std::cerr << "File initialization failed.\n";
		std::cin.get();
		return EXIT_FAILURE;
	}
	//branch if GLFW isn't initialized and kill the application
	if(!glfwInit()) {
		std::cerr << "GLFW initialization failed.\n";
		std::cin.get();
		return EXIT_FAILURE;
	}
	//set window hints
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//create window
	/*int width, height;
	get_resolution(width, height);
	auto window = glfwCreateWindow(width, height, "Pac-Man", glfwGetPrimaryMonitor(), nullptr);*/
	GLFWwindow *window = glfwCreateWindow(g_level.arrWidth * 35, g_level.arrHeight * 35, "Pac-Man", nullptr, nullptr);
	//setting the OpenGL context to the window
	glfwMakeContextCurrent(window);
	//enable transparency on texture
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//branch if window isn't created and kill the application
	if (window == nullptr) {
		std::cerr << "GLFW failed on window creation.\n";
		glfwTerminate();
		std::cin.get();
		return EXIT_FAILURE;
	}
	//branch if GLEW isn't initialized and kill the application
	if(glewInit() != GLEW_OK) {
		std::cerr << "GLEW initialization failuare.\n";
		glfwTerminate();
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
	//branch if there are too many ghosts and kill the application
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
		wall.draw();
		//draw pellets
		pellet.draw();
		//draw pacman
		pacman.draw();
		if (!g_gameover && deltaTime >= 1.0){
			//translate pacman
			pacman.mov(pellet);
			pacman.inputDirection(window);
		}
		//draw ghosts
		for(int i = 0; i < ghostArr.size(); i++) {
			ghostArr[i]->draw();
			if (!g_gameover && deltaTime >= 1.0){
				//translate ghosts
				ghostArr[i]->mov();
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
