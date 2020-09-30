#ifndef __ASSET_H_
#define __ASSET_H_

#include <string>

static const std::string assetVertexShaderSrc = R"(
#version 430 core

/** Inputs */
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexcoord;

/** Outputs */
out vec3 vsColor;
out vec2 vsTexcoord;

uniform mat4 u_TransformationMat = mat4(1);
uniform mat3 u_TransformationTex = mat3(1);

void main() {
	//Pass the color and texture data for the fragment shader
	vsColor = aColor;

	vec3 new_texture_coordinates = u_TransformationTex * vec3(aTexcoord, 1.0f);
	vsTexcoord = vec2(new_texture_coordinates);
	
	//We multiply our matrices with our position to change the positions of vertices to their final destinations.
	gl_Position = u_TransformationMat * vec4(aPosition, 0.0f, 1.0f);
}
)";

static const std::string assetFragmentShaderSrc = R"(
#version 430 core

/** Inputs */
in vec3 vsColor;
in vec2 vsTexcoord;

/** Outputs */
out vec4 outColor;

/** Binding specifies what texture slot the texture should be at (in this case TEXTURE0) */
uniform sampler2D uTextureA;

void main() {
	vec4 textColorA = texture(uTextureA, vsTexcoord);
	outColor = textColorA * vec4(vsColor, 1.0);
}
)";


#endif
