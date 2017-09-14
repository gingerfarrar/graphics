#pragma once
#include "graphics\RenderObjects.h"
#include <vector>
#include <iostream>
#include <string>
Texture loadTexture(const char *path);

Shader loadShader(const char *vpath, const char *fpath);

Geometry loadGeometry(const char *path);

Skybox loadCubeMap(std::vector<std::string> faces);