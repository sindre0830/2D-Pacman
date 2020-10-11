/* library */
#include "header/function.h"
#include "header/levelData.h"
#include <GLFW/glfw3.h>
/* dictionary */
extern enum Target {PELLET, WALL, PACMAN, EMPTY};
/* global data */
extern LevelData g_level;
/**
 * @brief Reads data from level file.
 */
bool readFile() {
	std::ifstream file;
	file.open(g_level.filePath);
	if (file) {
		int buffer;
		file >> g_level.arrWidth;
		file.ignore();
		file >> g_level.arrHeight;
		file.ignore();
		for (int i = 0; i < g_level.arrHeight; i++) {
			std::vector<int> arrRow;
			for (int j = 0; j < g_level.arrWidth; j++) {
				file >> buffer;
				if (buffer == WALL) {
					g_level.wallSize++;
				} else if (buffer == PELLET) {
					//branch if position is a teleportation entrence
					if(i == 0 || i == g_level.arrHeight - 1 || j == 0 || j == g_level.arrWidth - 1) {
						buffer = EMPTY;
					} else g_level.pelletSize++;
				}
				arrRow.push_back(buffer);
				file.ignore();
			}
			g_level.arr.push_back(arrRow);
		}
		file.close();
		//reverse order of array
		std::reverse(g_level.arr.begin(), g_level.arr.end());
		//set element value
		g_level.elementWidth = 1.f / ((float)(g_level.arrWidth) / 2.f);
		g_level.elementHeight = 1.f / ((float)(g_level.arrHeight) / 2.f);
		
		float
			x = -1.f,
			y = -1.f;
		//fills in array with coordinates
		for (int i = 0; i < g_level.arrHeight; i++, x = -1.f, y += g_level.elementHeight) {
			for (int j = 0; j < g_level.arrWidth; j++, x += g_level.elementWidth) {
				//top left
				g_level.gridElement[std::make_pair(i, j)].push_back({x, y + (float)(g_level.elementHeight)});
				//bottom left
				g_level.gridElement[std::make_pair(i, j)].push_back({x, y});
				//bottom right
				g_level.gridElement[std::make_pair(i, j)].push_back({x + (float)(g_level.elementWidth), y});
				//top right
				g_level.gridElement[std::make_pair(i, j)].push_back({x + (float)(g_level.elementWidth), y + (float)(g_level.elementHeight)});
			}
		}
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
	//set first ghost position on row
	row = (g_level.arrWidth / 2) - (size / 2);
	//branch if pacman won't start at the top
	if(g_level.pacmanCol != g_level.arrHeight - 1) {
		//search top to bottom for ghost positions
		for(int i = g_level.arrHeight - 1; i >= 0; i--, flag = true) {
			for(int j = 0; j < size; j++) {
				if(g_level.arr[i][row + j] != PELLET) flag = false;
				col = i;
			}
			if(flag) return true;
		}
	} else {
		//search bottom to top for ghost positions
		for(int i = 0; i < g_level.arrWidth; i++, flag = true) {
			for(int j = 0; j < size; j++) {
				if(g_level.arr[i][row + j] != PELLET) flag = false;
				col = i;
			}
			if(flag) return true;
		}
	}
	return false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
	get_resolution(width, height);
}

void get_resolution(int &width, int &height) {
    const float aspectRatio = ((float)width) / height;
    float xSpan = 1; // Feel free to change this to any xSpan you need.
    float ySpan = 1; // Feel free to change this to any ySpan you need.

    if (aspectRatio > 1){
        // Width > Height, so scale xSpan accordinly.
        xSpan *= aspectRatio;
    }
    else{
        // Height >= Width, so scale ySpan accordingly.
        ySpan = xSpan / aspectRatio;
    }

    glOrtho(-1*xSpan, xSpan, -1*ySpan, ySpan, -1.f, 1.f);
    // Use the entire window for rendering.
    glViewport(0, 0, width, height);
	std::cout << "oi";
}
