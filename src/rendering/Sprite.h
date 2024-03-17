#ifndef SPRITE_H
#define SPRITE_H


#include "core/Rectangle.h"
#include "math/Vectors.h"

namespace Tactics
{
	struct Renderer;
	struct Texture;
	struct Sprite
	{
		Texture* texture;
		Vector2 position;
		float rotation;
		Rectangle source_rect;
		Rectangle collision_offset;
		Vector2 scale;
		Vector2 origin;
		Vector4 color;
	};
	void make_sprite(Texture* texture, Vector2 position, Rectangle source_rect, Sprite* sprite);
	Rectangle get_sprite_bounds(Sprite* sprite);
}
#endif