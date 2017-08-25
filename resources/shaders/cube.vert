#version 450

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec4 tex;
layout(location = 3) in vec4 nor;

layout(location = 1) uniform mat4 model;

out vec4 vUV;
out vec4 vnormal;

void main()
{
	gl_Position = model * position;
	vnormal = model * pos;
	vUV = tex;
}