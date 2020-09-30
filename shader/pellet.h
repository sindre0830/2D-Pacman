#ifndef __PELLET_H_
#define __PELLET_H_

#include <string>

static const std::string pelletVertexShaderSrc = R"(
#version 430 core

layout(location = 0) in vec2 a_Position;

void main() {
	gl_Position = vec4(a_Position, 0.f, 1.f);
}
)";

static const std::string pelletFragmentShaderSrc = R"(
#version 430 core

out vec4 color;

void main() {
    //set color white
    color = vec4(1.f, 1.f, 1.f, 1.f);
}
)";

#endif
