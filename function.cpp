/* libraries */
#include "header/function.h"

extern int  g_levelRow, g_levelCol, g_wallSize, g_pelletSize;
extern double g_rowInc, g_colInc;
extern std::vector<std::vector<int>> g_level;
extern std::vector<std::vector<bool>> g_ghostPos;
/**
 * @brief Reads data from level file.
 */
bool readFile() {
	std::ifstream file;
	file.open("level/level0");
	if (file) {
		int buffer;
		file >> g_levelRow;
		file.ignore();
		file >> g_levelCol;
		file.ignore();
		for (int i = 0; i < g_levelCol; i++) {
			std::vector<int> arrRow;
			std::vector<bool> boolRow;
			for (int j = 0; j < g_levelRow; j++) {
				file >> buffer;
				if (buffer == 1) {
					g_wallSize++;
				} else if (buffer == 0) {
					g_pelletSize++;
				}
				arrRow.push_back(buffer);
				boolRow.push_back(false);
				file.ignore();
			}
			g_level.push_back(arrRow);
			g_ghostPos.push_back(boolRow);
		}
		file.close();
		//reverse order of array
		std::reverse(g_level.begin(), g_level.end());
		//set increment value
		g_rowInc = 1.f / ((float)(g_levelRow) / 2.f);
		g_colInc = 1.f / ((float)(g_levelCol) / 2.f);
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
	row = (g_levelRow / 2) - (size / 2);
	for(int i = 0; i < g_levelCol; i++) {
		for(int j = row; j < row + size; j++) {
			if(g_level[i][j] != 0) break;
			col = i;
			return true;
		}
	}
	return false;
}