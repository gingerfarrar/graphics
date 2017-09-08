#pragma once
//Graphics\include\graphics\GameObjects.h
#include "RenderObjects.h"
#include "Draw.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"

struct Transform
{
	glm::vec3 position;
	glm::vec3 scale;
	glm::mat3 rotation; // best to use an interface or helper function

	Transform *parent = nullptr;

	glm::mat4 getLocal() const; // evaluate local matrix: (T*R*S)
	glm::mat4 getGlobal() const; // evaluate global: parent.global * local

								 // helpers for setting a meaningful rotation:
	void axisAngle(float angle, const glm::vec3 &axis = { 0,1,0 });
	void lookAt(const glm::vec3 &target, const glm::vec3 &up = { 0,1,0 });
};

struct Camera
{
	Transform transform;

	float fov = 45.f, aspect = 8.f / 6.f, near = 0.01f, far = 100.0f;

	glm::mat4 proj;
	glm::mat4 view;
};

struct specGloss
{
	Geometry geo;

	glm::mat4 model;
	Texture diffuse;
	Texture specular;
	Texture normal;
	float gloss;
};

struct StandardLight
{
	glm::vec3 dir;
	glm::vec4 color;
	float intensity;
	glm::vec4 ambient;
	int type;

};



struct DirectionalLight
{
	glm::vec3 target;
	float range;

	glm::vec3 direction;
	
	glm::mat4 getProj() const { return glm::ortho<float>(-range,range, -range, range, -range, range); }
	glm::mat4 getView() const { return glm::lookAt(-direction + target, target, glm::vec3(0, 1, 0)); }
	
	glm::vec4 color;
	float intensity;

	
};
struct SimplePresetScene
{
	Camera cam;
	specGloss go[3];
	DirectionalLight dl[2];

	SimplePresetScene();
};
namespace __internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const specGloss &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Camera &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const DirectionalLight &val);
}

struct Mesh
{
	Transform transform;

	Geometry geometry;
};

