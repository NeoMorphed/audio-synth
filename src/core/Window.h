#ifndef WINDOW_H
#define	WINDOW_H

#include "GLFW/glfw3.h"
#include "math/Vectors.h"

namespace Tactics
{

struct Window
{
	GLFWwindow* glfw_window;
	const char* name;
	iVector2 position;
	int width;
	int height;
	//bool isFullScreen = false;
	bool vsync;
	bool should_close;
};
void init_window(Window* window, int x, int y, int width, int height, const char* name);
void init_window(Window* window, iVector2 position, int width, int height, const char* name);
void set_window_vsync(Window* window, bool value);
void set_window_pos(Window* window, iVector2 position);
void set_window_width(Window* window, int width);
void set_window_height(Window* window, int height);
void set_window_size(Window* window, int width, int height);
iVector2 get_window_size(Window* window);
void update_window(Window* window);
void enable_mouse_cursor(Window* window, bool value);

void set_glfw_callbacks(Window* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



}// namespace Tactics
#endif