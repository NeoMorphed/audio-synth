
#ifndef TEXTURE_H
#define TEXTURE_H


namespace Tactics
{
	struct Texture
	{
		const char* path;
		unsigned int rendererID;
		int width;
		int height;
		unsigned int slot;
	};
	void init_texture(Texture* texture, const char* path, int width, int height, unsigned char* texture_data, unsigned int slot);
}
#endif