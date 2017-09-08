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
	specGloss ss;
	ss.geo = loadGeometry("../../resources/models/soulspear.obj");

	ss.normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	ss.diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	ss.specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	ss.gloss = 4.0f;
	
	/////////////////////////////
	//camera
	Camera cam;
	cam.view = glm::lookAt(glm::vec3(0, 2, 3),
									glm::vec3(0, 2, 0),
									glm::vec3(0, 1, 0));
	cam.proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

	/////////////////////////////
	//light
	StandardLight l;
	l.dir = glm::normalize(glm::vec3(.2, -1, -1));
	l.color = glm::vec4(1.0,.5,1.0,1);
	l.intensity = 1;
	l.ambient = glm::vec4(.2,.5,.1,1);
	l.type = 0;

	while (context.step())
	{
		float time = context.getTime();
		ss.model = glm::rotate(time, glm::vec3(0, 1, 0));
				

		clearFramebuffer(fbuffer);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, slot = 0;
		setUniforms(standard, loc, slot,
			cam.proj, cam.view, //camera
			ss.model,ss.diffuse,ss.specular, ss.normal,ss.gloss, //model
			l.dir,l.color,l.intensity,l.ambient,l.type); //light

		s0_draw(fbuffer, standard, ss.geo);

		//screen pass
		clearFramebuffer(screen);
		loc = 0, slot = 0;
		setUniforms(fsq_shader, loc, slot, fbuffer.targets[1], fbuffer.targets[2]);
		s0_draw(screen, fsq_shader, quad);

	}
	context.term();
	return 0;

}