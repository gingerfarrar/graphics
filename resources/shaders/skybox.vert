#version 450 
layout (location = 0) in vec4 position;
layout (location = 2) in vec2 texcoord; 
layout(location = 0) uniform mat4 projection;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;

out vec3 vPos;
out vec2 TexCoord;

void main()
{ 
    gl_Position = projection * view * model * position; 
	TexCoord = texcoord;
	vPos = (position).xyz;
}