#version 450

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 tex;
layout(location = 3) in vec4 nor;

layout(location = 1) uniform mat4 model;

out vec2 vUV;
out vec4 vnormal;

void main()
{
	gl_Position = model * pos;
	vnormal = model * nor;
	vUV = tex;
}