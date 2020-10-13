#ifndef __GAMEOVERSHADER_H
#define __GAMEOVERSHADER_H
/* library */
#include <string>

static const std::string gameoverVertexShaderSrc = R"(
#version 430 core

/** Inputs */
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexcoord;

/** Outputs */
out vec2 vsTexcoord;

void main() {
	vsTexcoord = aTexcoord;
	gl_Position = vec4(aPosition, 0.0f, 1.0f);
}
)";

static const std::string gameoverFragmentShaderSrc = R"(
#version 430 core

/** Inputs */
in vec2 vsTexcoord;

/** Outputs */
out vec4 color;

/** Binding specifies what texture slot the texture should be at (in this case TEXTURE0) */
uniform sampler2D uTexture;

void main() {
	vec4 textColorA = texture(uTexture, vsTexcoord);
	color = textColorA * vec4(1.f, 1.f, 1.f, 1.f);
}
)";


#endif
