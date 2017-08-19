#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"

int main()
{
	Context context;
	context.init(800, 600);

	//make opengl stuff
	Vertex verts[4] = { { { 0,   0, 0, 1 },{ 1,1,1,1 } },
						{ {.5f,  0, 0, 1 },{ 1,0,1,1 } },
						{ {.5f, .5f, 0, 1 },{ 1,0,0,1 } },
						{ { 0, .5f, 0, 1 },{ 0,0,1,1 } } };

	unsigned idxs[6] = { 0,1,2,0,3,2 };

	Geometry g = makeGeometry(verts, 4, idxs, 6);
	

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 0) uniform float time;\n"
		"out vec4 vcolor;\n"
		"out vec2 vUV;\n"
		"void main () {gl_Position = position; gl_Position.x += sin(time + position.x)/5.0;\n"
		" vcolor = color; vUV = position.xy;}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"layout(location = 0) uniform float time;\n"
		"layout(location = 1) uniform int tog;\n"
		"layout(location = 4) uniform sampler2D map;\n"
		"in vec4 vcolor;\n"
		"in vec2 vUV;\n"
		"void main ()\n"
		"{ if(tog == 1) outColor = 1.0 - vcolor; \n"
		"else outColor = vcolor; outColor.r = sin(time); outColor = texture(map,vUV); }\n";

	Shader s = makeShader(vsource, fsource);

	FrameBuffer f = { 0, 800,600 };

	unsigned char pixels[] = {255,0,255,255,255,0};

	Texture t_magyel = makeTexture(2, 1, 3, pixels);

	while (context.step())
	{
		//draw call

		
		clearFramebuffer(f);
		
		setUniform(s, 0, (float)context.getTime());
		setUniform(s, 1, (int)context.getKey(' '));
		
		setUniform(s, 4, t_magyel, 0);
		s0_draw(f, s, g);
		
	}

	//delete everything
	freeGeometry(g);
	freeShader(s);

	context.term();
	return 0;
}