#include "graphics\Load.h"
#include "graphics\RenderObjects.h"
#include "graphics\Context.h"
#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "glm\ext.hpp"
#include <vector>
#include <string>
//skybox 
//first of all wtf

void main()
{
	Context context;
	context.init(1280, 720);

	Framebuffer screen = { 0,1280, 720 };
	std::vector<std::string> faces;

	glm::mat4 sky_model;

	// Cube
		Geometry cube_geo = loadGeometry("../../resources/models/cube.obj");
		glm::mat4 cube_model = glm::translate(glm::vec3(2, 1, -1));

	// Camera
		glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 2, 5),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0));
		glm::mat4 cam_proj = glm::perspective(45.f, screen.width / (float)screen.height, 1.f, 1000.f);

	//shader
		Shader shdr_skybox = loadShader("../../resources/shaders/skybox.vert",
			"../../resources/shaders/skybox.frag");

	//skybox		

		faces = { "../../resources/textures/stormydays_ft.tga",
			      "../../resources/textures/stormydays_bk.tga",
				  "../../resources/textures/stormydays_up.tga",
				  "../../resources/textures/stormydays_dn.tga",
				  "../../resources/textures/stormydays_rt.tga",
				  "../../resources/textures/stormydays_lf.tga" };

		Skybox skybox = loadCubeMap(faces);

		sky_model = glm::scale(glm::vec3(20, 20, 20));



	int loc, slot;
	while (context.step())
	{
		float time = context.getTime();

		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);
		sky_model = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(100,100,100));
		loc = slot = 0;
		setUniforms(shdr_skybox, loc, slot, cam_proj, cam_view, sky_model, skybox);
			s0_draw(screen, shdr_skybox, cube_geo);
	}

}