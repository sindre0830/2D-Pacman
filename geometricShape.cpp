/* library */
#include "header/geometricShape.h"
#include <set>
/**
 * @brief Destroy the Geometric Shape:: Geometric Shape object
 * 
 */
GeometricShape::~GeometricShape() {
	glDeleteProgram(shapeShaderProgram);
    destroyVAO(shapeVAO);
}
/**
 * @brief Compile the vertex and fragment shader.
 * 
 * @param vertexShaderSrc 
 * @param fragmentShaderSrc 
 * @return GLuint 
 */
GLuint GeometricShape::compileShader(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc) {

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

	glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
/**
 * @brief Generate VAO (rectangle shape)
 * 
 * @return GLuint 
 */
GLuint GeometricShape::genObject(const std::vector<GLfloat> arr, const int size) {
    std::vector<GLuint> arrIndices = genIndices(size);
    return createVAO(arr, arrIndices);
}
/**
 * @brief Create the VAO, VBO and EBO. Bind the objects to memory.
 * 
 * @param arr
 * @param arr_indices
 * @return GLuint
 */
GLuint GeometricShape::createVAO(const std::vector<GLfloat> &arr, const std::vector<GLuint> &arr_indices) {
	//create and bind the vertex array object
	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//create the vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	//set vbo to arr data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, arr.size() * sizeof(GLfloat), arr.data(), GL_STATIC_DRAW);
	//create the element buffer object
	GLuint ebo;
	glGenBuffers(1, &ebo);
	//set ebo to arr_indices data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arr_indices.size() * sizeof(GLuint), arr_indices.data(), GL_STATIC_DRAW);
	return vao;
}
/**
 * @brief Generate indices for rectangle shape
 * 
 * @param size 
 * @return std::vector<GLuint> 
 */
std::vector<GLuint> GeometricShape::genIndices(const int size) {
    std::vector<GLuint> arrIndices;
    for (int i = 0, j = 0; i < size; i++, j += 4) {
		//row 1
		arrIndices.push_back(j);
		arrIndices.push_back(j + 1);
		arrIndices.push_back(j + 2);
		//row 2
		arrIndices.push_back(j);
		arrIndices.push_back(j + 2);
		arrIndices.push_back(j + 3);
	}
    return arrIndices;
}
/**
 * @brief Clear data from memory.
 * 
 * @param vao 
 */
void GeometricShape::destroyVAO(GLuint &vao) {
	GLint nAttr = 0;
	std::set<GLuint> vbos;

	GLint eboId;
	glGetVertexArrayiv(vao, GL_ELEMENT_ARRAY_BUFFER_BINDING, &eboId);
	glDeleteBuffers(1, (GLuint*)&eboId);

	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttr);
	glBindVertexArray(vao);

	for (int iAttr = 0; iAttr < nAttr; ++iAttr) {
		GLint vboId = 0;
		glGetVertexAttribiv(iAttr, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &vboId);
		if (vboId > 0) {
			vbos.insert(vboId);
		}
		glDisableVertexAttribArray(iAttr);
	}

	for(auto vbo : vbos) {
	  glDeleteBuffers(1, &vbo);
	}

	glDeleteVertexArrays(1, &vao);
}
