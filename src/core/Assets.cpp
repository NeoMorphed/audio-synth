#include "Assets.h"

#include "rendering/Font.h"
#include "rendering/Texture.h"
#include "rendering/Shader.h"
#include "rendering/Vertex.h"
#include "core/ErrorCheck.h"

namespace Tactics
{


static FT_Library ft;



// static std::unordered_map<std::string, BmFont*> bm_fonts;

void init_assets()
{
	if (FT_Init_FreeType(&ft))
	{
		log_error("ERROR::FREETYPE: Could not init FreeType Library");
		exit(0);
	}
}
// void load_texture(const std::string& path, TextureType texture_type)
// {
// 	std::string texture_name = get_asset_name_from_path(path);
//     if (textures.find(texture_name) != textures.end())
//     {
//     	log_error("Texture at path " + path + " already exists.");
//     	return;
//     }
// 	int width = 0;
// 	int height = 0;
// 	int BPP = 0;
// 	int n_channels = 0;
// 	if (texture_type == TextureType::RGBA)
// 		n_channels = 4;
// 	else if (texture_type == TextureType::RGB)
// 		n_channels = 3;
// 	stbi_set_flip_vertically_on_load(1);
// 	unsigned char* texture_data = stbi_load(path.c_str(), &width, &height, &BPP, n_channels);
// 	if (texture_data == NULL)
// 	{
// 		log_error("Error in loading the image at path: " + path);
// 		return;
// 	}
// 	Texture* texture = create_platform_texture(path.c_str(), width, height, texture_data, texture_type, (unsigned int)textures.size());
// 	if (texture_data)
// 		stbi_image_free(texture_data);
//     textures.emplace(texture_name, texture);
// }
Font* load_font(const std::string& path, int size)
{
	std::unordered_map<char, FontCharacter> fontCharacters = std::unordered_map<char, FontCharacter>();
	FT_Face face;
	if (FT_New_Face(ft, path.c_str(), 0, &face))
	{
		log_error("ERROR::FREETYPE: Failed to load font \"%s\"", path.c_str());
		exit(0);
	}
	FT_Set_Pixel_Sizes(face, 0, size);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char c = 0; c < 128; c++)
	{

		//load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			log_error("ERROR::FREETYPE: Failed to load Glyph");
			continue;
		}
		//generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		FontCharacter character = 
		{
			texture,
			vec2((float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows),
			vec2((float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top),
			(unsigned int)face->glyph->advance.x
		};
		fontCharacters.insert(std::pair<char, FontCharacter>(c, character));
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	Font* font = new Font(face, fontCharacters);
	font->size = size;
	return font;
}
// Font* load_font(const std::string& path)
// {
// 	std::string font_name = get_asset_name_from_path(path);
// 	if (fonts.find(font_name) != fonts.end())
//     {
//     	log_error("Model at path " + path + " already added.");
//     	return;
//     }
// 	std::ifstream in(path, std::ios::in | std::ios::binary);
//     if (!in)
//         log_error("Cannot open file %s\n", path.c_str());
// 	std::unordered_map<int, FontGlyph> font_glyphs;

// 	float glyph_size = 0;
//     in.read((char*)&glyph_size, sizeof(float));

// 	size_t number_of_font_glyphs = 0;
//     in.read((char*)&number_of_font_glyphs, sizeof(size_t));
//     for (int i = 0; i < number_of_font_glyphs; i++)
//     {
//     	FontGlyph font_glyph;
//     	in.read((char*)&font_glyph.char_id, sizeof(int));
//     	in.read((char*)&font_glyph.advance, sizeof(float));
//     	in.read((char*)&font_glyph.left, sizeof(float));
//     	in.read((char*)&font_glyph.right, sizeof(float));
//     	in.read((char*)&font_glyph.top, sizeof(float));
//     	in.read((char*)&font_glyph.bottom, sizeof(float));
//     	font_glyphs.emplace(font_glyph.char_id, font_glyph);
//     }

// 	//float glyph_size = 0;
//     // in.read((char*)&glyph_size, sizeof(float));

// 	// size_t number_of_font_glyphs = 0;
//     // in.read((char*)&number_of_font_glyphs, sizeof(size_t));
//     // for (int i = 0; i < number_of_font_glyphs; i++)
//     // {
//     // 	Font_Glyph font_glyph;
//     // 	in.read((char*)&font_glyph.char_id, sizeof(int));
//     // 	in.read((char*)&font_glyph.advance, sizeof(float));
//     // 	in.read((char*)&font_glyph.left, sizeof(float));
//     // 	in.read((char*)&font_glyph.right, sizeof(float));
//     // 	in.read((char*)&font_glyph.top, sizeof(float));
//     // 	in.read((char*)&font_glyph.bottom, sizeof(float));
//     // 	font_glyphs[font_glyph_char] = ;
//     // }
//     Font* font = new Font(get_texture(font_name), font_glyphs);
//     font->glyph_size = glyph_size;
//     return font
// }


}//namespace Tactics