#include "Texture.h"

namespace Tactics
{
	void init_texture(Texture* texture, const char* path, int width, int height, unsigned char* texture_data, unsigned int slot)
	{
		texture-> path = path;
		texture->width = width;
		texture->height = height;
		texture->slot = slot;
		GLCall(glGenTextures(1, &texture->rendererID));
		GLCall(glActiveTexture(GL_TEXTURE0 + texture->slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, texture->rendererID));
		//@Cleanup This should be dependent on the way the entire sprite batch is rendered rather than an invidual basis
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data));	
	}

}
