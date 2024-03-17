#ifndef RECTANGLE_H
#define	RECTANGLE_H

namespace Tactics
{
	struct Rectangle
	{
	private:

	public:
		int x;
		int y;
		int width;
		int height;
		Rectangle();
		Rectangle(int x, int y, int width, int height);
		
		int top;
		int bottom;
		int left;
		int right;
	};
	bool rect_intersect(const Rectangle& a, const Rectangle &b);
	std::ostream& operator<<(std::ostream& os, const Rectangle& rect);
}
#endif