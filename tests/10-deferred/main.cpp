#include "graphics\Context.h"
#include "graphics\draw.h"
#include "graphics\GameObjects.h"
#include "graphics\RenderObjects.h"
#include "graphics\Load.h"
#include "graphics\Vertex.h"


void main()
{
	Context context;
	context.init(1280, 720);

	SimplePresetScene scene;


	// Fullscreen quad
	Vertex vquad[] = { { { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };
	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	/////////////////////////
	// Shaders

	// draw all geometry to gbuffer
	Shader gpass = loadShader("../../resources/shaders/gpass.vert", "../../resources/shaders/gpass.frag");

	// directional lighting shadow/light pass
	Shader spassD = loadShader("../../resources/shaders/shadow.vert", "../../resources/shaders/shadow.frag");
	Shader lpassD = loadShader("../../resources/shaders/lpassD.vert", "../../resources/shaders/lpassD.frag");

	// composites into the screen
	Shader cpass = loadShader("../../resources/shaders/cpass.vert", "../../resources/shaders/cpass.frag");

	/////////////////////////
	// Buffers
	Framebuffer gbuff = makeFramebuffer(1280, 720, 4, true, 2, 2); // color, spec, pos, normal
	Framebuffer lbuff = makeFramebuffer(1280, 720, 4, false, 2, 0); // color, spec
	Framebuffer sbuff = makeFramebuffer(2048, 2048, 0, true, 0, 0);
	Framebuffer screen = { 0,1280, 720 };


	int loc, slot;
	while (context.step())
	{
		float time = context.getTime();

		//////////////////////////////////
		// GPASS
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(gbuff);
		for (int i = 0; i < 3; ++i)
		{
			loc = slot = 0;
			setUniforms(gpass, loc, slot, scene.cam, scene.go[i]);
			s0_draw(gbuff, gpass, scene.go[i].geo);
		}

		///////////////////////////////////
		//Lpass
		clearFramebuffer(lbuff);
		
		for (int i = 0; i < 2; ++i)
		{
			clearFramebuffer(sbuff);
			setFlags(RenderFlag::DEPTH);
			for (int j = 0; j < 3; ++j)
			{
				loc = slot = 0;
				setUniforms(gpass, loc, slot, scene.dl[i].getProj(), scene.dl[i].getView(), scene.go[j].model);
				s0_draw(sbuff, spassD, scene.go[j].geo);
			}
			//lpass
			setFlags(RenderFlag::ADDITIVE);
			loc = slot = 0;
			setUniforms(lpassD, loc, slot, scene.cam, scene.dl[i], 
				gbuff.targets[3], gbuff.targets[2], sbuff.depthTarget);
			s0_draw(lbuff, lpassD, quad);
		}

		///////////////////////////////////
		// CPASS
		clearFramebuffer(screen);
		loc = slot = 0;
		setUniforms(cpass, loc, slot, gbuff.targets[0],lbuff.targets[0]);
		s0_draw(screen, cpass, quad);
	}

	context.term();
}