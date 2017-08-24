#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "glm\ext.hpp"

int main()
{
	Context context;
	context.init(800, 600);

	//make opengl stuff
	Vertex verts[4] = { { {  0,  0, 0, 1 },{ 1,1,1,1 } },
						{ {.5f,  0, 0, 1 },{ 1,0,1,1 } },
						{ {.5f,.5f, 0, 1 },{ 1,0,0,1 } },
						{ {  0,.5f, 0, 1 },{ 0,0,1,1 } } };

	unsigned idxs[6] = { 0,1,2,0,3,2 };

	Geometry g = makeGeometry(verts, 4, idxs, 6);

	unsigned char pixels[] = { 255,0,255,255,255,0 };

	Texture t_magyel = makeTexture(2, 1, 3, pixels);
	Texture t_mask = makeTexture(4, 1, 3, pixels);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 3) uniform mat4 model;\n"		
		"void main ()\n" 
		"{\n"
		"gl_Position = model * position;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"layout(location = 0) uniform int Key1;\n"
		"layout(location = 1) uniform int Key2;\n"
		"layout(location = 2) uniform int Key3;\n"

		"uniform vec4 Red = vec4(1,0,0,1);\n"
		"uniform vec4 Green = vec4(0,1,0,1);\n"
		"uniform vec4 Blue = vec4(0,0,1,1);\n"

		"void main ()\n"
		"{ outColor = Red*(1-Key1) + Green*Key2 + Blue*Key3;\n "
		"}\n";

	Shader s = makeShader(vsource, fsource);

	FrameBuffer f = { 0, 800,600 };

	while (context.step())
	{
		//draw call
		clearFramebuffer(f);
		glm::mat4 rot = glm::translate(glm::vec3(-.1, 0, 0)) *
		glm::rotate((float)context.getTime(), glm::vec3(0.f, 0.f, 1.f)); 

		//glm::mat4 rot = glm::translate(glm::vec3(.1,.1,0));

		int loc = 0, tex = 0;
		setUniforms(s, loc, tex,
			(int)context.getKey('W'),(int)context.getKey('A'),(int)context.getKey('S'),
			/*glm::vec4(1,1,1,1), glm::vec4(1,0,1,1), glm::vec4(.5,.5,.5,1),*/rot);
		s0_draw(f, s, g);

	}

	//delete everything	
	freeTexture(t_magyel);
	freeTexture(t_mask);
	freeGeometry(g);
	freeShader(s);
	context.term();
	return 0;
}