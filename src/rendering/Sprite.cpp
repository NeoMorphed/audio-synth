#include "Sprite.h"
#include "math/common_math.h"


namespace Tactics
{
	void make_sprite(Texture* texture, Vector2 position, Rectangle source_rect, Sprite* sprite)
	{
		sprite->texture = texture;
		sprite->position = position;
		sprite->source_rect = source_rect;
		sprite->rotation = 0;
		sprite->collision_offset = Rectangle(0, 0, 0, 0);
		sprite->scale = vec2(1, 1);
		sprite->origin = vec2(0, 0);
		sprite->color = vec4(1.0f); 
	}
	Rectangle get_sprite_bounds(Sprite* sprite)
	{
		// @Cleanup Sprite position at top left corner
		// Need to switch when sprite pos is in center
		int x = (int)std::floor(sprite->position.x) + sprite->collision_offset.x;
		int y = (int)std::floor(sprite->position.y) + sprite->collision_offset.y;
		int width = sprite->source_rect.width;
		int height = sprite->source_rect.height;
		return Rectangle(x, y, width, height);
	}

}
