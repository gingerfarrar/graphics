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

void setUniform(const Shader &s, int location, float value)
{
	glProgramUniform1f(s.handle, location,value);
}

void clearFramebuffer(const FrameBuffer &f)
{
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void setUniform(const Shader &s, int location, int value)
{
	glProgramUniform1i(s.handle, location, value);
}

void setUniform(const Shader &s, int location, const Texture &value, unsigned slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, value.handle);

	glProgramUniform1i(s.handle, location, slot);
}