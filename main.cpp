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
#include "shaders/asset.h"
#include <iostream>
#include <set>
#include <vector>
#include "headers/scenario.h"
#include "headers/functions.h"
#include "headers/pacman.h"
/* global objects */
Scenario gScenario;
Pacman gPacman;
/* global variables */
int gCol, gRow, gWallSize, gPelletSize;
float gPacX, gPacY;
std::vector<std::vector<int>> gLevel;
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
	//reads data from file
	gScenario.readFile();
	//setting window hints
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//create window
	auto window = glfwCreateWindow(840, 1080, "Pac-Man", nullptr, nullptr);
	//branch if window is created
	if (window == nullptr) {
		std::cerr << "GLFW failed on window creation." << '\n';
		std::cin.get();
		glfwTerminate();
		return EXIT_FAILURE;
	}
	//setting the OpenGL context to the window
	glfwMakeContextCurrent(window);
	//branch if GLEW is initialized
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

	//generate pacman
	auto pacmanVAO = gPacman.genAsset();
	GLuint pacmanShaderProgram = CompileShader(assetVertexShaderSrc, assetFragmentShaderSrc);
	// Specify the layout of the vertex data, including the texture coordinates
    GLint posAttrib = glGetAttribLocation(pacmanShaderProgram, "aPosition");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

    GLint colorAttrib = glGetAttribLocation(pacmanShaderProgram, "aColor");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    GLint texAttrib = glGetAttribLocation(pacmanShaderProgram, "aTexcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
    /*Load the texture image, create OpenGL texture, and bind it to the current context*/
    auto texture0 = load_opengl_texture("assets/pacman.png", 0);

	//set background color black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	float 
		x = 0.0f,
		y = 0.0f;
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


		//draw pacman
        auto samplerSlotLocation0 = glGetUniformLocation(pacmanShaderProgram, "uTextureA");
        glUseProgram(pacmanShaderProgram);
        glBindVertexArray(pacmanVAO);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			Transform(x, (y += 0.005f), pacmanShaderProgram);
		} if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			Transform((x -= 0.005f), y, pacmanShaderProgram);
		} if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			Transform(x, (y -= 0.005f), pacmanShaderProgram);
		} if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			Transform((x += 0.005f), y, pacmanShaderProgram);
		}
        glUniform1i(samplerSlotLocation0, 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);


		//swaps the front and back buffers of the specified window. - source: https://www.glfw.org/docs/3.3/group__window.html#ga15a5a1ee5b3c2ca6b15ca209a12efd14
		glfwSwapBuffers(window);
		//break loop if 'ESC' key is pressed
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
	}
	//clean memory
	glUseProgram(0);
	glDeleteProgram(squareShaderProgram);
	glDeleteProgram(pelletShaderProgram);
	glDeleteProgram(pacmanShaderProgram);
    glDeleteTextures(1, &texture0);
	CleanVAO(mapVAO);
	CleanVAO(pelletVAO);
	CleanVAO(pacmanVAO);
	glfwTerminate();
	return EXIT_SUCCESS;
}
