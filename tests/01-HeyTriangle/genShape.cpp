#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "glm\glm.hpp"
#include "genShape.h"

Geometry makeNGon(size_t N, float r)
{
	unsigned vsize = N+1;

	unsigned isize = N*3;
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	float a = (2 * 3.14159265359) / N;

	verts[N] = { {0,0,0,1},{1,1,1,1} };

	for (int i = 0; i < N; ++i)
	{
		float x = cos(i*a)*r;
		float y = sin(i*a)*r;

		verts[i] = { {x,y,0,1}, {x,y,0,1} };

		idxs[i * 3+0] = N;
		idxs[i * 3+1] = i;
		idxs[i * 3+2] = i == N-1? 0 : i + 1;
	}

	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;

	return ret;
}

Geometry makeCheckerBoard(int dim, int size)
{
	int N = (dim + 1)*(dim + 1);
	unsigned vsize = (dim + 1)*(dim + 1);

	unsigned isize = 3 * 2 * dim*dim;
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	float step = dim / (float)size;

	for (int i = 0; i < dim; ++i)
	{
		float y = i*step;
		
		for (int j = 0; j < dim; ++j)
		{
			float x = j*step;			
		}
	}


	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;
	
	return ret;
}