#ifndef __SCOREBOARD_H_
#define __SCOREBOARD_H_
/* library */
#include <string>

static const std::string scoreboardVertexShaderSrc = R"(
#version 430 core

/** Inputs */
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexcoord;

/** Outputs */
out vec2 vsTexcoord;

uniform mat4 u_TransformationMat = mat4(1);
uniform mat3 u_TransformationTex = mat3(1);

void main() {
	vec3 new_texture_coordinates = u_TransformationTex * vec3(aTexcoord, 1.0f);
	vsTexcoord = vec2(new_texture_coordinates);
	
	//We multiply our matrices with our position to change the positions of vertices to their final destinations.
	gl_Position = u_TransformationMat * vec4(aPosition, 0.0f, 1.0f);
}
)";

static const std::string scoreboardFragmentShaderSrc = R"(
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
