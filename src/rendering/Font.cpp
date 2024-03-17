#include "Font.h"

namespace Tactics
{
	FontChar::FontChar()
	{
		
	}
	FontChar::FontChar(int char_id, Rectangle source_rect, Vector2 bearing, int advance)
		:char_id(char_id), source_rect(source_rect), bearing(bearing), advance(advance) 
	{

	}
	BmFont::BmFont()
	{

	}
	BmFont::BmFont(Texture* texture, std::unordered_map<char, FontChar> font_chars)
		:texture(texture), font_chars(font_chars)
	{

	}
	int get_string_width_of_font(const std::string& text, BmFont* font)
	{
		int string_size = 0;
		for (int i = 0; i < text.size(); i++)
		{
			string_size += font->font_chars[text[i]].advance;
		}
		return string_size;
	}
	Font::Font()
	{
		
	}
	Font::Font(FT_Face face, std::unordered_map<char, FontCharacter> fontCharacters)
		:face(face), fontCharacters(fontCharacters)
	{

	}
}

