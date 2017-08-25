// Graphics\resources\shaders\mvplite.frag
#version 450

out vec4 outColor;
in vec2 vUV;
in vec4 vPos;
in vec4 vNormal;

layout (location = 3) uniform sampler2D diffuse;

out vec4 outColor;

void main()
{
	vec3 L = normalize(vec3(1,-1,-1));
	vec3 N = vNormal.xyz;

	float lamb = dot(N, -L);

    outColor = texture(diffuse, vUV);
}