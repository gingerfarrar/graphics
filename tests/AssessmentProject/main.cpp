#include "graphics\Load.h"
#include "graphics\RenderObjects.h"
#include "graphics\Context.h"
#include "graphics\draw.h"
#include "graphics\Vertex.h"

//skybox 
//first of all wtf

void main()
{
	Context context;
	context.init(1280, 720);

	Vertex vquad[] = { { { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };
	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Framebuffer screen = { 0,1280, 720 };

	int loc, slot;
	while (context.step())
	{

	}

}