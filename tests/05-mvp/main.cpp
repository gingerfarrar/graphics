#include "graphics\Load.h"
#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "glm\ext.hpp"
#include "glm\glm.hpp"
void main()
{
	Context context;
	context.init(800, 600);
	
	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");

	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");

	Shader mvplite = loadShader("../../resources/shaders/mvplite.vert",
								"../../resources/shaders/mvplite.frag");

	FrameBuffer screen = { 0,800,600 };

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);
	glm::mat4 go_model;

	while (context.step())
	{
		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);

		//cam_view = glm::lookAt(glm::vec3(0, 3, -4), targetPosition, glm::vec3(0, 1, 0));

		int loc = 0, slot = 0;
		setUniforms(mvplite, loc, slot, cam_proj, cam_view, go_model, ss_diffuse);
		
		s0_draw(screen, mvplite, ss_geo);
	}
}