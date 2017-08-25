#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "graphics\Load.h"

int main()
{
	Context context;
	context.init(800, 800);
	Vertex vquad[4] = { { {-1, -1, 0, 1 },{ 1,1,1,1 },{0,0} },
						{ { 1, -1, 0, 1 },{ 1,0,1,1 },{1,0} },
						{ { 1,  1, 0, 1 },{ 1,0,0,1 },{1,1} },
						{ {-1,  1, 0, 1 },{ 0,0,1,1 },{0,1} } };

	unsigned quadidx[6] = { 0,1,3,1,2,3 };

	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);
	
	Geometry cube = loadGeometry("../../resources/models/cube.obj");

	Texture tex = loadTexture("../../resources/textures/pepe.jpg");

	Shader sq = loadShader("../../resources/shaders/test.vert",
						   "../../resources/shaders/test.frag");
	Shader scube = loadShader("../../resources/shaders/cube.vert",
							  "../../resources/shaders/cube.frag");
	FrameBuffer screen = { 0, 800,800 };

	while (context.step())
	{
		//draw call
		clearFramebuffer(screen);
		

		//glm::mat4 mod_cube = glm::rotate(time, glm::vec3{ 1,1,1 });

		setFlags(RenderFlag::DEPTH);
		int loc = 0, tslot = 0;
		setUniforms(sq, loc, tslot, tex);
		s0_draw(screen, sq, quad);

	}

	//delete everything	
	
	freeGeometry(quad);
	freeShader(sq);
	context.term();
	return 0;
}
