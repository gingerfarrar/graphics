#pragma once

#include "graphics\RenderObjects.h"

void s0_draw(const FrameBuffer &f, const Shader &s, const Geometry &g);

void clearFramebuffer(const FrameBuffer &f);

void setUniform(const Shader &s, int location, float value);

void setUniform(const Shader &s, int location, int value);

void setUniform(const Shader &s, int location, const Texture &value, unsigned slot);