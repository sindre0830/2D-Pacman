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
#include "header/scoreboard.h"
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
	//construct scoreboard
	std::vector<Scoreboard*> scoreboardArr(4, nullptr);
	for(int i = 0; i < scoreboardArr.size(); i++) {
		scoreboardArr[i] = new Scoreboard(0, (g_level.arrWidth - 1) - i);
	}
	//construct pacman
	Pacman pacman;
	//construct ghosts
	int ghostStartRow, ghostStartCol;
	std::vector<std::vector<int>> possibleStartingPos;
	for(int i = 0; i < g_level.arrHeight; i++) {
		for(int j = 0; j < g_level.arrWidth; j++) {
			if(g_level.arr[i][j] == PELLET) possibleStartingPos.push_back({i, j});
		}
	}
	std::vector<Ghost*> ghostArr(4, nullptr);
	for(int i = 0; i < ghostArr.size(); i++) {
		//branch if there are too many ghosts and kill the application
		if(ghostArr.size() > possibleStartingPos.size()) {
			std::cerr << "Get ghost position failed.\n";
			glfwTerminate();
			std::cin.get();
			return EXIT_FAILURE;
		}
		getGhostPos(possibleStartingPos, ghostStartRow, ghostStartCol);
		ghostArr[i] = new Ghost(ghostStartRow, ghostStartCol);
	}
	//construct pellets
	Pellet pellet;
	//set background color black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//setup timer
	static double limitFPS = 1.0 / 60.0;
    double lastTime = glfwGetTime(), nowTime = 0, timer = lastTime;
    double deltaTime = 0;
	int counter = 0;
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
		//draw scoreboard
		for(int i = 0; i < scoreboardArr.size(); i++) {
			scoreboardArr[i]->draw();
			if (g_level.scoreChanged) {
				//translate ghosts
				scoreboardArr[i]->update(g_level.getScore(i));
			}
		}
		g_level.scoreChanged = false;
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
		bool flag = true;
		for(int i = 0; i < ghostArr.size(); i++) {
			if(!ghostArr[i]->dead) {
				flag = false;
				ghostArr[i]->draw();
				if (!g_gameover && deltaTime >= 1.0){
					//translate ghosts
					ghostArr[i]->mov();
				}
			}
		}
		if(flag) g_gameover = true;
		
		//reset time control
		if (!g_gameover && deltaTime >= 1.0) deltaTime -= 1.0;
		if(!g_gameover && glfwGetTime() - timer > 1.0f) {
			timer++;
			if(g_level.magicEffect) {
				if(counter == 0) {
					for(int i = 0; i < ghostArr.size(); i++) {
						if(!ghostArr[i]->dead) ghostArr[i]->changeColor(1);
					}
				}
				counter++;
				if(counter >= 5) {
					counter = 0;
					g_level.magicEffect = false;
					for(int i = 0; i < ghostArr.size(); i++) {
						if(!ghostArr[i]->dead) ghostArr[i]->changeColor(0);
					}
				}
			}
		}
		//go to next buffer
		glfwSwapBuffers(window);
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			//get_resolution(window, width, height);
		});
		//break loop if 'ESC' key is pressed
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
	}
	std::cout << "\nFinal score was: " << g_level.score << '/' << g_level.pelletSize << '\n';
	//clear memory
	for(int i = 0; i < scoreboardArr.size(); i++) {
		delete scoreboardArr[i];
	}
	scoreboardArr.clear();
	for(int i = 0; i < ghostArr.size(); i++) {
		delete ghostArr[i];
	}
	ghostArr.clear();
	glUseProgram(0);
	glfwTerminate();
	return EXIT_SUCCESS;
}
