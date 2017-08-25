#version 450

in vec2 vUV;
in vec4 vnormal;

out vec4 outColor;

layout(location = 1) uniform sampler2D map;

	void main()
	{
		outColor = dot(vnormal, -normalize(vec4(1,0,1,0)) * texture(map, vUV);
	}