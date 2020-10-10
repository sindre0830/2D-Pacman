/* libraries */
#include "header/function.h"
#include "header/levelData.h"
#include <GLFW/glfw3.h>

extern LevelData g_level;
/**
 * @brief Reads data from level file.
 */
bool readFile() {
	std::ifstream file;
	file.open("level/level0");
	if (file) {
		int buffer;
		file >> g_level.arrWidth;
		file.ignore();
		file >> g_level.arrHeight;
		file.ignore();
		for (int i = 0; i < g_level.arrHeight; i++) {
			std::vector<int> arrRow;
			std::vector<bool> boolRow;
			for (int j = 0; j < g_level.arrWidth; j++) {
				file >> buffer;
				if (buffer == 1) {
					g_level.wallSize++;
				} else if (buffer == 0) {
					g_level.pelletSize++;
				}
				arrRow.push_back(buffer);
				boolRow.push_back(false);
				file.ignore();
			}
			g_level.arr.push_back(arrRow);
			g_level.ghostPos.push_back(boolRow);
		}
		file.close();
		//reverse order of array
		std::reverse(g_level.arr.begin(), g_level.arr.end());
		//set element value
		g_level.elementWidth = 1.f / ((float)(g_level.arrWidth) / 2.f);
		g_level.elementHeight = 1.f / ((float)(g_level.arrHeight) / 2.f);
		return true;
	} else return false;
}
/**
 * @brief Eanable capture of debug output.
 */
void enableDebug() {
    glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(messageCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
	//glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}
/**
 * @brief Customize the error message.
 * 
 * @param source 
 * @param type 
 * @param id 
 * @param severity 
 * @param length 
 * @param message 
 * @param userParam 
 */
void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ) {
	std::cerr 
		<< "GL CALLBACK:" << ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ) 
		<< "type = 0x" << type 
		<< ", severity = 0x" << severity 
		<< ", message =" << message << '\n';
}

bool getGhostPos(const int size, int &row, int &col) {
	bool flag = true;
	row = (g_level.arrWidth / 2) - (size / 2);
	for(int i = g_level.arrHeight - 1; i >= 0; i--, flag = true) {
		for(int j = 0; j < size; j++) {
			if(g_level.arr[i][row + j] != 0) flag = false;
			col = i;
		}
		if(flag) return true;
	}
	return false;
}

void get_resolution(int &width, int &height) {
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    width = mode->width;
    height = mode->height;
}
