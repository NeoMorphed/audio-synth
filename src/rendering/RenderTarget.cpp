#include "RenderTarget.h"

namespace Tactics
{
	// RenderTarget::RenderTarget()
	// {
	// }
	// RenderTarget::RenderTarget(int width, int height)
	// 	:width(width), height(height)
	// {
	// 	glGenFramebuffers(1, &rendererID);
	// 	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
	// 	GLCall(glGenTextures(1, &texID));
	// 	glActiveTexture(GL_TEXTURE0);
	// 	GLCall(glBindTexture(GL_TEXTURE_2D, texID));
	// 	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));

	// 	//@Cleanup This should be dependent on the way the entire sprite batch is rendered rather than an invidual basis
	// 	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	// 	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	// 	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	// 	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texID, 0));	

	// 	if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE))
	// 	{
	// 		log_error("GL::ERROR: Framebuffer not complete");
	// 	}
	// 	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// }
	void make_render_target(RenderTarget* render_target, int width, int height)
	{
		render_target->width = width;
		render_target->height = height;
		glGenFramebuffers(1, &render_target->rendererID);
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, render_target->rendererID));
		GLCall(glGenTextures(1, &render_target->texID));
		glActiveTexture(GL_TEXTURE0);
		GLCall(glBindTexture(GL_TEXTURE_2D, render_target->texID));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));

		//@Cleanup This should be dependent on the way the entire sprite batch is rendered rather than an invidual basis
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_target->texID, 0));	

		if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE))
		{
			log_error("GL::ERROR: Framebuffer not complete");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);	
	}
}