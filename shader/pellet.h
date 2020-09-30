#ifndef __PELLET_H_
#define __PELLET_H_

#include <string>

static const std::string squareVertexShaderSrc = R"(
#version 430 core

layout(location = 0) in vec3 a_Position;

void main() {
	gl_Position = vec4(a_Position, 1.0f);
}
)";

static const std::string squareFragmentShaderSrc = R"(
#version 430 core

out vec4 color;

void main() {
    //set color white
    color = vec4(1.f, 1.f, 1.f, 1.f);
}
)";

#endif
