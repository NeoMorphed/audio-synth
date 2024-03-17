#include "Rectangle.h"

namespace Tactics
{
	Rectangle::Rectangle()
		:x(0), y(0), width(0), height(0)
	{

	}
	Rectangle::Rectangle(int x, int y, int width, int height)
		:x(x), y(y), width(width), height(height)
	{
		top = y;
		bottom = y + height;
		left = x;
		right = x + width;
	}
	bool rect_intersect(const Rectangle& a, const Rectangle &b)
	{
		return b.left < a.right &&
                   a.left < b.right &&
                   b.top < a.bottom &&
                   a.top < b.bottom;
	}
	std::ostream& operator<<(std::ostream& os, const Rectangle& rect)
	{
		os << "{ " << rect.x << ", " << rect.y << ", " << rect.width << ", " << rect.height << " }";
		return os;
	}
}