#include "Window.h"
#include <stdlib.h>
#include "math/Vectors.h"
#include "glad/glad.h"
namespace Tactics
{
	
	// GLFWwindow* glfw_window;
	// int x;
	// int y;
	// int width;
	// int height;
	// bool vsync;
	// bool is_running;


	// Window* init_window()
	// static void set_previous_values(Window* window);
	// //Add check to see if the window was properly created
	// void init_window(Window* window, int x, int y, int width, int height)
	// {
	// 	GLFWwindow* glfw_window = glfwCreateWindow(width, height, "Test", NULL, NULL);
	// 	window->glfw_window = glfw_window;
	// 	window->x = x;
	// 	window->y = y;
	// 	window->width = width;
	// 	window->height = height;
	// 	window->vsync = false;
	// 	window->is_running = true;
	// 	glfwSetWindowPos(glfw_window, x, y);
	// 	glfwMakeContextCurrent(glfw_window);
	// }
	// void update_window(Window* window)
	// {
	// 	if (glfwWindowShouldClose(window->glfw_window))
	// 		window->is_running = false;
	// 	if (window->x != prev_x || window->y != prev_y)
	// 		glfwSetWindowPos(window->glfw_window, window->x, window->y);
	// 	if (window->width != prev_width ||window->height != prev_height)
	// 		glfwSetWindowSize(window->glfw_window, window->width, window->height);
	// 	if (window->vsync != prev_vsync)
	// 		glfwSwapInterval(window->vsync);
	// 	set_previous_values(window);
	// }
	// void free_window(Window* window)
	// {
	// 	free(window);
	// }
	// static void set_previous_values(Window* window)
	// {
	// 	prev_x = window->x;
	// 	prev_y = window->y;
	// 	prev_width = window->width;
	// 	prev_height = window->height;
	// 	//prev_is_full_screen = window->isFullScreen;
	// 	prev_vsync = window->vsync;		
	// }

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void set_view_port(int x, int y, int width, int height);
void set_mouse_scroll(float offset);
//Add check to see if the window was properly created
void init_window(Window* window, int x, int y, int width, int height, const char* name)
{
	if (!glfwInit())
	{
		log_error("GLFW failed to initialize");
		exit(0);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
	window->position = ivec2(x, y);
	window->width = width;
	window->height = height;
	window->name = name;
	window->vsync = false;
	window->should_close = false;
	window->glfw_window = glfwCreateWindow(window->width, window->height, window->name, NULL, NULL);
	glfwSwapInterval(window->vsync);
	glfwSetWindowPos(window->glfw_window, window->position.x, window->position.y);
	glfwMakeContextCurrent(window->glfw_window);
	//glad: load all Opengl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD!\n");
		exit(0);	
	}
	glViewport(0, 0, window->width, window->height);
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}
void init_window(Window* window, iVector2 position, int width, int height, const char* name)
{
	if (!glfwInit())
	{
		log_error("GLFW failed to initialize");
		exit(0);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
	window->position = position;
	window->width = width;
	window->height = height;
	window->name = name;
	window->vsync = false;
	window->should_close = false;
	window->glfw_window = glfwCreateWindow(window->width, window->height, window->name, NULL, NULL);
	glfwSwapInterval(window->vsync);
	glfwSetWindowPos(window->glfw_window, window->position.x, window->position.y);
	glfwMakeContextCurrent(window->glfw_window);
}
void set_window_vsync(Window* window, bool value)
{
	window->vsync = value;
	glfwSwapInterval(window->vsync);
}
void set_window_pos(Window* window, iVector2 position)
{
	window->position = position;
	glfwSetWindowPos(window->glfw_window, window->position.x, window->position.y);
}
void set_window_width(Window* window, int width)
{
	window->width = width;
	glfwSetWindowSize(window->glfw_window, window->width, window->height);
}
void set_window_height(Window* window, int height)
{
	window->height = height;
	glfwSetWindowSize(window->glfw_window, window->width, window->height);
}
void set_window_size(Window* window, int width, int height)
{
	window->width = width;
	window->height = height;
	glfwSetWindowSize(window->glfw_window, window->width, window->height);
}
iVector2 get_window_size(Window* window)
{
	return {window->width, window->height};
}
void update_window(Window* window)
{
	window->should_close = glfwWindowShouldClose(window->glfw_window);
}
void enable_mouse_cursor(Window* window, bool value)
{
	if (value == true)
		glfwSetInputMode(window->glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else if (value == false)
		glfwSetInputMode(window->glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     set_view_port(0, 0, width, height);
// }
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//set_mouse_scroll((float)yoffset);
}

void set_glfw_callbacks(Window* window)
{
	//glfwSetFramebufferSizeCallback(window->glfw_window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(window->glfw_window, mouse_callback);
	glfwSetScrollCallback(window->glfw_window, scroll_callback);
} 

}


