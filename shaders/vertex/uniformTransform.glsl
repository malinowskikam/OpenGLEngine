#version 330

layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec4 inNormal;
layout (location = 2) in vec2 inUv;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragUv;

uniform mat4 model;
uniform mat4 itmodel;
uniform mat4 projView;

void main()
{
	fragPosition = vec3(model * inPosition);
	fragNormal = normalize(mat3(itmodel)*vec3(inNormal));
	fragUv = inUv;

	gl_Position = projView * model * inPosition;
}
