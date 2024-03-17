#ifndef FONT_H
#define FONT_H

#include <unordered_map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "math/Vectors.h"
#include "core/Rectangle.h"
#include "rendering/Texture.h"

namespace Tactics
{
	struct FontCharacter 
	{
		unsigned int TextureID;
		Vector2 Size;
		Vector2 Bearing;
		unsigned int Advance;
	};
	struct FontChar
	{
		int char_id;
		Rectangle source_rect;
		Vector2 bearing;
		int advance;
		FontChar();
		FontChar(int char_id, Rectangle source_rect, Vector2 bearing, int advance);
	};
	struct BmFont
	{
		Texture* texture;
		std::unordered_map<char, FontChar> font_chars;
		int line_height = 0;
		BmFont();
		BmFont(Texture* texture, std::unordered_map<char, FontChar> font_chars);
	};
	int get_string_width_of_font(const std::string& text, BmFont* font);

	// struct TextToRender
	// {
	// 	std::string text;
	// 	Vector2 pso
	// }

	struct Font
	{
		FT_Face face;
		int size = 48;
		std::unordered_map<char, FontCharacter> fontCharacters;
		Font();
		Font(FT_Face face, std::unordered_map<char, FontCharacter> fontCharacters);
		//FT_Done_Face(face);
	};
}

#endif