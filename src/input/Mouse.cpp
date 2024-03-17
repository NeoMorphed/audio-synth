#include "Mouse.h"
#include "core/Window.h"
#include "math/Vectors.h"
#include "MouseButtonCodes.h"

namespace Tactics
{
	void update_mouse(Mouse* mouse, Window* window)
	{
		
		glfwGetCursorPos(window->glfw_window, &(double)mouse->position.x, &(double)mouse->position.y);

		update_mouse_states(mouse, window);
	}
	void update_mouse_states(Mouse* mouse, Window* window)
	{
		
		mouse->state[MOUSE_BUTTON_LEFT]	 	= glfwGetMouseButton(window->glfw_window, MOUSE_BUTTON_1); 
		mouse->state[MOUSE_BUTTON_RIGHT]	 	= glfwGetMouseButton(window->glfw_window, MOUSE_BUTTON_2); 
		mouse->state[MOUSE_BUTTON_MIDDLE] 	= glfwGetMouseButton(window->glfw_window, MOUSE_BUTTON_3); 
		mouse->state[MOUSE_BUTTON_MIDDLE] 	= glfwGetMouseButton(window->glfw_window, MOUSE_BUTTON_4); 
		mouse->state[MOUSE_BUTTON_MIDDLE] 	= glfwGetMouseButton(window->glfw_window, MOUSE_BUTTON_5); 
		mouse->state[MOUSE_BUTTON_MIDDLE] 	= glfwGetMouseButton(window->glfw_window, MOUSE_BUTTON_6); 
		mouse->state[MOUSE_BUTTON_MIDDLE] 	= glfwGetMouseButton(window->glfw_window, MOUSE_BUTTON_7); 
		mouse->state[MOUSE_BUTTON_MIDDLE] 	= glfwGetMouseButton(window->glfw_window, MOUSE_BUTTON_8); 
	
		if (mouse->current_state_number == MAX_MOUSE_STATES - 1)
		{
			mouse->current_state_number = 0;
		}
		else mouse->current_state_number++;
		memcpy(mouse->states[mouse->current_state_number], mouse->state, sizeof(bool) * MOUSE_STATE_SIZE);
	}
	int get_previous_mouse_state_number(Mouse* mouse)
	{
		if (mouse->current_state_number == 0)
			return MAX_MOUSE_STATES - 1;
		else return mouse->current_state_number - 1;
	}
	// void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
	// {
	// 	position = vec2((float)xpos, (float)ypos);
	// }
}