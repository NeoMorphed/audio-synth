#ifndef ASSET_MANAGER___H
#define ASSET_MANAGER___H

namespace Tactics
{

struct Shader;
struct Font;

class std::string;

void 		init_assets();
//void 		load_texture(const std::string& path, TextureType texture_type);
Font* 		load_font(const std::string& path, int size);

}

#endif