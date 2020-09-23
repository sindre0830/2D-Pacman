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
/* global variables */
const int
	gRow = 28,
	gCol = 36;
int gMap[36][28] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
	{1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
	{1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int gWallSize, gPelletSize;
/* defining functions */
void readLevel();
GLuint CompileShader(const std::string& vertexShader, const std::string& fragmentShader);
GLuint CreateMaze();
GLuint createPellets();
void CleanVAO(GLuint &vao);
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
/**
 * Main program.
 */
int main() {
	readLevel();
	//initialization of GLFW
	if(!glfwInit())
	{
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
	auto window = glfwCreateWindow(840, 1080, "SandBox", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "GLFW failed on window creation." << '\n';
		std::cin.get();

		glfwTerminate();

		return EXIT_FAILURE;
	}
	//setting the OpenGL context
	glfwMakeContextCurrent(window);
	//initialization of GLEW
	if(glewInit() != GLEW_OK)
	{
	  std::cerr << "GLEW initialization failuare." << '\n';
	  std::cin.get();

	  return EXIT_FAILURE;
	}
	//eanable capture of debug output
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(MessageCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	//create maze
	auto mazeVAO = CreateMaze();
	auto squareShaderProgram = CompileShader(squareVertexShaderSrc, squareFragmentShaderSrc);
	//create pellets
	auto pelletVAO = createPellets();
	auto pelletShaderProgram = CompileShader(squareVertexShaderSrc, squareFragmentShaderSrc);
	//set background color red
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//loop until user closes window
	while(!glfwWindowShouldClose(window)) {
		//???
		glfwPollEvents();
		//for every frame reset background color to the value in the buffer ???
		glClear(GL_COLOR_BUFFER_BIT);
		//draw maze
		auto vertexColorLocation = glGetUniformLocation(squareShaderProgram, "u_Color");
		glUseProgram(squareShaderProgram);
		glBindVertexArray(mazeVAO);
		glUniform4f(vertexColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, (6 * gWallSize), GL_UNSIGNED_INT, (const void*)0);
		//draw pellets
		auto vertexColorLocation1 = glGetUniformLocation(pelletShaderProgram, "u_Color");
		glUseProgram(pelletShaderProgram);
		glBindVertexArray(pelletVAO);
		glUniform4f(vertexColorLocation1, 1.0f, 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, (6 * gPelletSize), GL_UNSIGNED_INT, (const void*)0);
		//???
		glfwSwapBuffers(window);
		//break loop if 'ESC' key is pressed
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
	}
	//clean memory
	glUseProgram(0);
	glDeleteProgram(squareShaderProgram);
	glDeleteProgram(pelletShaderProgram);
	CleanVAO(mazeVAO);
	CleanVAO(pelletVAO);
	glfwTerminate();
	return EXIT_SUCCESS;
}
/**
 * Read level design
 * gWallSize = 708, gPelletSize = 299
 */
void readLevel() {
	for (int i = 0; i < gCol; i++) {
		for (int j = 0; j < gRow; j++) {
			if (gMap[i][j] == 1) {
				gWallSize++;
			} else if (gMap[i][j] == 0) {
				gPelletSize++;
			}
		}
	}
	std::cout << "gWallSize = " << gWallSize << " gPelletSize = " << gPelletSize << std::endl;
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
 * Create maze
 */
GLuint CreateMaze() {
	/* local variables */
	float
		x = -1.0f,
		y = -1.0f,
		z = 0.0f,
		rowInc = 1.0f / ((float)(gRow) / 2),
		colInc = 1.0f / ((float)(gCol) / 2);
	std::vector<GLfloat> arr;
	std::vector<GLuint> arr_indices;
	//fills in arr with coordinates
	for (int i = 0; i < gCol; i++, x = -1.0f, y += colInc) {
		for (int j = 0; j < gRow; j++, x += rowInc) {
			if (gMap[i][j] == 1) {
				//top left coordinate
				arr.push_back(x);
				arr.push_back(y + colInc);
				arr.push_back(z);
				//bottom left coordinate
				arr.push_back(x);
				arr.push_back(y);
				arr.push_back(z);
				//bottom right coordinate
				arr.push_back(x + rowInc);
				arr.push_back(y);
				arr.push_back(z);
				//top right coordinate
				arr.push_back(x + rowInc);
				arr.push_back(y + colInc);
				arr.push_back(z);
			}
		}
	}
	//fills in map_indicies array
	for (int i = 0, j = 0; i < gWallSize; i++, j += 4) {
		//row 1
		arr_indices.push_back(j);
		arr_indices.push_back(j + 1);
		arr_indices.push_back(j + 2);
		//row 2
		arr_indices.push_back(j);
		arr_indices.push_back(j + 2);
		arr_indices.push_back(j + 3);
	}
	//create and bind the vertex array object
	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//create the vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	//set vbo to map data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, arr.size() * sizeof(arr), &arr[0], GL_STATIC_DRAW);
	//create the element buffer object
	GLuint ebo;
	glGenBuffers(1, &ebo);
	//set ebo to map_indices data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arr_indices.size() * sizeof(arr_indices), &arr_indices[0], GL_STATIC_DRAW);
	//set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void *)0);
	glEnableVertexAttribArray(0);
	return vao;
}
/**
 * Create Pellets
 */
GLuint createPellets() {
	/* local variables */
	float
		x = -1.0f,
		y = -1.0f,
		z = 0.0f,
		rowInc = 1.0f / ((float)(gRow) / 2),
		colInc = 1.0f / ((float)(gCol) / 2);
	std::vector<GLfloat> arr;
	std::vector<GLuint> arr_indices;
	//fills in arr with coordinates
	for (int i = 0; i < gCol; i++, x = -1.0f, y += colInc) {
		for (int j = 0; j < gRow; j++, x += rowInc) {
			if (gMap[i][j] == 0) {
				//top left coordinate
				arr.push_back((x + (rowInc / 3.0f)));
				arr.push_back((y + colInc) - (colInc / 3.0f));
				arr.push_back(z);
				//bottom left coordinate
				arr.push_back((x + (rowInc / 3.0f)));
				arr.push_back(y + (colInc / 3.0f));
				arr.push_back(z);
				//bottom right coordinate
				arr.push_back((x + rowInc) - (rowInc / 3.0f));
				arr.push_back(y + (colInc / 3.0f));
				arr.push_back(z);
				//top right coordinate
				arr.push_back((x + rowInc) - (rowInc / 3.0f));
				arr.push_back((y + colInc) - (colInc / 3.0f));
				arr.push_back(z);
			}
		}
	}
	//fills in map_indicies array
	for (int i = 0, j = 0; i < gPelletSize; i++, j += 4) {
		//row 1
		arr_indices.push_back(j);
		arr_indices.push_back(j + 1);
		arr_indices.push_back(j + 2);
		//row 2
		arr_indices.push_back(j);
		arr_indices.push_back(j + 2);
		arr_indices.push_back(j + 3);
	}
	//create and bind the vertex array object
	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//create the vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	//set vbo to map data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, arr.size() * sizeof(arr), &arr[0], GL_STATIC_DRAW);
	//create the element buffer object
	GLuint ebo;
	glGenBuffers(1, &ebo);
	//set ebo to map_indices data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arr_indices.size() * sizeof(arr_indices), &arr_indices[0], GL_STATIC_DRAW);
	//set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void*)0);
	glEnableVertexAttribArray(0);
	return vao;
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
