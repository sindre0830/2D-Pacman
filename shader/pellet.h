#ifndef __PELLET_H_
#define __PELLET_H_
/* library */
#include <string>

static const std::string pelletVertexShaderSrc = R"(
#version 430 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in float a_Display;

out float vs_Display;

void main() {
    vs_Display = a_Display;
	gl_Position = vec4(a_Position, 0.f, 1.f);
}
)";

static const std::string pelletFragmentShaderSrc = R"(
#version 430 core

in float vs_Display;

out vec4 color;

void main() {
    if(vs_Display == 1.f) {
        //set color white
        color = vec4(1.f, 1.f, 1.f, 1.f); 
    } else {
        //set color black
        color = vec4(0.f, 0.f, 0.f, 1.f); 
    }   
}
)";

#endif
