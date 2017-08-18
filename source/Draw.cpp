#include "graphics\Draw.h"
#include "glinc.h"

void s0_draw(const FrameBuffer &f, const Shader &s, const Geometry &g)
{
	//what were using
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.handle);

	//what area of framebuffer do we draw to?
	glViewport(0, 0, f.width, f.height);
	
	//draw plz
	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);

	//unbind 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
	glBindVertexArray(0);
}