#include "headers/functions.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <iostream>
#include <set>
GLuint createVAO(std::vector<GLfloat> arr, std::vector<GLuint> arr_indices) {
	//create and bind the vertex array object
	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//create the vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	//set vbo to arr data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, arr.size() * sizeof(arr), &arr[0], GL_STATIC_DRAW);
	//create the element buffer object
	GLuint ebo;
	glGenBuffers(1, &ebo);
	//set ebo to arr_indices data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arr_indices.size() * sizeof(arr_indices), &arr_indices[0], GL_STATIC_DRAW);
	//set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void*)0);
	glEnableVertexAttribArray(0);
	return vao;
}
GLuint load_opengl_texture(const std::string& filepath, GLuint slot) {
	//flip image
	stbi_set_flip_vertically_on_load(true);
	//load pixel data from a stored image
    int w, h, bpp;
    auto pixels = stbi_load(filepath.c_str(), &w, &h,&bpp, STBI_rgb_alpha);
    //generate the texture
	GLuint tex{};
    glGenTextures(1, &tex);					//generate a texture object
    glActiveTexture(GL_TEXTURE0 + slot);	//set the active texture
    glBindTexture(GL_TEXTURE_2D, tex);		//bind texture
	//transfer the image data to the texture in GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    //set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /** Very important to free the memory returned by STBI, otherwise we leak */
    if(pixels) stbi_image_free(pixels);
    return tex;
}
void Transform(const float x, const float y, const GLuint shaderprogram) {
    //Presentation below purely for ease of viewing individual components of calculation, and not at all necessary.

    //Translation moves our object.        base matrix      Vector for movement along each axis
    glm::mat4 translation = glm::translate(glm::mat4(1), glm::vec3(x, y, 0.f));

    //Rotate the object                    base matrix      degrees to rotate          axis to rotate around
    //glm::mat4 rotation = glm::rotate(glm::mat4(1), glm::radians(time) * 10, glm::vec3(0, 0, 1));

    //Scale the object                     base matrix      vector containing how much to scale along each axis (here the same for all axis)
    //glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(sin(time)));

    //Create transformation matrix      These must be multiplied in this order, or the results will be incorrect
    glm::mat4 transformation = translation/* * rotation * scale*/;


    //Get uniform to place transformation matrix in
    //Must be called after calling glUseProgram         shader program in use   Name of Uniform
    GLuint transformationmat = glGetUniformLocation(shaderprogram, "u_TransformationMat");

    //Send data from matrices to uniform
    //                 Location of uniform  How many matrices we are sending    value_ptr to our transformation matrix
    glUniformMatrix4fv(transformationmat, 1, false, glm::value_ptr(transformation));
}
/**
 * Eanable capture of debug output.
 */
void enableDebug() {
    glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(MessageCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}
/**
 * Compile vertex and fragment shader.
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

	glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
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