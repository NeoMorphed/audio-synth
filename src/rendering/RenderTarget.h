#ifndef RENDERTARGET_H
#define RENDERTARGET_H

namespace Tactics
{
	struct RenderTarget
	{
		unsigned int rendererID;
		unsigned int texID;
		int width;
		int height;
	};
	void make_render_target(RenderTarget* render_target, int width, int height);
}

#endif