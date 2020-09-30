#ifndef __WALL_H_
#define __WALL_H_

#include <string>

static const std::string squareVertexShaderSrc = R"(
#version 430 core

layout(location = 0) in vec2 a_Position;

void main() {
	gl_Position = vec4(a_Position, 0.f, 1.f);
}
)";

static const std::string squareFragmentShaderSrc = R"(
#version 430 core

out vec4 color;

void main() {
    //set color blue
    color = vec4(.09f, .09f, .4f, 1.f);
}
)";

#endif
