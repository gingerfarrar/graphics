
#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "genShape.h"
int main()
{
	Context context;
	context.init(800,600);

	//make opengl stuff
	Vertex verts[7] = { {{   0,   0, 0, 1},{1,1,1,1}},
						{{   1,   0, 0, 1},{1,0,1,1}},
						{{ .5f,   1, 0, 1},{1,0,0,1}},
						{{-.5f,   1, 0, 1},{0,0,1,1}},
						{{  -1,   0, 0, 1},{ 1,0,1,1 } },
						{{-.5f,  -1, 0, 1},{ 1,0,0,1 } },
						{{ .5f,  -1, 0, 1},{ 0,0,1,1 } } };

	unsigned idxs[19] = { 1,2,0,2,3,0,3,4,0,4,5,0,5,6,0,6,1,0,1 };

	Geometry g = makeGeometry(verts, 7, idxs, 19);
	Geometry gt = makeNGon(6, .5f);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"out vec4 vPos; out vec4 vcolor;\n"
		"void main () {vPos = position;\n"
		"gl_Position = position; vcolor = color;}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec4 vPos;\n"
		"in vec4 vcolor;\n"
		"void main () { outColor = vcolor; }\n";

	Shader s = makeShader(vsource, fsource);

	FrameBuffer f = { 0, 800,600 };

	while (context.step())
	{
		//draw call
		//s0_draw(f, s, g);
		s0_draw(f, s, gt);
	}

	//delete everything
	freeGeometry(g);
	freeShader(s);

	context.term();
	return 0;
}