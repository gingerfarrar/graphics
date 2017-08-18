#pragma once

struct Vertex;

struct Geometry
{
	unsigned handle, // vertext array object
		vbo,		 //vertex buffer
		ibo,		 //index buffer
		size;		 //how many indices make up the model
};

Geometry makeGeometry(const Vertex *verts, size_t vsize,
					  const unsigned *idxs, size_t isize);

void freeGeometry(Geometry &g);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vert_src, const char *frag_src);
void freeShader(Shader &s);

struct FrameBuffer
{
	unsigned handle, width, height;
};