#ifndef __CHARACTERSHADER_H_
#define __CHARACTERSHADER_H_
/* library */
#include <string>
//vertex shader
static const std::string characterVertexShader = R"(
#version 430 core
//input
layout(location = 0) in vec2 gridPos;
layout(location = 1) in vec2 texPos;
//output
out vec2 vs_texPos;
//uniform
uniform mat4 u_transformationPos = mat4(1);
uniform mat3 u_transformationTex = mat3(1);

void main() {
	//transform texture coordinates
	vec3 newTexPos = u_transformationTex * vec3(texPos, 1.0f);
	vs_texPos = vec2(newTexPos);
	//transform grid coordinates
	gl_Position = u_transformationPos * vec4(gridPos, 0.0f, 1.0f);
}
)";
//fragment shader
static const std::string characterFragmentShader = R"(
#version 430 core
//input
in vec2 vs_texPos;
//output
out vec4 color;
//uniform
uniform sampler2D u_texture;
uniform int u_changeColor = 0;

void main() {
	vec4 textColorA = texture(u_texture, vs_texPos);
	//branch if color should change
	if(u_changeColor == 1) {
		color = textColorA * vec4(0.5f, 1.f, 0.5f, 1.f);
	} else color = textColorA * vec4(1.f, 1.f, 1.f, 1.f);
}
)";
#endif
