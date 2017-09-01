#include "graphics\Context.h"
#include "graphics\Draw.h"
#include "graphics\Load.h"
#include "graphics\RenderObjects.h"
#include "graphics\GameObjects.h"
#include "graphics\Vertex.h"
#include "glm\ext.hpp"

int main()
{
	Context context;
	context.init();

	Vertex vquad[] = {
		{ {-1,-1,0,1 },{},{ 0 ,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1 ,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1 ,1 },{ 0,0,1,0 } },
		{ {-1, 1,0,1 },{},{ 0 ,1 },{ 0,0,1,0 } }

	};
	
	unsigned quadidx[] = { 0,1,3,1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Shader standard = loadShader("../../resources/shaders/standard.vert",
								 "../../resources/shaders/standard.frag");

	Framebuffer screen = { 0,800,600 };
	Framebuffer fbuffer = makeFramebuffer(800, 600, 4, true, 3, 1);
	Shader fsq_shader = loadShader("../../resources/shaders/quad.vert",
								   "../../resources/shaders/quad.frag");
	//////////////////////////
	//model data
	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model;

	Texture ss_normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Texture ss_specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	float ss_gloss = 4.0f;
	
	/////////////////////////////////
	//camera
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 2, 3),
									glm::vec3(0, 2, 0),
									glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

	//light
	glm::vec3 l_dir = glm::normalize(glm::vec3(.2, -1, -1));
	glm::vec4 l_color = glm::vec4(1.0,.5,1.0,1);
	float l_intensity = 1;
	glm::vec4 l_ambient = glm::vec4(.2,.5,.1,1);
	int l_type = 0;

	while (context.step())
	{
		float time = context.getTime();
		ss_model = glm::rotate(time, glm::vec3(0, 1, 0));
				

		clearFramebuffer(fbuffer);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, slot = 0;
		setUniforms(standard, loc, slot,
			cam_proj, cam_view, //camera
			ss_model,ss_diffuse,ss_specular, ss_normal,ss_gloss, //model
			l_dir,l_color,l_intensity,l_ambient,l_type); //light

		s0_draw(fbuffer, standard, ss_geo);

		//screen pass
		clearFramebuffer(screen);
		loc = 0, slot = 0;
		setUniforms(fsq_shader, loc, slot, fbuffer.targets[1], fbuffer.targets[2]);
		s0_draw(screen, fsq_shader, quad);

	}
	context.term();
	return 0;

}