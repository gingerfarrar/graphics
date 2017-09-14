#version 450
out vec4 FragColor;

in vec3 vPos;
in vec2 TexCoord;

layout(location = 3) uniform samplerCube skybox;



void main()
{    
    FragColor = texture(skybox, vPos);
}